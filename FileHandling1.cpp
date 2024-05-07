// ps 20

#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;

class Student
{
    int roll;
    char name[20];
    int div;
    char address[20];

public:
    Student()
    {
        strcpy(name, "");
        strcpy(address, "");
        roll = div = 0;
    }
    Student(int roll, int div, char name[20], char address[20])
    {
        this->roll = roll;
        this->div = div;
        strcpy(this->name, name);
        strcpy(this->address, address);
    }
    int getroll()
    {
        return roll;
    }
    void displayRecord()
    {
        // cout <<setw(5)<< roll << setw(5) << name << setw(5) << div << setw(5) << address<<setw(5) << endl;
        cout << setw(5) << roll << setw(10) << name << setw(10) << div << setw(10) << address << endl;
    }
};

class FileOperations
{
    fstream file;

public:
    FileOperations(char *filename)
    {
        file.open(filename, ios::in | ios::out | ios::binary|ios::app);
    }
    void insert(char name[20], int roll, int div, char address[20])
    {

        Student s(roll, div, name, address);
        file.seekp(0, ios::end);
        file.write((char *)&s, sizeof(Student));

        cout << "data inserted successfully !!!" << endl;
    }
    void displayAll()
    {
        Student s;
        file.seekg(0,ios::beg);
            while (file.read((char*)&s,sizeof(Student)))
            {
                s.displayRecord();
            }
            file.clear();
            
        
    }
    void displayRecord(int roll)
    {
        Student s;
        file.seekg(0, ios::beg);
        bool flag = false;
        while (file.read((char *)&s, sizeof(Student)))
        {
            if (s.getroll() == roll)
            {
                s.displayRecord();
                flag = true;
                break;
            }
        }
        if (flag == false)
        {
            cout << "record of " << roll << " not found" << endl;
        }
        file.clear();
    }
   void deleteRecord(int roll){
    ofstream outfile("new.dat",ios::binary); // Create a new file to store non-deleted records
    file.seekg(0,ios::beg);
    bool flag=false;
    Student s;
    
    while (file.read((char *)&s,sizeof(Student)))
    {
        if (s.getroll()==roll)
        {
            flag=true;
            continue; // Skip writing the record to the new file if it matches the roll
        }
        outfile.write((char*)&s,sizeof(Student)); // Write the record to the new file
            
    }
    if (flag)
    {
        cout<<"record deleted successfully !! "<<endl;
    }
    
    if (!flag)
    {
        cout << "record of " << roll << " not found" << endl;
    }
    
    file.close(); // Close the original file
    outfile.close(); // Close the new file
    
    remove("student.dat"); // Delete the original file
    rename("new.dat","student.dat"); // Rename the new file to the original filename
    file.open("student.dat", ios::in | ios::out | ios::binary | ios::app); // Reopen the file in appropriate mode
}

};
int main()
{
    FileOperations file((char *)"student.dat");
    int choice;
    int roll, div;
    char name[20];
    char address[20];
    while (true)
    {
        cout << "1->add new record" << endl;
        cout << "2->display all records" << endl;
        cout<<"3->search single record"<<endl;
        cout<<"4->delete record"<<endl;
        cout << "5->exit" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "enter name " << endl;
            cin >> name;
            cout << "enter roll" << endl;
            cin >> roll;
            cout << "enter div" << endl;
            cin >> div;
            cout << "enter address" << endl;
            cin >> address;

            file.insert(name, roll, div, address);
        }
        if (choice == 2)
        {
           
            cout << setw(5) << "Roll" << setw(10) << "Name" << setw(10) << "Div" << setw(10) << "Address" << endl;
            file.displayAll();
        }
        if (choice==3)
        {
            cout<<"enter roll"<<endl;
            cin>>roll;
            file.displayRecord(roll);
        }
        if (choice==4)
        {
            cout<<"enter roll"<<endl;
            cin>>roll;
            file.deleteRecord(roll);
            
        }
        if (choice==5)
        
        {
            cout<<"exited........";
            break;
        }
        
        
    }

    return 0;
}