//
//  CourseList.cpp
//  CourseSort
//
//  Created by Ashley De Venuto on 10/22/22.
//

#include "CourseList.hpp"

void Courses::addCourse(const Course course) {
    // if added to first element, push
    if (getSize() == 0) {
        append(course);
    } // if last element is less than one being inserted, push
    // useful if file is mostly sorted
    else if (at(getSize() - 1).getId().compare(course.getId()) < 0) {
        append(course);
    }
    else { // otherwise insert which requires a binary search and then moving elements to make room
        size_t insertionPoint;
        insertionPoint = binarySearch(course.getId());

        if (insertionPoint != SIZE_MAX) {
            insert(insertionPoint, course);
        }
    }
}

size_t Courses::binarySearch(const string key) const {
    size_t midPoint = SIZE_MAX;
    size_t lowPoint = 0;
    size_t highPoint = getSize() - 1;

    // if the points haven't crossed each other continue
    // its possible for the highpoint to wrap around from zero to SIZE_MAX, stop when that happens
    while (highPoint != SIZE_MAX && highPoint >= lowPoint) {
        midPoint = (highPoint + lowPoint) / 2; // locate the midpoint

        Course course = at(midPoint); // get value at midpoint

        if (course.getId() < key) {   // what we are looking for is in the lower half?
            lowPoint = midPoint + 1;
        }
        else if (course.getId() > key) { // what we are looking for is in the upper half?
            highPoint = midPoint - 1;
        }
        else {
            return midPoint;            // found a match
        }
    }

    // even if not found this is the closest point for insertion
    // caller is responsible for checking value to determine how used
    return midPoint;
}

void Courses::printAll() const
{
    // already sorted so print out all courses by id and title
    for (size_t i = 0; i < getSize(); ++i) {
        Course course = at(i);
        cout << course.getId() << " " << course.getTitle() << endl;
    }
}

void Courses::printCourse(const string courseId) const {
    Course course = findCourse(courseId);

    if (course.getId().compare(courseId) == 0) {
        // found
        course.print();
    }
    else {
        // not found
        cout << "Could not find course: " << courseId << endl;
    }
}

void Courses::loadFromCSV(const string filename, const string deliminator /* = "," */) {
    string line;            // holds a single line read from the file
    int lineNumber = 0;     // maintains a count of which line number in file we are on
    ifstream inputFile(filename.c_str()); // open input file

    if (inputFile.is_open())
    {
        while (inputFile.good())
        {
            // read line from file
            getline(inputFile, line);
            if (line != "") {
                ++lineNumber;
                auto tokens = splitString(line, deliminator); // split line into tokens by deliminator

                // check if there at least 2 tokens, id and title
                if (tokens.size() < 2) {
                    cout << "Error: Line format error, expected 2 or more tokens, got ";
                    cout << tokens.size() << " tokens, line number: " << lineNumber << endl;

                    // skip line we cannot parse
                    continue; // while (inputFile.good())
                }

                Course course;
                course.setId(tokens[0]);

                // check if course is already loaded
                Course duplicateCourse = findCourse(course.getId());
                if (duplicateCourse.getId() != "") {
                    cout << "Warning: Duplicate course detected, line number: ";
                    cout << lineNumber << endl;

                    // dont add duplicate
                    continue; // while (inputFile.good())
                }

                // we can parse and not a duplicate so set the rest of the properties
                course.setTitle(tokens[1]);

                // check for any prerequisites and add to course
                for (size_t i = 2; i < tokens.size(); ++i) {
                    string prerequisiteId = tokens.at(i);

                    // only add if prerequisite is already loaded
                    Course courseExists = findCourse(prerequisiteId);

                    if (courseExists.getId() == "")
                    {
                        cout << "Warning: Prerequisite not found, course: " << course.getId();
                        cout << ", prerequisite: " << prerequisiteId << endl;

                        // not found, skip to next
                        continue; // for (size_t i ...
                    }

                    // found, add course
                    course.addPrerequisite(courseExists);
                }

                // add course to data structure
                addCourse(course);
            }
        }
        inputFile.close();

        if (lineNumber == 0)
            throw runtime_error("No Data in " + filename);
    }
    else
        throw runtime_error("Failed to open " + filename);
}

Course Courses::findCourse(const string courseId) const {
    size_t index = binarySearch(courseId);
    if (index != SIZE_MAX) {
        Course course = at(index);

        if (course.getId().compare(courseId) == 0) {
            // found
            return course;
        }
        else {
            // not found
            return Course();
        }
    }
    else {
        // not found
        return Course();
    }
}

vector<string> Courses::splitString(const string input, const string delimiter) const {
    string temp = input;
    size_t pos = 0;
    string token;
    vector<string> returnValue;

    while ((pos = temp.find(delimiter)) != std::string::npos) {
        token = temp.substr(0, pos);             // get token from input
        returnValue.push_back(token);            // add value to vector
        temp.erase(0, pos + delimiter.length()); // remove the part we found and leave the unfound for next call to find
    }

    if (temp.length() > 0) {
        returnValue.push_back(temp);            // add last value to vector
    }

    return returnValue;
}
