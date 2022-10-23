//
//  Course.cpp
//  CourseSort
//
//  Created by Ashley De Venuto on 10/22/22.
//

#include "Course.hpp"

void Course::print() const {
    cout << id << ", " << title;

    // check id prerequisites are on display
    if (prerequisites.size() > 0) {
        cout << endl << "Prerequisites: ";

        // display all
        for (size_t i = 0; i < prerequisites.size(); ++i) {
            cout << prerequisites.at(i).getId();

            // if before last, add delimiter
            if (i + 1 < prerequisites.size()) {
                cout << ", ";
            }
        }
    }

    cout << endl;
}
