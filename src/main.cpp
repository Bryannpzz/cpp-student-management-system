#include <iostream>
#include <vector>
#include <fstream>
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

    string toFileString() const {
        return name + "," + to_string(age);
    }

    static Student fromFileString(const string& line) {
        size_t commaPos = line.find(",");
        string name = line.substr(0, commaPos);
        int age = stoi(line.substr(commaPos + 1));
        return Student(name, age);
    }
};

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

        clearInput();
        return value;
    }
}

string readLine(const string& prompt) {
    string text;
    cout << prompt;
    getline(cin, text);
    return text;
}

void saveStudents(const vector<Student>& students) {
    ofstream file("students.txt");
    for (const Student& s : students) {
        file << s.toFileString() << endl;
    }
}

void loadStudents(vector<Student>& students) {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            students.push_back(Student::fromFileString(line));
        }
    }
}

void addStudent(vector<Student>& students) {
    string name = readLine("Enter student name: ");
    int age = readInt("Enter student age: ");

    students.push_back(Student(name, age));
    saveStudents(students);

    cout << "Student added and saved.\n";
}

void listStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    cout << "\n--- Student List ---\n";
    for (int i = 0; i < (int)students.size(); i++) {
        cout << (i + 1) << ") "
             << students[i].getName()
             << " (Age: " << students[i].getAge() << ")\n";
    }
}

void showMenu() {
    cout << "\n===== Student Management Menu =====\n";
    cout << "1) Add student\n";
    cout << "2) List students\n";
    cout << "3) Exit\n";
}

int main()
