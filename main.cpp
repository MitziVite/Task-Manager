#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


// Task class
class Task {
private:
    std::string title;
    std::string description;
    std::string deadline;
    int priority;
    std::string status;

public:
    // Constructor that initializes a task with the given values
    Task(std::string t, std::string d, std::string dl, int p, std::string s)
        : title(t), description(d), deadline(dl), priority(p), status(s) {}

    // Getters
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getDeadline() const { return deadline; }
    int getPriority() const { return priority; }
    std::string getStatus() const { return status; }

    // Setters
    void setTitle(std::string t) { title = t; }
    void setDescription(std::string d) { description = d; }
    void setDeadline(std::string dl) { deadline = dl; }
    void setPriority(int p) { priority = p; }
    void setStatus(std::string s) { status = s; }

    // Show details of the task
    void displayTask() const {
        std::cout << "Title: " << title << "\nDescription: " << description
                  << "\nDeadline: " << deadline << "\nPriority: " << priority
                  << "\nStatus: " << status << std::endl;
    }
};


// Displays the menu options for the task management system
void displayMenu() {
    std::cout << "Task Management System\n";
    std::cout << "1. Create Task\n";
    std::cout << "2. Edit Task\n";
    std::cout << "3. Delete Task\n";
    std::cout << "4. List Tasks\n";
    std::cout << "5. Save Tasks\n";
    std::cout << "6. Load Tasks\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

// Saves the tasks to a file
void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file("task.txt");
    if (!file) {
        std::cerr << "Error opening file for saving tasks!" << std::endl;
        return;
    }
    for (const auto& task : tasks) {
        file << task.getTitle() << "," << task.getDescription() << ","
             << task.getDeadline() << "," << task.getPriority() << ","
             << task.getStatus() << std::endl;
    }
    file.close();
}


// Loads the tasks from a file
void loadTasks(std::vector<Task>& tasks) {
    std::ifstream file("task.txt");
    if (!file) {
        std::cerr << "Error opening file for loading tasks!" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string title, description, deadline, status;
        int priority;
        std::getline(ss, title, ',');
        std::getline(ss, description, ',');
        std::getline(ss, deadline, ',');
        ss >> priority;
        ss.ignore(1, ',');
        std::getline(ss, status);

        tasks.push_back(Task(title, description, deadline, priority, status));
    }
    file.close();
}


int main() {
    std::vector<Task> tasks;
    int choice;

    loadTasks(tasks);

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Create task
                std::string title, description, deadline, status;
                int priority;

                std::cout << "Enter title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter description: ";
                std::getline(std::cin, description);
                std::cout << "Enter deadline (YYYY-MM-DD): ";
                std::getline(std::cin, deadline);
                std::cout << "Enter priority (1: High, 2: Medium, 3: Low): ";
                std::cin >> priority;
                std::cout << "Enter status (pending, in progress, completed): ";
                std::cin.ignore(); 
                std::getline(std::cin, status);

                tasks.push_back(Task(title, description, deadline, priority, status));
                std::cout << "Task created successfully!\n";
                break;
            }
            case 2: {
                // Edit task
                int taskNumber;
                std::cout << "Enter task number to edit: ";
                std::cin >> taskNumber;

                if (taskNumber < 1 || taskNumber > tasks.size()) {
                    std::cout << "Invalid task number!\n";
                } else {
                    std::string title, description, deadline, status;
                    int priority;

                    std::cout << "Enter new title: ";
                    std::cin.ignore(); 
                    std::getline(std::cin, title);
                    std::cout << "Enter new description: ";
                    std::getline(std::cin, description);
                    std::cout << "Enter new deadline (YYYY-MM-DD): ";
                    std::getline(std::cin, deadline);
                    std::cout << "Enter new priority (1: High, 2: Medium, 3: Low): ";
                    std::cin >> priority;
                    std::cout << "Enter new status (pending, in progress, completed): ";
                    std::cin.ignore();
                    std::getline(std::cin, status);

                    tasks[taskNumber - 1].setTitle(title);
                    tasks[taskNumber - 1].setDescription(description);
                    tasks[taskNumber - 1].setDeadline(deadline);
                    tasks[taskNumber - 1].setPriority(priority);
                    tasks[taskNumber - 1].setStatus(status);
                    std::cout << "Task updated successfully!\n";
                }
                break;
            }
            case 3: {
                // Delete Task
                int taskNumber;
                std::cout << "Enter task number to delete: ";
                std::cin >> taskNumber;

                if (taskNumber < 1 || taskNumber > tasks.size()) {
                    std::cout << "Invalid task number!\n";
                } else {
                    tasks.erase(tasks.begin() + (taskNumber - 1));
                    std::cout << "Task deleted successfully!\n";
                }
                break;
            }
            case 4: {
                // List tasks
                for (size_t i = 0; i < tasks.size(); ++i) {
                    std::cout << "Task " << (i + 1) << ":\n";
                    tasks[i].displayTask();
                    std::cout << std::endl;
                }
                break;
            }
            case 5: {
                // Save tasks
                saveTasks(tasks);
                std::cout << "Tasks saved successfully!\n";
                break;
            }
            case 6: {
                // Load tasks
                loadTasks(tasks);
                std::cout << "Tasks loaded successfully!\n";
                break;
            }
            case 7: {
                // Exit
                std::cout << "Exiting program.\n";
                break;
            }
            default: {
                std::cout << "Invalid choice! Please try again.\n";
                break;
            }
        }
    } while (choice != 7);

    return 0;
}