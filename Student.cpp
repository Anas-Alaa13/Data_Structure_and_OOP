// Student.cpp
#include "Student.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <map>
#include <unordered_map>

using namespace std;

Student::Student(DataManager& dm) : dm(dm), studentID(0) {}

void Student::setUsername(const string& user) {
    username = user;
}

void Student::setStudentID(int id) {
    studentID = id;
}

int Student::getStudentID() const {
    return studentID;
}

string Student::getUsername() const {
    return username;
}

bool Student::alreadyRegistered(const string& courseName) {
    auto it = dm.registrations.find(studentID);
    if (it != dm.registrations.end()) {
        for (const auto& course : it->second) {
            if (course == courseName) {
                return true;
            }
        }
    }
    return false;
}

bool Student::prerequisitesMet(const string& prereq) {
    if (prereq.empty()) return true;

    auto it = dm.registrations.find(studentID);
    if (it != dm.registrations.end()) {
        stringstream ss(prereq);
        string singlePrereq;
        while (getline(ss, singlePrereq, ',')) {
            singlePrereq.erase(remove_if(singlePrereq.begin(), singlePrereq.end(), ::isspace), singlePrereq.end());
            bool met = false;
            for (const auto& course : it->second) {
                if (course == singlePrereq) {
                    met = true;
                    break;
                }
            }
            if (!met) return false;
        }
        return true;
    }
    return false;
}

bool Student::isCourseValid(const string& courseName) {
    string inputLower = courseName;
    transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);
    for (const auto& course : dm.courses) {
        string titleLower = course.title;
        transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
        if (inputLower == titleLower) {
            return true;
        }
    }
    return false;
}

Course Student::findCourse(const string& searchName) {
    string searchLower = searchName;
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    for (const auto& course : dm.courses) {
        string titleLower = course.title;
        transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
        if (searchLower == titleLower) {
            return course;
        }
    }
    return Course();
}

bool Student::registerCourse(const string& courseName, string& errorMessage) {
    if (!isCourseValid(courseName)) {
        errorMessage = "Course not found or name is incorrect.";
        return false;
    }

    Course course = findCourse(courseName);
    if (course.title.empty()) {
        errorMessage = "Course not found.";
        return false;
    }

    if (alreadyRegistered(courseName)) {
        errorMessage = "You are already registered in this course.";
        return false;
    }

    if (!prerequisitesMet(course.prerequisites)) {
        errorMessage = "Prerequisites not met for this course.";
        return false;
    }

    dm.registrations[studentID].push_back(courseName);
    errorMessage = "Registered successfully.";
    return true;
}

vector<string> Student::getRegisteredCourses() {
    vector<string> courses;
    auto it = dm.registrations.find(studentID);
    if (it != dm.registrations.end()) {
        courses = it->second;
    }
    return courses;
}

vector<Grade> Student::getGrades() {
    vector<Grade> studentGrades;
    for (const auto& grade : dm.grades) {
        if (grade.ID == studentID) {
            studentGrades.push_back(grade);
        }
    }
    return studentGrades;
}

vector<Grade> Student::filterGrades(double minGPA) {
    vector<Grade> filteredGrades;
    for (const auto& grade : dm.grades) {
        if (grade.ID == studentID && grade.GPA >= minGPA) {
            filteredGrades.push_back(grade);
        }
    }
    return filteredGrades;
}

string Student::generateReport(const string& id) {
    stringstream report;
    report << "******** Student Grade Report ********\n";
    report << "Name: " << username << "\n";
    report << "ID: " << id << "\n";

    auto regIt = dm.registrations.find(stoi(id));
    vector<string> registeredCourses;
    if (regIt != dm.registrations.end()) {
        registeredCourses = regIt->second;
    }

    if (registeredCourses.empty()) {
        report << "No registration data found for user with ID: " << id << "\n";
        return report.str();
    }

    map<string, Grade> courseGrades;
    for (const auto& grade : dm.grades) {
        if (grade.ID == stoi(id)) {
            courseGrades[grade.Subject] = grade;
        }
    }

    unordered_map<string, int> courseCreditHours;
    for (const auto& course : dm.courses) {
        courseCreditHours[course.title] = course.creditHours;
    }

    vector<vector<string>> semesters;
    vector<string> currentSemester;
    int currentSemesterHours = 0;

    for (const string& course : registeredCourses) {
        if (courseCreditHours.find(course) != courseCreditHours.end()) {
            int courseHours = courseCreditHours[course];
            if (currentSemesterHours + courseHours > 15) {
                semesters.push_back(currentSemester);
                currentSemester.clear();
                currentSemesterHours = 0;
            }
            currentSemester.push_back(course);
            currentSemesterHours += courseHours;
        }
    }

    if (!currentSemester.empty()) {
        semesters.push_back(currentSemester);
    }

    report << "\n******** Registered Courses by Semester ********\n";
    double totalGPA = 0;
    int courseCount = 0;

    for (size_t i = 0; i < semesters.size(); ++i) {
        report << "Semester " << (i + 1) << ":\n";
        for (const string& course : semesters[i]) {
            report << "- " << course << " (" << courseCreditHours[course] << " credit hours)";
            if (courseGrades.find(course) != courseGrades.end()) {
                const Grade& grade = courseGrades[course];
                report << " | Quiz: " << grade.Quiz
                    << " | Assignment: " << grade.Assignment
                    << " | Midterm: " << grade.Midterm
                    << " | Practical: " << grade.Practical
                    << " | Final: " << grade.Final
                    << " | Total: " << grade.Total
                    << " | GPA: " << grade.GPA;
                totalGPA += grade.GPA;
                courseCount++;
            }
            else {
                report << " | Grade: N/A";
            }
            report << "\n";
        }
        report << "-------------------------------\n";
    }

    if (courseCount > 0) {
        double overallGPA = totalGPA / courseCount;
        report << "\nOverall GPA: " << overallGPA << "\n";
    }
    else {
        report << "\nNo grades found for your registered courses.\n";
    }

    report << "*********************************************\n";

    string reportFilename = "Student_Report_" + id + ".txt";
    ofstream reportFile(reportFilename);
    if (reportFile.is_open()) {
        reportFile << report.str();
        reportFile.close();
    }

    return report.str();
}