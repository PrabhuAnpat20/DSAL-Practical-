// ps 26

#include <iostream>
#include <fstream>
#include <cstring>
#define SIZE 10

using namespace std;

class Student
{
public:
    int roll;
    char name[20];

    Student()
    {
        roll = 0;
        strcpy(name, "");
    }

    Student(int roll, const char name[20])
    {
        this->roll = roll;
        strcpy(this->name, name);
    }

    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Roll: " << roll << endl;
    }
};

class DAFile
{
private:
    fstream file;

public:
    DAFile(const char *filename)
    {
        file.open(filename, ios::in | ios::out | ios::binary);
    }

    int getHash(int roll)
    {
        return roll % SIZE;
    }

    void insert(const char name[20], int roll)
    {
        Student s(roll, name);
        int hash = getHash(roll);
        file.seekp(hash * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<char *>(&s), sizeof(Student));
        cout << "Data inserted successfully!!!" << endl;
    }

    void Display(int roll)
    {
        Student s;
        int hash = getHash(roll);
        file.seekg(hash * sizeof(Student), ios::beg);
        file.read(reinterpret_cast<char *>(&s), sizeof(Student));
        if (s.roll == roll)
        {
            s.display();
        }
        else
        {
            cout << "Not found!" << endl;
        }
    }
   void Delete(int roll)
{
    int hash = getHash(roll);
    file.seekg(hash * sizeof(Student), ios::beg);
    Student s;
    file.read(reinterpret_cast<char *>(&s), sizeof(Student));
    if (s.roll == roll)
    {
        
        Student s1;
        file.seekp(hash * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<char *>(&s1), sizeof(Student));
        cout << "Record deleted successfully !!" << endl;
        return;
    }
    cout << "Not found!" << endl;
}

};

int main()
{
    int choice;
    char name[20];
    int roll;
    DAFile file("demo3.dat");
    while (true)
    {
        cout << "1 -> Add new record" << endl;
        cout << "2 -> Display record" << endl;
        cout << "3 -> Delete record" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter roll: ";
            cin >> roll;
            file.insert(name, roll);
            break;
        case 2:
            cout << "Enter roll: ";
            cin >> roll;
            file.Display(roll);
            break;
        case 3:
            cout << "Enter roll: ";
            cin >> roll;
            file.Delete(roll);
        default:
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
