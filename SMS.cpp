#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Student {
protected:
    int rollno, age;
    string name;

public:
    Student(int stdId, string stdName, int stdAge) : rollno(stdId), name(stdName), age(stdAge) {}

    void setRollno(int stdId) { rollno = stdId; }
    int getRollno() const { return rollno; }

    void setName(const string& stdName) { name = stdName; }
    const string& getName() const { return name; }

    void setAge(int stdAge) { age = stdAge; }
    int getAge() const { return age; }

    virtual void displayDetails() const {
        cout << "Student Number : " << rollno << endl;
        cout << "Name           : " << name << endl;
        cout << "Age            : " << age << endl;
    }

    virtual ~Student() {}
};

class GraduateStudent : public Student {
private:
    string thesisTopic;

public:
    GraduateStudent(int stdId, string stdName, int stdAge, string topic)
        : Student(stdId, stdName, stdAge), thesisTopic(topic) {}

    void setThesisTopic(const string& topic) { thesisTopic = topic; }
    const string& getThesisTopic() const { return thesisTopic; }

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Thesis Topic: " << thesisTopic << endl;
    }
    void research() const {
        cout << "Performed Research In The Field Of: " << thesisTopic << endl;
        }

   
    ~GraduateStudent() override {}
};

void updateStudent(vector<Student*>& students) {
    string sname;
    cout << "\t\tEnter Name to Update Record :";
    cin.ignore();
    getline(cin, sname);

    auto it = find_if(students.begin(), students.end(), [&sname](const Student* s) {
        return s->getName() == sname;
    });

    if (it != students.end()) {
        cout << "\t\t---Student Found -----"<< endl;
        cout << "\t\t 1. Update Student Number " << endl;
        cout << "\t\t 2. Update Name " << endl;
        cout << "\t\t 3. Update Age " << endl;

        int choice;
        cout << "\t\tEnter Your Choice :";
        cin >> choice;

        switch (choice) {
            case 1: {
                int rno;
                cout << "\t\tEnter New Student Number :";
                cin >> rno;
                (*it)->setRollno(rno);
                break;
            }
            case 2: {
                string name;
                cout << "\t\tEnter New Name :";
                cin.ignore();
                getline(cin, name);
                (*it)->setName(name);
                break;
            }
            case 3: {
                int age;
                cout << "\t\tEnter New Age :";
                cin >> age;
                (*it)->setAge(age);
                break;
            }
            default:
                cout << "\t\tInvalid Number" << endl;
        }
    } else {
        cout << "\t\tRecord Not Found" << endl;
    }
}

void displayAllStudents(const vector<Student*>& students) {
    if (students.empty()) {
        cout << "\t\t No Student Found " << endl;
    } else {
        for (const auto& student : students) {
            student->displayDetails();
            cout << endl;
        }
    }
}

void deleteStudent(vector<Student*>& students) {
    string name;
    cout << "Enter Name to Delete :";
    cin.ignore();
    getline(cin, name);

    auto it = remove_if(students.begin(), students.end(), [&name](const Student* s) {
        return s->getName() == name;
    });

    if (it != students.end()) {
        delete *it;  // Release memory for the deleted object
        students.erase(it, students.end());
        cout << "\t\tStudent Removed Successfully" << endl;
    } else {
        cout << "\t\tStudent Not Found" << endl;
    }
}

void searchStudent(const vector<Student*>& students) {
    int rollno;
    cout << "\t\tEnter Student Number :";
    cin >> rollno;

    auto it = find_if(students.begin(), students.end(), [rollno](const Student* s) {
        return s->getRollno() == rollno;
    });

    if (it != students.end()) {
        cout << "\t\t--------Student Found ------------" << endl;
        (*it)->displayDetails();
        if (auto graduateStudent = dynamic_cast<GraduateStudent*>(*it)) {
            graduateStudent->research();
        }
    
    } else {
        cout << "\t\tRecord Not Found" << endl;
    }
}

void addNewStudent(vector<Student*>& students) {
    int studentType;
    cout << "\t\t 1. Undergraduate Student" << endl;
    cout << "\t\t 2. Graduate Student" << endl;
    cout << "\t\t Enter Student Type : ";
    cin >> studentType;

    int rollno, age;
    string name;
    string thesisTopic;

    cout << "\t\t Enter Student Number :";
    cin >> rollno;

    auto it = find_if(students.begin(), students.end(), [rollno](const Student* s) {
        return s->getRollno() == rollno;
    });

    if (it != students.end()) {
        cout << "\t\t Student Already Exists" << endl;
        return;
    }

    cout << "\t\t Enter Name : ";
    cin.ignore();
    getline(cin, name);
    cout << "\t\t Enter Age : ";
    cin >> age;

    if (studentType == 1) {
        students.push_back(new Student(rollno, name, age));
    } else if (studentType == 2) {
        cout << "\t\t Enter Thesis Topic : ";
        cin.ignore();
        getline(cin, thesisTopic);
        students.push_back(new GraduateStudent(rollno, name, age, thesisTopic));
    } else {
        cout << "\t\t Invalid Student Type" << endl;
    }

    cout << "\t\tStudent Added Successfully" << endl;
}

int main() {
    vector<Student*> students;

    char choice;

    do {
        system("cls");

        cout << "\n\t\t--------------------------------";
        cout << "\n\t\t*** Student Management System ***";
        cout << "\n\t\t--------------------------------";
        cout << "\n\t\t 1. Add New Student" << endl;
        cout << "\t\t 2. Display All Students " << endl;
        cout << "\t\t 3. Search For Students" << endl;
        cout << "\t\t 4. Update Students" << endl;
        cout << "\t\t 5. Delete Students " << endl;
        cout << "\t\t 6. Exit" << endl;
        cout << "\t\t What Do You Want To Do?   : ";

        int op;
        cin >> op;

        switch (op) {
            case 1:
                addNewStudent(students);
                break;
            case 2:
                displayAllStudents(students);
                break;
            case 3:
                searchStudent(students);
                break;
            case 4:
                updateStudent(students);
                break;
            case 5:
                deleteStudent(students);
                break;
            case 6:
                // Clean up dynamically allocated memory
                for (const auto& student : students) {
                    delete student;
                }
                return 0;
            default:
                cout << "\t\tInvalid Number " << endl;
        }

        cout << "\t\tDo You Want To Continue Using The Program [Yes/No] ? :";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
