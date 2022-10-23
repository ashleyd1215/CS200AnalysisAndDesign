//
//  CourseList.hpp
//  CourseSort
//
//  Created by Ashley De Venuto on 10/22/22.
//

#ifndef CourseList_hpp
#define CourseList_hpp

#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Course.hpp"

using namespace std;

class Courses
{
private:
    /// Stores course objects in memory
    vector<Course> courses;

    /// Method that adds course to datatype
    void addCourse(const Course course);

    /// A method called by addCourse which appends a course,
    /// wraps data type implementation, and should call addCourse.
    void append(const Course course) {
        courses.push_back(course);
    }

    /// A method called by addCourse which inserts a course in data type,
    /// wraps data type implementation, and should call addCourse.
    void insert(const size_t position, const Course course) {
        vector<Course>::iterator iter;
        iter = courses.begin() + position;
        courses.insert(iter, course);
    }

    /// Use this method istead of directly accessing datatype
    Course at(const size_t index) const {
        return courses.at(index);
    }

    /// Performs a Binary search that searches an already sorted data
    /// Returns midpoint inn order to get to the closest value
    /// The caller checks for return value to see if a match is found.
    /// getSize() should be called before if > 0.
    size_t binarySearch(const string key) const;

    /// Calls binarySearch and checks return value.
    /// Match will return if course is found.
    /// If no match is found it will return default Course object.
    Course findCourse(const string courseId) const;

    /// Splits a string into a vector<string> of tokens by a delimiter
    vector<string> splitString(const string input, const string delimiter) const;

public:
    /// Clears data
    void clear() {
        courses.clear();
    }

    /// Initialize the Courses object from a CSV file
    void loadFromCSV(const string filename, const string deliminator = ",");

    /// Prints a course and its Prerequisites.
    void printCourse(const string courseId) const;

    /// Prints courses by Id and Title in alphanumeric order.
    void printAll() const;

    /// Wraps sixe() calls and uses this method instead of accessing the datatype directly
    size_t getSize() const {
        return courses.size();
    }
};
#endif /* CourseList_hpp */
