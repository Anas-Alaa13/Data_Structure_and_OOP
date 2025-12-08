#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "DataManager.h"
#include "Structures.h"

class Admin {
private:
    DataManager& dm;

public:
    Admin(DataManager& dm);

    // Anas
    void displayMenu();
    void deleteUser(int id, bool& undo, User& deletedUser);
    void editStudentData(const std::string& username, int id, const std::string& firstName,
        const std::string& lastName, const std::string& phone,
        const std::string& email, const std::string& password);

    // Framawy-Ahmed
    void ShowCourses(std::string& output);
    bool isValidPrerequisites(const std::string& prereqList);
    void UploadCourse(const std::string& title, const std::string& syllabus,
        int creditHours, const std::string& instructor);
    void SetPrerequisites(const std::string& title, const std::string& prereqs);

    // Nabil
    void manageStudentGrades(int id, const std::string& subject, int quiz, int assignment,
        int midterm, int practical, int finalExam);
    float calculateGPA(int total);
};

#endif