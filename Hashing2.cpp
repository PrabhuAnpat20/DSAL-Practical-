#include <iostream>
using namespace std;
#define size 10

class node
{
public:
    string word;
    string meaning;
    node *next;

    node()
    {
        word = "";
        meaning = "";
        next = NULL;
    }
    node(string word, string meaning)
    {
        this->word = word;
        this->meaning = meaning;
        next = NULL;
    }
};

class Hash
{
public:
    node *dict[size];

    Hash()
    {

        for (int i = 0; i < size; i++)
        {
            dict[i] = NULL;
        }
    }
    int gethash(string key)
    {
        int hash = 0;
        for (int i = 0; i < key.length(); i++)
        {
            hash += int(key[i]);
        }
        cout << hash << endl;
        return hash % size;
    }
    void insert(string word, string meaning)
    {
        node *newnode = new node(word, meaning);
        int hash = gethash(word);
        if (dict[hash] != NULL)
        {
            node *temp = dict[hash];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newnode;
        }
        else
        {
            dict[hash] = newnode;
        }
        cout << "inserted" << endl;
    }
    void deleteWord(string word)
    {
        int hash = gethash(word);
        node *prev = NULL;
        node *current = dict[hash];

        // Search for the word to be deleted
        while (current != NULL && current->word != word)
        {
            prev = current;
            current = current->next;
        }

        // If word not found
        if (current == NULL)
        {
            cout << "Word '" << word << "' not found for deletion." << endl;
            return;
        }

        // If word is the first node in the linked list
        if (prev == NULL)
        {
            dict[hash] = current->next;
            delete current;
            cout << "Word '" << word << "' deleted." << endl;
            return;
        }

        // If word is in the middle or at the end of the linked list
        prev->next = current->next;
        delete current;
        cout << "Word '" << word << "' deleted." << endl;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            node *temp = dict[i];
            cout << i << ":";
            while (temp)
            {
                cout << temp->word << "->";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    void search(string word)
    {
        int hash = gethash(word);
        node *temp = dict[hash];
        bool b = 0;
        while (temp)
        {
            if (temp->word == word)
            {
                cout << "word :" << temp->word << "  "
                     << "meaning :" << temp->meaning << endl;
                b = 1;
                break;
            }
            temp = temp->next;
        }
        if (!b)
        {
            cout << "not found" << endl;
        }
    }
};

int main()
{
    Hash h;
    h.insert("e", "dwdw");
    h.insert("a", "wdw");
    h.insert("e", "dwdw");
    h.insert("a", "dwdw");
    h.insert("a", "d");
    h.deleteWord("a");
    h.print();
    h.search("aasaa");

    return 0;
}