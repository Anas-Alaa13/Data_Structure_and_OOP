#include "Admin.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Admin::Admin(DataManager& dataManager) : dm(dataManager) {}

void Admin::displayMenu() {
    std::cout << "Admin Menu:\n"
        << "1. Upload Course\n"
        << "2. Set Prerequisites\n"
        << "3. Edit Student Data\n"
        << "4. Show Courses\n"
        << "5. Manage Student Grades\n"
        << "6. Delete User\n"
        << "7. Exit\n";
}

void Admin::deleteUser(int id, bool& undo, User& deletedUser) {
    auto it = std::find_if(dm.users.begin(), dm.users.end(),
        [id](const User& u) { return u.ID == id; });
    if (it == dm.users.end()) {
        throw std::runtime_error("User not found!");
    }

    deletedUser = *it;
    dm.users.erase(it);
    dm.registrations.erase(id);
    dm.grades.erase(std::remove_if(dm.grades.begin(), dm.grades.end(),
        [id](const Grade& g) { return g.ID == id; }), dm.grades.end());

    dm.saveAllData();
    undo = false;
}

void Admin::editStudentData(const std::string& username, int id, const std::string& firstName,
    const std::string& lastName, const std::string& phone,
    const std::string& email, const std::string& password) {
    auto it = std::find_if(dm.users.begin(), dm.users.end(),
        [&username](const User& u) { return u.Username == username; });
    if (it == dm.users.end()) {
        throw std::runtime_error("Username not found!");
    }

    std::set<std::string> existingUsernames;
    for (const auto& user : dm.users) {
        if (user.Username != username) {
            existingUsernames.insert(user.Username);
        }
    }
    if (!username.empty() && existingUsernames.find(username) != existingUsernames.end()) {
        throw std::runtime_error("Username already exists!");
    }

    if (id != -1) it->ID = id;
    if (!firstName.empty()) it->FirstName = firstName;
    if (!lastName.empty()) it->LastName = lastName;
    if (!phone.empty()) it->PhoneNumber = phone;
    if (!email.empty()) it->Email = email;
    if (!password.empty()) it->Password = password;

    dm.writeUsers("database.csv");
}

void Admin::ShowCourses(std::string& output) {
    std::stringstream ss;
    int i = 1;
    for (const auto& course : dm.courses) {
        ss << i++ << ". Title: " << course.title
            << " | Syllabus: " << course.syllabus
            << " | Credit Hours: " << course.creditHours
            << " | Instructor: " << course.instructor
            << " | Prerequisites: " << course.prerequisites << "\n";
    }
    output = ss.str();
}

bool Admin::isValidPrerequisites(const std::string& prereqList) {
    if (prereqList.empty()) return true;
    std::stringstream ss(prereqList);
    std::string prereq;
    while (std::getline(ss, prereq, ',')) {
        if (dm.courseTitles.find(prereq) == dm.courseTitles.end()) {
            return false;
        }
    }
    return true;
}

void Admin::UploadCourse(const std::string& title, const std::string& syllabus,
    int creditHours, const std::string& instructor) {
    if (title.empty() || syllabus.empty() || instructor.empty() || creditHours <= 0) {
        throw std::runtime_error("All fields are required and Credit Hours must be positive!");
    }

    Course newCourse;
    newCourse.title = title;
    if (dm.courseTitles.find(title) != dm.courseTitles.end()) {
        throw std::runtime_error("Course with this title already exists!");
    }

    newCourse.syllabus = syllabus;
    newCourse.creditHours = creditHours;
    newCourse.instructor = instructor;
    newCourse.prerequisites = "";

    dm.courses.push_back(newCourse);
    dm.courseTitles.insert(title);
    dm.writeCourses("courses.csv");
}

void Admin::SetPrerequisites(const std::string& title, const std::string& prereqs) {
    if (title.empty()) {
        throw std::runtime_error("Course title is required!");
    }

    auto it = std::find_if(dm.courses.begin(), dm.courses.end(),
        [&title](const Course& c) { return c.title == title; });
    if (it == dm.courses.end()) {
        throw std::runtime_error("Course not found!");
    }

    if (!prereqs.empty() && !isValidPrerequisites(prereqs)) {
        throw std::runtime_error("Invalid prerequisites!");
    }

    it->prerequisites = prereqs;
    dm.writeCourses("courses.csv");
}

void Admin::manageStudentGrades(int id, const std::string& subject, int quiz, int assignment,
    int midterm, int practical, int finalExam) {
    if (subject.empty()) {
        throw std::runtime_error("Subject is required!");
    }

    if (quiz < 0 || quiz > 10 || assignment < 0 || assignment > 10 ||
        midterm < 0 || midterm > 15 || practical < 0 || practical > 20 ||
        finalExam < 0 || finalExam > 60) {
        throw std::runtime_error("Grades are out of valid range!");
    }

    int total = quiz + assignment + midterm + practical + finalExam;
    if (total > 100) {
        throw std::runtime_error("Total exceeds 100!");
    }

    auto userIt = std::find_if(dm.users.begin(), dm.users.end(),
        [id](const User& u) { return u.ID == id; });
    if (userIt == dm.users.end()) {
        throw std::runtime_error("Student ID not found!");
    }

    auto regIt = dm.registrations.find(id);
    if (regIt == dm.registrations.end() ||
        std::find(regIt->second.begin(), regIt->second.end(), subject) == regIt->second.end()) {
        throw std::runtime_error("Student is not registered for this subject!");
    }

    auto gradeIt = std::find_if(dm.grades.begin(), dm.grades.end(),
        [id, &subject](const Grade& g) { return g.ID == id && g.Subject == subject; });

    float gpa = calculateGPA(total);
    if (gradeIt != dm.grades.end()) {
        gradeIt->Quiz = quiz;
        gradeIt->Assignment = assignment;
        gradeIt->Midterm = midterm;
        gradeIt->Practical = practical;
        gradeIt->Final = finalExam;
        gradeIt->Total = total;
        gradeIt->GPA = gpa;
    }
    else {
        Grade newGrade = { id, subject, quiz, assignment, midterm, practical, finalExam, total, gpa };
        dm.grades.push_back(newGrade);
    }

    dm.writeGrades("grades.csv");
}

float Admin::calculateGPA(int total) {
    if (total >= 90) return 4.0;
    if (total >= 85) return 3.7;
    if (total >= 80) return 3.3;
    if (total >= 75) return 3.0;
    if (total >= 70) return 2.7;
    if (total >= 65) return 2.3;
    if (total >= 60) return 2.0;
    return 0.0;
}

