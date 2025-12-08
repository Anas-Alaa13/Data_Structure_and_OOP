// Student.h
#pragma once
#include "DataManager.h"
#include "Structures.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

class Student {
private:
    DataManager& dm;
    int studentID;
    std::string username;

public:
    Student(DataManager& dm);
    void setUsername(const std::string& username);
    void setStudentID(int id);
    int getStudentID() const;
    std::string getUsername() const;
    bool registerCourse(const std::string& courseName, std::string& errorMessage);
    Course findCourse(const std::string& courseName);
    std::vector<Grade> getGrades();
    std::vector<Grade> filterGrades(double minGPA);
    std::vector<std::string> getRegisteredCourses();
    std::string generateReport(const std::string& studentID);
    bool prerequisitesMet(const std::string& courseName);
    bool isCourseValid(const std::string& courseName);
    bool alreadyRegistered(const std::string& courseName);
};