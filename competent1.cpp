#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Task {
    string title;
    bool done;

public:
    Task() : done(0) {}

    Task(string t, bool d) : title(t), done(d) {}

    void input() {
        cout << "Task: ";
        cin.ignore();
        getline(cin, title);
    }

    void display() {
        cout << title << "\t";
        cout << ((done) ? "[Done]" : "[Pending]") << endl;
    }

    void completeTask() { done = 1; }

    //getters
    string getTitle() const { return title; }
    bool getDone() const { return done; }
};

vector<Task> tasks;

void addTask() {
    Task t;
    t.input();
    tasks.push_back(t);
}

void showTasks() {
    cout << "\n-------Tasks-------\n";
    for (int i = 0; i < tasks.size(); i++) { 
        cout << i+1 << ". ";
        tasks[i].display(); 
    }
}

void deleteTask() {
    int no;
    cout << "Enter task no. to be deleted: ";
    cin >> no;
    if (no < 1 || no > tasks.size()) {
        cout << "Invalid Task number!\n";
    }
    else {
        tasks.erase(tasks.begin() + no - 1);
        cout << "Task deleted successfully!";
    }

}

void markCompleted() {
    int no;
    cout << "Enter task number: ";
    cin >> no;

    if (no < 1 || no > tasks.size()) { cout << "Invalid task number!\n"; }

    else {
        tasks[no - 1].completeTask();
        cout << "Task marked complete!\n";
    }
}


void saveTasks() {
    ofstream fout("tasks.txt");

    for (int i = 0; i < tasks.size(); i++) {
        fout << tasks[i].getTitle() << "|" << tasks[i].getDone() << endl;
    }

    fout.close();
    cout << "Tasks saved successfully!\n";
}

void loadTasks() {
    ifstream fin("tasks.txt");

    if (!fin) {
        cout << "No saved file found!\n";
        return;
    }

    tasks.clear();

    string line;
    while (getline(fin, line)) {
        int pos = line.find("|");

        string title = line.substr(0, pos);
        bool done = stoi(line.substr(pos + 1));

        tasks.push_back(Task(title, done));
    }

    cout << "Tasks loaded successfully!\n";
}

int main() {
    int ch = 0;
    while (ch != 6) {
        cout << "\n---------Task Manager--------\n";
        cout << "\n1. Add Task\n2. Show Task\n3. Delete Task\n4. Complete Task\n5. Load Tasks\n6. Exit\n";
        cout << "Enter choice: ";    
        cin >> ch;
    
        if (ch < 1 || ch > 6) cout << "Invalid choice!";

        else if (ch == 1) { addTask(); } 
        else if (ch == 2) { 
            if (tasks.size() < 1) { cout << "No tasks entered!\n"; }
            else showTasks(); }
        else if (ch == 3) { deleteTask(); }
        else if (ch == 4) { markCompleted(); }
        else if (ch == 5) {loadTasks(); }
        else { 
            saveTasks();
            cout << "\nExited successfully!\n"; 
        }
    }

    return 0;
}