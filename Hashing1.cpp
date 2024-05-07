#include <iostream>
#define size 10
using namespace std;
class Contact
{
    string name;
    string num;
    Contact()
    {
        name = " ";
        num = "";
    }

    friend class Hash;
};

class Hash
{
    Contact *people;

public:
    Hash()
    {
        people = new Contact[size];
        for (int i = 0; i < size; i++)
        {
            people[i] = Contact();
        }
    }
    int getHash(string key)
    {
        int hash = 0;
        for (int i = 0; i < key.length(); i++)
        {
            hash += int(key[i]);
        }
        cout << hash << endl;
        return hash % size;
        // return  ((hash*3+5)+1)%size;
    }

    void insert_without_replacement(string name, string num)
    {
        int hash = getHash(name);

        while (people[hash].name != " " || people[hash].name == name)
        {
            hash = (hash + 1) % size;
        }
        people[hash].name = name;
        people[hash].num = num;
        cout << "inserted" << endl;
    }

    void insert_with_replacement(string name, string num)
    {
        int hash = getHash(name);

        while (people[hash].name != " " || people[hash].name == name)
        {
            int prev = getHash(people[hash].name);
            if (prev != hash)
            {
                // swap
                string temp_name = people[hash].name;
                string temp_num = people[hash].num;

                people[hash].name = name;
                people[hash].num = num;

                name = temp_name;
                num = temp_num;
            }
            hash = (hash + 1) % size;
        }
        people[hash].name = name;
        people[hash].num = num;
        cout << "inserted" << endl;
    }
 void delete_contact(string name) {
        int hash = getHash(name);

        for (int i = 0; i < size; i++) {
            if (people[hash].name == name) {
                people[hash].name = " ";
                people[hash].num = "";
                cout << "Contact Deleted!" << endl;
                return;
            }
            hash = (hash + 1) % size;
             // hash=((hash*3+5)+1)%size;
        }
        cout << "Contact Not Found!!" << endl;
    }
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << i << "->" << people[i].name << "   " << people[i].num << endl;
        }
    }
    void search(string name)
    {
        int count = 0;

        int hash = getHash(name);

        for (int i = 0; i < size; i++)
        {
            count++;
            if (people[hash].name == name)
            {
                cout << "Contact Found! Required Comparisions = " << count << endl;
                cout << "Name: " << people[hash].name << endl;
                cout << "Number: " << people[hash].num << endl;
                return;
            }
            hash = (hash + 1) % size;
            // hash=((hash*3+5)+1)%size;
        }
        cout << "Data Not Found!!" << endl;
        
    }
};
int main()
{

    
    
    Hash h;
    h.insert_without_replacement("e", "8421318464");
    h.insert_without_replacement("g", "9869393457");
    h.insert_without_replacement("g", "8378973381");
    h.insert_without_replacement("h", "73381");
   h.display();
    h.search("h");
    cout<<"********************************************"<<endl;
   Hash h2;

    h2.insert_with_replacement("e", "545");
    h2.insert_with_replacement("g", "54");
    h2.insert_with_replacement("g", "4");
    h2.insert_with_replacement("h", "100");
    h2.display();
    h2.search("h");
    h2.delete_contact("h");
    h2.insert_with_replacement("i", "101");
    h2.display();
    return 0;
}