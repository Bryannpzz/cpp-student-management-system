#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Student {
private:
    string name;
    int age;

public:
    Student(string n, int a) : name(n), age(a) {}

    string getName() const { return name; }
    int getAge() const { return age; }
};

// Clears bad input so the menu doesn’t get stuck
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        clearInput(); // remove leftover newline
        return value;
    }
}

string readLine(const string& prompt) {
    string text;
    cout << prompt;
    getline(cin, text);
    return text;
}

void addStudent(vector<Student>& students) {
    string name = readLine("Enter student name: ");

    int age;
    while (true) {
        age = readInt("Enter student age: ");
        if (age <= 0 || age > 120) {
            cout << "Please enter a valid age (1-120).\n";
        } else {
            break;
        }
    }

    students.push_back(Student(name, age));
    cout << "Student added!\n";
}

void listStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    cout << "\n--- Student List ---\n";
    for (int i = 0; i < (int)students.size(); i++) {
        cout << (i + 1) << ") " << students[i].getName()
             << " (Age: " << students[i].getAge() << ")\n";
    }
}

void showMenu() {
    cout << "\n===== Student Management Menu =====\n";
    cout << "1) Add student\n";
    cout << "2) List students\n";
    cout << "3) Exit\n";
}

int main() {
    vector<Student> students;

    while (true) {
        showMenu();
        int choice = readInt("Choose an option: ");

        if (choice == 1) {
            addStudent(students);
        } else if (choice == 2) {
            listStudents(students);
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
