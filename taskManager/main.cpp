#include <iostream>
#include <vector>
using namespace std;

// Task Class
class Task {
public:
    int id;
    string title;
    string description;
    string status; // "TODO", "IN_PROGRESS", "COMPLETED"

    Task(int id, string title, string description) {
        this->id = id;
        this->title = title;
        this->description = description;
        this->status = "TODO"; // Default status
    }

    void updateStatus(string newStatus) {
        this->status = newStatus;
    }

    void display() const { // ✅ Add 'const' here to avoid error
        cout << "ID: " << id << ", Title: " << title << ", Status: " << status << "\n";
        cout << "Description: " << description << "\n";
    }
};

// Task Manager Class
class TaskManager {
private:
    vector<Task> tasks;
    int taskCounter = 1; // To assign unique IDs

public:
    void addTask(string title, string description) {
        tasks.push_back(Task(taskCounter++, title, description));
        cout << "Task added successfully!\n";
    }

    void updateTask(int id, string newStatus) {
        for (auto &task : tasks) {
            if (task.id == id) {
                task.updateStatus(newStatus);
                cout << "Task updated successfully!\n";
                return;
            }
        }
        cout << "Task not found!\n";
    }

    void deleteTask(int id) {
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == id) {
                tasks.erase(it);
                cout << "Task deleted successfully!\n";
                return;
            }
        }
        cout << "Task not found!\n";
    }

    void viewTasks() const { // ✅ Make this function 'const' as well
        if (tasks.empty()) {
            cout << "No tasks available!\n";
            return;
        }
        for (const auto &task : tasks) { // ✅ 'const' added
            task.display();
            cout << "----------------------\n";
        }
    }
};

int main() {
    TaskManager taskManager;
    int choice;

    while (true) {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n";
        cout << "2. Update Task Status\n";
        cout << "3. Delete Task\n";
        cout << "4. View All Tasks\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string title, description;
            cout << "Enter Task Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Task Description: ";
            getline(cin, description);
            taskManager.addTask(title, description);
        } 
        else if (choice == 2) {
            int id;
            string status;
            cout << "Enter Task ID: ";
            cin >> id;
            cout << "Enter New Status (TODO, IN_PROGRESS, COMPLETED): ";
            cin >> status;
            taskManager.updateTask(id, status);
        } 
        else if (choice == 3) {
            int id;
            cout << "Enter Task ID to delete: ";
            cin >> id;
            taskManager.deleteTask(id);
        } 
        else if (choice == 4) {
            taskManager.viewTasks();
        } 
        else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } 
        else {
            cout << "Invalid choice, try again!\n";
        }
    }

    return 0;
}
