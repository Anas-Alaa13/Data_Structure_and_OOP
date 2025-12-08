#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

DataManager::DataManager() {
    readUsers("database.csv");
    readCourses("courses.csv");
    readRegistrations("registrations.csv");
    readGrades("grades.csv");
}

void DataManager::readUsers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        User user;
        std::string temp;
        std::getline(ss, temp, ','); user.ID = std::stoi(temp);
        std::getline(ss, user.FirstName, ',');
        std::getline(ss, user.LastName, ',');
        std::getline(ss, user.PhoneNumber, ',');
        std::getline(ss, user.Username, ',');
        std::getline(ss, user.Password, ',');
        std::getline(ss, user.Email, ',');
        users.push_back(user);
    }
    file.close();
}

void DataManager::readCourses(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Course course;
        std::string temp;
        std::getline(ss, course.title, ',');
        std::getline(ss, course.syllabus, ',');
        std::getline(ss, temp, ','); // نقرأ creditHours كـ string مؤقتًا
        try {
            course.creditHours = std::stoi(temp); // نحوّله لـ int
        }
        catch (const std::exception& e) {
            course.creditHours = 0; // قيمة افتراضية لو التحويل فشل
            std::cerr << "Error converting creditHours for course " << course.title << ": " << e.what() << std::endl;
        }
        std::getline(ss, course.instructor, ',');
        std::getline(ss, course.prerequisites, ',');
        courses.push_back(course);
        courseTitles.insert(course.title);
    }
    file.close();
}

void DataManager::readRegistrations(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string userIDStr;
        std::getline(ss, userIDStr, ',');
        int userID = std::stoi(userIDStr);
        std::vector<std::string> subjects;
        std::string subject;
        while (std::getline(ss, subject, ',')) {
            if (!subject.empty()) subjects.push_back(subject);
        }
        registrations[userID] = subjects;
    }
    file.close();
}

void DataManager::readGrades(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Grade grade;
        std::string temp;
        std::getline(ss, temp, ','); grade.ID = std::stoi(temp);
        std::getline(ss, grade.Subject, ',');
        std::getline(ss, temp, ','); grade.Quiz = std::stoi(temp);
        std::getline(ss, temp, ','); grade.Assignment = std::stoi(temp);
        std::getline(ss, temp, ','); grade.Midterm = std::stoi(temp);
        std::getline(ss, temp, ','); grade.Practical = std::stoi(temp);
        std::getline(ss, temp, ','); grade.Final = std::stoi(temp);
        std::getline(ss, temp, ','); grade.Total = std::stoi(temp);
        std::getline(ss, temp, ','); grade.GPA = std::stod(temp);
        grades.push_back(grade);
    }
    file.close();
}

void DataManager::writeUsers(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error writing to " << filename << std::endl;
        return;
    }
    file << "ID,FirstName,LastName,PhoneNumber,Username,Password,Email\n";
    for (const auto& user : users) {
        file << user.ID << ',' << user.FirstName << ',' << user.LastName << ','
            << user.PhoneNumber << ',' << user.Username << ',' << user.Password
            << ',' << user.Email << '\n';
    }
    file.close();
}

void DataManager::writeCourses(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error writing to " << filename << std::endl;
        return;
    }
    file << "Course_Title,Syllabus,Credit_Hours,Instructor,Prerequisites\n";
    for (const auto& course : courses) {
        file << course.title << ',' << course.syllabus << ',' << course.creditHours << ','
            << course.instructor << ',' << course.prerequisites << '\n';
    }
    file.close();
}

void DataManager::writeRegistrations(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error writing to " << filename << std::endl;
        return;
    }
    int maxCourses = 0;
    for (const auto& entry : registrations) {
        if (entry.second.size() > maxCourses) maxCourses = entry.second.size();
    }
    file << "UserID";
    for (int i = 1; i <= maxCourses; i++) file << ",Subject" << i;
    file << '\n';
    for (const auto& entry : registrations) {
        file << entry.first;
        for (const auto& subject : entry.second) {
            file << ',' << subject;
        }
        file << '\n';
    }
    file.close();
}

void DataManager::writeGrades(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error writing to " << filename << std::endl;
        return;
    }
    file << "ID,Subject,Quiz,Assignment,Midterm,Practical,Final,Total,GPA\n";
    for (const auto& grade : grades) {
        file << grade.ID << ',' << grade.Subject << ',' << grade.Quiz << ','
            << grade.Assignment << ',' << grade.Midterm << ',' << grade.Practical << ','
            << grade.Final << ',' << grade.Total << ',' << grade.GPA << '\n';
    }
    file.close();
}

void DataManager::saveAllData() {
    writeUsers("database.csv");
    writeCourses("courses.csv");
    writeRegistrations("registrations.csv");
    writeGrades("grades.csv");
}