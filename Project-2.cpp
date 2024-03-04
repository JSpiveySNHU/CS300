#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

//Jim Spivey
//3-3-24

using namespace std;

vector<vector<string>> courses; // Create the vector to hold courses
string loadMsg = "This file is not loaded yet. Please run option 1 first.";

void loadVector() {
    string inputFile;
    cout << "Enter location of input file" << endl;
    cin >> inputFile;

    ifstream file(inputFile); // Open the file

    if (!file.is_open()) {
        cerr << "Could not open the file - '" << inputFile << "'" << endl;
        return; // Exit the function if the file cannot be opened
    }

    string line;
    while (getline(file, line)) { // Reading line to line
        istringstream s(line);
        string field;
        vector<string> row;

        while (getline(s, field, ',')) { // Split line by commas
            row.push_back(field); // Add each field to the 'row' vector
        }

        courses.push_back(row); // Add the row to the 'courses' vector
    }

    file.close(); // Close the file
    cout << "File loaded successfully" << endl;
}

void printCourseList() {
    // Sort the courses in alphanumeric order by course number
    sort(courses.begin(), courses.end(), [](const vector<string>& a, const vector<string>& b) {
        return a[0] < b[0]; // Assuming the course number is the first element
        });

    for (const auto& course : courses) {
        if (course.size() >= 2) { // Ensure there's at least a course number and title
            cout << course[0] << ", " << course[1] << endl; // Print only course number and title
        }
    }
}

void printCourse() {
    cout << "Enter the course ID to print: ";
    string courseId;
    cin >> courseId;

    // Find the course by ID
    bool found = false;
    for (const auto& course : courses) {
        if (course.size() >= 2 && course[0] == courseId) { // Check if course ID matches
            cout << "Course: " << course[0] << " - " << course[1] << endl; // Course ID and Name
            cout << "Prerequisites: ";
            if (course.size() > 2) { // Check if there are prerequisites
                for (size_t i = 2; i < course.size(); ++i) {
                    cout << course[i];
                    if (i < course.size() - 1) cout << ", "; 
                }
            }
            else {
                cout << "None";
            }
            cout << endl;
            found = true;
            break; // Exit the loop once the course is found
        }
    }

    if (!found) {
        cout << "Course ID '" << courseId << "' not found." << endl;
    }
}

int main() {
    int choice = 0;
    bool isLoaded = false;
    bool exit = false;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;



        if (choice != 1 && choice != 2 && choice != 3 && choice != 9) {
            cout << choice << " is not a valid option." << endl;
            break;
        }

        switch (choice) {
        case 1:
            loadVector();
            isLoaded = true;
            break;
        case 2:
            if (isLoaded) {
                printCourseList();
                break;
            }
            else {
                cout << loadMsg << endl;
                break;
            }
        case 3:
            if (isLoaded) {
                printCourse();
                break;
            }
            else {
                cout << loadMsg << endl;
                break;
            }
        }
    }
    cout << "Thank you for using the course planner!" << endl;

    return 0;
}
