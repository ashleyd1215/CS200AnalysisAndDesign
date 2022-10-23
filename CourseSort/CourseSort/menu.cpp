//
//  menu.cpp
//  CourseSort
//
//  Created by Ashley De Venuto on 10/23/22.
//

#include "menu.hpp"
#include "Course.hpp"
#include "CourseList.hpp"

/// Print menu options
void printMenu(void) {
    cout << "Menu:" << endl;
    cout << "  1. Load Data Structure." << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl << endl;
    cout << "What would you like to do? ";
}

/// Calls functions based on choise user makes.
void handleChoice(int choice, Courses& courses) {
    switch (choice) {
    case 1: // load file
        {
            string filename;
            auto state = cin.exceptions();  // create exception handling
            cin.exceptions(std::istream::failbit | state);
            cout << "Please enter the name of the data file to load." << endl;
            cin.ignore();

            // if loaded already discard and start over
            if (courses.getSize() > 0) {
                courses.clear();
            }

            try {
                getline(cin, filename);     // get user input of filename
                courses.loadFromCSV(filename);
            }
            catch (exception ex) {
                cout << ex.what() << endl;  // display what happened to console
            }

            cin.exceptions(state);          // restore previous exception settings
        }
        break;

    case 2: // print courses id and title in alphanumeric order
        cout << "Here is a sample schedule:" << endl << endl;
        courses.printAll();
        break;

    case 3: // print course and its prerequisites
        {
            string courseId;
            cout << "What course do you want to know about? ";
            cin >> courseId;
            courses.printCourse(courseId);
        }
        break;

    case 9: // exit program
        cout << "Thank you for using the course planner!" << endl;
        break;

    default: // invalid choice
        cout << choice << "is not a valid option." << endl << endl;
        break;
    }
}

void commandLoop(void) {
    int choice = 0;
    Courses courses; // declares and allocates memory of lifetime for loop

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) { // while not exit command
        cout << endl;
        printMenu();
        cin >> choice; // wait for user input
        handleChoice(choice, courses);
    }
}
