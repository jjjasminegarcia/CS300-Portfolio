// ============================================================================
// Name        - CS 300 - ProjectTwo.cpp
// Author      - Jasmine Garcia - July 2025
// Description - ABCU Advising Program
// ============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// define structure to hold course info
struct Course {
    string courseId;
    string courseName;
    vector<string> prerequisites;
};

// define  Binary Search Tree class
class BinarySearchTree {
private:
    struct Node {
        Course course;
        Node* left;
        Node* right;

        Node(Course aCourse) {
            this->course = aCourse;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    Node* root;

    void addNode(Node* node, Course course) {
        if (course.courseId < node->course.courseId) {
            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                addNode(node->left, course);
            }
        }
        else {
            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                addNode(node->right, course);
            }
        }
    }

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseId << ", " << node->course.courseName << endl;
            inOrder(node->right);
        }
    }

    Course search(Node* node, string courseId) {
        if (node == nullptr) {
            return Course();
        }
        if (node->course.courseId == courseId) {
            return node->course;
        }
        if (courseId < node->course.courseId) {
            return search(node->left, courseId);
        }
        else {
            return search(node->right, courseId);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void Insert(Course course) {
        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            addNode(root, course);
        }
    }

    void PrintAll() {
        inOrder(root);
    }

    Course Search(string courseId) {
        return search(root, courseId);
    }
};

// Function to split a string by commas
vector<string> split(const string& line, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(line);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Load courses from CSV file
void loadCourses(string fileName, BinarySearchTree* bst) {
    ifstream file(fileName);
    string line;

    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        Course course;
        if (tokens.size() >= 2) {
            course.courseId = tokens[0];
            course.courseName = tokens[1];
            for (size_t i = 2; i < tokens.size(); ++i) {
                course.prerequisites.push_back(tokens[i]);
            }
            bst->Insert(course);
        }
    }

    file.close();
}

// display the course details
void displayCourse(Course course) {
    cout << course.courseId << ", " << course.courseName << endl;
    cout << "Prerequisites: ";
    if (course.prerequisites.empty()) {
        cout << "None";
    }
    else {
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
    }
    cout << endl;
}

// MAIN FUNCTION
int main() {
    BinarySearchTree courseTree;
    Course course;
    string fileName;
    string courseId;
    int choice = 0;

    while (choice != 9) {
        cout << "\nMenu:\n";
        cout << "  1. Load Courses\n";
        cout << "  2. Print All Courses Alphabetically\n";
        cout << "  3. Search for a Course\n";
        cout << "  9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter course file name to load (e.g., CS_300_ABCU_Advising_Program_Input.csv): ";
            cin >> fileName;
            loadCourses(fileName, &courseTree);
            break;
        case 2:
            cout << "\nAll Courses:\n";
            courseTree.PrintAll();
            break;
        case 3:
            cout << "Enter course ID to search: ";
            cin >> courseId;
            course = courseTree.Search(courseId);
            if (course.courseId.empty()) {
                cout << "Course not found.\n";
            }
            else {
                displayCourse(course);
            }
            break;
        case 9:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please enter 1, 2, 3, or 9.\n";
        }
    }
    return 0;
}