#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Lecture class representing a video lecture
class Lecture {
public:
    string title;
    int duration; // in minutes

    Lecture(const string& t, int d) : title(t), duration(d) {}
};

// Assignment class representing a course assignment
class Assignment {
public:
    string description;
    string dueDate;

    Assignment(const string& desc, const string& due) : description(desc), dueDate(due) {}
};

// Course class representing a course with lectures and assignments
class Course {
public:
    string title;
    string instructor;
    vector<Lecture*> lectures;
    vector<Assignment*> assignments;

    Course(const string& t, const string& instr) : title(t), instructor(instr) {}

    void addLecture(Lecture* lecture) {
        lectures.push_back(lecture);
        cout << "Added Lecture: " << lecture->title << " to " << title << endl;
    }

    void addAssignment(Assignment* assignment) {
        assignments.push_back(assignment);
        cout << "Added Assignment: " << assignment->description << " to " << title << endl;
    }

    void displayDetails() const {
        cout << "\nCourse Title: " << title << "\n";
        cout << "Instructor: " << instructor << "\n";
        cout << "Lectures:\n";
        for (const auto& lecture : lectures) {
            cout << "  - " << lecture->title << " (" << lecture->duration << " minutes)\n";
        }
        cout << "Assignments:\n";
        for (const auto& assignment : assignments) {
            cout << "  - " << assignment->description << " (Due: " << assignment->dueDate << ")\n";
        }
    }
};

// User class representing a user of the platform
class User {
public:
    string name;
    string role; // Student or Instructor
    vector<Course*> enrolledCourses;

    User(const string& n, const string& r) : name(n), role(r) {}

    void enroll(Course* course) {
        enrolledCourses.push_back(course);
        cout << name << " enrolled in " << course->title << endl;
    }

    void displayEnrolledCourses() const {
        if (enrolledCourses.empty()) {
            cout << name << " is not enrolled in any courses.\n";
            return;
        }
        cout << name << "'s enrolled courses:\n";
        for (const auto& course : enrolledCourses) {
            cout << "  - " << course->title << "\n";
        }
    }

    void displayDetails() const{
        cout << "Name: " << name << " | Role: " << role << endl;
    }
};

// LearningPlatform class managing users and courses
class LearningPlatform {
public:
    vector<User*> users;
    vector<Course*> courses;

    void addUser(User* user) {
        users.push_back(user);
        cout << "User " << user->name << " added as " << user->role << endl;
    }

    void addCourse(Course* course) {
        courses.push_back(course);
        cout << "Course " << course->title << " by " << course->instructor << " added" << endl;
    }

    User* findUser(const string& name) {
        for (auto& user : users) {
            if (user->name == name) {
                return user;
            }
        }
        return nullptr;
    }

    Course* findCourse(const string& title) {
        for (auto& course : courses) {
            if (course->title == title) {
                return course;
            }
        }
        return nullptr;
    }

    void displayAllCourses() const {
        if (courses.empty()) {
            cout << "No courses available.\n";
            return;
        }
        for (const auto& course : courses) {
            course->displayDetails();
        }
    }

    void displayAllUsers() const {
        if (users.empty()) {
            cout << "No users available.\n";
            return;
        }
        for (const auto& user : users) {
            user->displayDetails();
        }
    }
};

// Function to display the main menu
void displayMenu() {
    cout << "\n--- Online Learning Platform Menu ---\n";
    cout << "1. Add User\n";
    cout << "2. Add Course\n";
    cout << "3. Add Lecture to Course\n";
    cout << "4. Add Assignment to Course\n";
    cout << "5. Enroll User in Course\n";
    cout << "6. View Courses\n";
    cout << "7. View Users\n";
    cout << "8. View User's Enrolled Courses\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

// Function to add a new user
void addUser(LearningPlatform& platform) {
    string name, role;
    cout << "Enter user name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, name);
    cout << "Enter role (Student/Instructor): ";
    getline(cin, role);
    platform.addUser(new User(name, role));
}

// Function to add a new course
void addCourse(LearningPlatform& platform) {
    string title, instructorName;
    cout << "Enter course title: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, title);
    cout << "Enter instructor name: ";
    getline(cin, instructorName);
    User* instructor = platform.findUser(instructorName);
    if (instructor && instructor->role == "Instructor") {
        platform.addCourse(new Course(title, instructorName));
    } else {
        cout << "Instructor not found or not valid.\n";
    }
}

// Function to add a lecture to a course
void addLectureToCourse(LearningPlatform& platform) {
    string courseTitle, lectureTitle;
    int duration;
    cout << "Enter course title: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, courseTitle);
    Course* course = platform.findCourse(courseTitle);
    if (course) {
        cout << "Enter lecture title: ";
        getline(cin, lectureTitle);
        cout << "Enter lecture duration (in minutes): ";
        cin >> duration;
        course->addLecture(new Lecture(lectureTitle, duration));
    } else {
        cout << "Course not found.\n";
    }
}

// Function to add an assignment to a course
void addAssignmentToCourse(LearningPlatform& platform) {
    string courseTitle, description, dueDate;
    cout << "Enter course title: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, courseTitle);
    Course* course = platform.findCourse(courseTitle);
    if (course) {
        cout << "Enter assignment description: ";
        getline(cin, description);
        cout << "Enter due date (YYYY-MM-DD): ";
        getline(cin, dueDate);
        course->addAssignment(new Assignment(description, dueDate));
    } else {
        cout << "Course not found.\n";
    }
}

// Function to enroll a user in a course
void enrollUserInCourse(LearningPlatform& platform) {
    string userName, courseTitle;
    cout << "Enter user name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, userName);
    User* user = platform.findUser(userName);
    if (user) {
        cout << "Enter course title: ";
        getline(cin, courseTitle);
        Course* course = platform.findCourse(courseTitle);
        if (course) {
            user->enroll(course);
        } else {
            cout << "Course not found.\n";
        }
    } else {
        cout << "User not found.\n";
    }
}

// Function to view a specific user's enrolled courses
void viewUserEnrolledCourses(LearningPlatform& platform) {
    string userName;
    cout << "Enter user name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, userName);
    User* user = platform.findUser(userName);
    if (user) {
        user->displayEnrolledCourses();
    } else {
        cout << "User not found.\n";
    }
}

int main() {
    LearningPlatform platform;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addUser(platform);
                break;
            case 2:
                addCourse(platform);
                break;
            case 3:
                addLectureToCourse(platform);
                break;
            case 4:
                addAssignmentToCourse(platform);
                break;
            case 5:
                enrollUserInCourse(platform);
                break;
            case 6:
                platform.displayAllCourses();
                break;
            case 7:
                platform.displayAllUsers();
                break;
            case 8:
                viewUserEnrolledCourses(platform);
                break;
            case 9:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
