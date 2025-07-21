#include <bits/stdc++.h>
using namespace std;

class Task {
    string taskName;
    string taskDetails;
    string taskDate; // Format: yyyy-mm-dd
    bool isDone;
    string assignedTo;

public:
    Task(string name, string details, string d, string assign = "Unassigned") {
        taskName = name;
        taskDetails = details;
        taskDate = d;
        isDone = false;
        assignedTo = assign;
    }

    string getName() const { return taskName; }
    string getDetails() const { return taskDetails; }
    string getDate() const { return taskDate; }
    bool getStatus() const { return isDone; }
    string getAssignedTo() const { return assignedTo; }

    void updateStatus() { isDone = !isDone; }
    void setDetails(const string& newDetails) { taskDetails = newDetails; }
    void setDate(const string& newDate) { taskDate = newDate; }
    void setAssignedTo(const string& assign) { assignedTo = assign; }
};

class TaskManager {
    vector<Task> taskList;

    bool isValidDate(const string& date) {
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        if (year < 2025 || month < 1 || month > 12 || day < 1 || day > 31) return false;
        return true;
    }

public:
    void addTask() {
        string name, details, date, assign;
        cout << "Enter task name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter task details: ";
        getline(cin, details);
        cout << "Enter date (yyyy-mm-dd): ";
        cin >> date;
        if (!isValidDate(date)) {
            cout << "Invalid date format!" << endl;
            return;
        }
        cout << "Assign to (press Enter for Unassigned): ";
        cin.ignore();
        getline(cin, assign);
        if (assign.empty()) assign = "Unassigned";

        taskList.emplace_back(name, details, date, assign);
        cout << "Task added successfully!" << endl;
        checkClash(date);
    }

    void displayTasks() {
        if (taskList.empty()) {
            cout << "No tasks available..." << endl;
            return;
        }
        int i = 1;
        for (auto& t : taskList) {
            cout << i++ << ". " << t.getName() << " - " << t.getDetails()
                 << " (Date: " << t.getDate() << ", Assigned to: " << t.getAssignedTo() << ")"
                 << (t.getStatus() ? " [Done]" : "") << endl;
        }
    }

    void markTaskDone() {
        displayTasks();
        int index;
        cout << "Enter task number to toggle done (0 to cancel): ";
        cin >> index;
        if (index <= 0 || index > taskList.size()) return;
        taskList[index - 1].updateStatus();
        cout << "Task status updated!" << endl;
    }

    void removeTask() {
        displayTasks();
        int index;
        cout << "Enter task number to delete (0 to cancel): ";
        cin >> index;
        if (index <= 0 || index > taskList.size()) return;
        taskList.erase(taskList.begin() + index - 1);
        cout << "Task deleted!" << endl;
    }

    void showCompletedTasks() {
        int count = 1;
        for (auto& t : taskList) {
            if (t.getStatus()) {
                cout << count++ << ". " << t.getName() << " - " << t.getDetails()
                     << " (Date: " << t.getDate() << ", Assigned to: " << t.getAssignedTo() << ")" << endl;
            }
        }
        if (count == 1) cout << "No completed tasks found." << endl;
    }

    void editTask() {
        displayTasks();
        int index;
        cout << "Enter task number to edit (0 to cancel): ";
        cin >> index;
        if (index <= 0 || index > taskList.size()) return;

        Task& t = taskList[index - 1];
        string newDetails, newDate, newAssign;

        cout << "Enter new details: ";
        cin.ignore();
        getline(cin, newDetails);
        cout << "Enter new date (yyyy-mm-dd): ";
        cin >> newDate;
        if (!isValidDate(newDate)) {
            cout << "Invalid date format!" << endl;
            return;
        }
        cout << "Assign to (press Enter to keep current): ";
        cin.ignore();
        getline(cin, newAssign);
        if (newAssign.empty()) newAssign = t.getAssignedTo();

        t.setDetails(newDetails);
        t.setDate(newDate);
        t.setAssignedTo(newAssign);
        cout << "Task updated successfully!" << endl;
        checkClash(newDate);
    }

    void checkClash(const string& date) {
        int count = 0;
        for (auto& t : taskList) {
            if (t.getDate() == date && !t.getStatus()) {
                if (count == 0)
                    cout << "Warning: Clashing tasks on " << date << ":\n";
                cout << "- " << t.getName() << " (Assigned to: " << t.getAssignedTo() << ")\n";
                count++;
            }
        }
        if (count > 1) cout << "Total clashing tasks: " << count << endl;
    }
};

int main() {
    TaskManager tm;
    cout << "Task Manager started at 10:37 PM IST, Monday, July 21, 2025\n";

    while (true) {
        cout << "\n=== My Awesome Task Manager ===\n";
        cout << "1. Add a new task\n";
        cout << "2. Show all tasks\n";
        cout << "3. Mark a task as done\n";
        cout << "4. Delete a task\n";
        cout << "5. Show completed tasks\n";
        cout << "6. Edit a task\n";
        cout << "7. Check for clashing events\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: tm.addTask(); break;
            case 2: tm.displayTasks(); break;
            case 3: tm.markTaskDone(); break;
            case 4: tm.removeTask(); break;
            case 5: tm.showCompletedTasks(); break;
            case 6: tm.editTask(); break;
            case 7: {
                string date;
                cout << "Enter date to check (yyyy-mm-dd): ";
                cin >> date;
                tm.checkClash(date);
                break;
            }
            case 8:
                cout << "Thanks for using My Task Manager. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice, try again!" << endl;
        }
    }
}
