// DataManager.h
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <set>
#include "Structures.h"

class DataManager {
public:
    std::vector<User> users;
    std::vector<Course> courses;
    std::set<std::string> courseTitles;
    std::map<int, std::vector<std::string>> registrations;
    std::vector<Grade> grades;
    std::vector<StudentGrade> studentGrades; // قائمة جديدة لتخزين الدرجات
    DataManager();
    void readUsers(const std::string& filename);
    void readCourses(const std::string& filename);
    void readRegistrations(const std::string& filename);
    void readGrades(const std::string& filename);
    void writeUsers(const std::string& filename);
    void writeCourses(const std::string& filename);
    void writeRegistrations(const std::string& filename);
    void writeGrades(const std::string& filename);
    void saveAllData();
};

#endif