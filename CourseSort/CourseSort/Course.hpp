//
//  Course.hpp
//  CourseSort
//
//  Created by Ashley De Venuto on 10/22/22.
//

#ifndef Course_hpp
#define Course_hpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Course {

private:
    string id;
    string title;
    vector<Course> prerequisites;

public:
   // Default constructor
    Course() {
        
    }

    // Accessor method
    string getId() const {
        return this->id;
    }

    string getTitle() const {
        return this->title;
    }

   // Mutator method
    void setId(const string id) {
        this->id = id;
    }

    void setTitle(const string title) {
        this->title = title;
    }

    // Add prerequisites
    void addPrerequisite(const Course course) {
        prerequisites.push_back(course);
    }

  // Display Id, Title, and Prerequisites
    void print() const;
};

#endif /* Course_hpp */
