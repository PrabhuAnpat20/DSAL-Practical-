#include <iostream>
using namespace std;

class Node
{
    string key;
    string meaning;
    Node *left;
    Node *right;
    int height;

    Node(string key, string meaning)
    {
        this->key = key;
        this->meaning = meaning;
        left = NULL;
        right = NULL;
        height = 1;
    }
    friend class AVL;
};
class AVL
{

public:
    Node *root;
    AVL()
    {
        root = NULL;
    }
    void insert(string key, string meaning)
    {
        this->root = insert(root, key, meaning);
    }

    void Ascending()
    {

        inorder(root);
    }
    void SearchNode(string key)
    {
        int c = 0;
        Node *temp = search(key, root, c);
        if (temp)
        {
            cout << "Found after " << c << " comparisons" << endl;
            cout << temp->key << " \t " << temp->meaning << " - " << getBF(temp) << endl;
        }
        else
        {
            cout << "not found" << endl;
        }
    }

private:
    int height(Node *node)
    {
        if (node == NULL)

        {
            return 0;
        }
        return node->height;
    }
    int getBF(Node *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *t = x->right;

        // rotation
        x->right = y;
        y->left = t;

        // update height
        y->height = 1 + max(height(y->left), height(y->right));

        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }
    Node *rotateLeft(Node *y)
    {
        Node *x = y->right;
        Node *t = x->left;

        // rotation
        x->left = y;
        y->right = t;

        // update height
        y->height = 1 + max(height(y->left), height(y->right));

        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }
    Node *insert(Node *node, string key, string meaning)
    {

        Node *newnode = new Node(key, meaning);
        if (node == NULL)
        {
            return newnode;
        }

        if (key < node->key)
        {
            node->left = insert(node->left, key, meaning);
        }
        else
        {
            node->right = insert(node->right, key, meaning);
        }

        // update height
        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBF(node);

        // LL
        if (balance > 1 && key < node->left->key)
        {
            return rotateRight(node);
        }
        // RR
        if (balance < -1 && key > node->right->key)
        {
            return rotateLeft(node);
        }
        // RL
        if (balance < -1 && key < node->right->key)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
            return (node);
        }
        // LR
        if (balance > 1 && key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        return node;
    }

    void inorder(Node *node)
    {
        if (node != NULL)
        {

            inorder(node->left);
            cout << node->key << " \t " << node->meaning << " - " << getBF(node) << endl;
            inorder(node->right);
        }
    }

    Node *search(string key, Node *node, int &c)
    {
        if (node == NULL)
        {
            return NULL;
        }
        if (node->key == key)
        {
            c++;
            return node;
        }

        if (key > node->key)
        {
            c++;
            search(key, node->right, c);
        }
        else
        {
            c++;
            search(key, node->left, c);
        }
    }
};
int main()
{
    AVL avl;
    string key, meaning;
    int choice;

    while (true)
    {
        cout << "1 ->add word " << endl;
        cout << "2->Display(Ascending)" << endl;
        cout<<"3->search"<<endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter word" << endl;
            cin >> key;
            cout << "enter meaning" << endl;
            cin >> meaning;
            avl.insert(key, meaning);
            break;
        case 2:
            avl.Ascending();

            break;
        case 3:
            cout<<"word to search"<<endl;
            cin>>key;
            avl.SearchNode(key);
            break;    
        default:
            cout << "Invalid Input!!" << endl;
            break;
        }
    }

    return 0;
}