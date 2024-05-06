// PS  8 10 11 12

#include <iostream>
using namespace std;
class Node
{
private:
    int data;
    Node *left;
    Node *right;
    int Lbit;
    int Rbit;
    Node(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
        Lbit = 0;
        Rbit = 0;
    }
    friend class TBST;
};
class TBST
{
public:
    Node *root;
    Node *head;

    TBST()
    {
        head = new Node(9999);
        root = NULL;
    }
    void Insert(int data)
    {
        Node *newnode = new Node(data);
        if (root == NULL)
        {
            root = newnode;
            head->left = root;
            root->left = head;
            root->right = head;
            head->Lbit = 1;
        }
        else
        {

            Node *parent = root;
            while (true)
            {
                if (parent->data > data)
                // go left
                {
                    if (parent->Lbit == 1)
                    {
                        parent = parent->left;
                    }
                    else
                    {

                        newnode->left = parent->left;
                        parent->left = newnode;
                        parent->Lbit = 1;
                        newnode->right = parent;
                        return;
                    }
                }
                // go right
                else
                {
                    if (parent->Rbit == 1)
                    {
                        parent = parent->right;
                    }
                    else
                    {
                        newnode->right = parent->right;
                        parent->right = newnode;
                        parent->Rbit = 1;
                        newnode->left = parent;
                        return;
                    }
                }
            }
        }
    }

    void Inorder()
    {
        Node *temp = root;
        do
        {
            while (temp->Lbit != 0)
            {
                temp = temp->left;
            }
            cout << temp->Lbit << "<-" << temp->data << "->" << temp->Rbit << "   ";
            while (temp->Rbit == 0)
            {
                temp = temp->right;
                if (temp == head)
                {
                    return;
                }

                cout << temp->Lbit << "<-" << temp->data << "->" << temp->Rbit << "   ";
            }
            temp = temp->right;

        } while (temp != head);
    }
    void PreOrder()
    {
        Node *temp = root;
        do
        {
            while (temp->Lbit != 0)
            {
                cout << temp->Lbit << "<-" << temp->data << "->" << temp->Rbit << "   ";
                temp = temp->left;
            }
            cout << temp->Lbit << "<-" << temp->data << "->" << temp->Rbit << "   ";
            while (temp->Rbit == 0)
            {
                temp = temp->right;
                if (temp == head)
                {
                    return;
                }
            }
            temp = temp->right;

        } while (temp != head);
    }

    bool Search(int data, Node *&Parent, Node *&Curr)
    {
        while (Curr != head)
        {
            if (Curr->data == data)
            {
                return true;
            }
            else
            {
                Parent = Curr;
                if (Curr->data > data)
                {
                    Curr = Curr->left;
                }
                else
                {
                    Curr = Curr->right;
                }
            }
        }
        return false;
    }
    void Delete(Node *&parent, Node *&curr)
    {
        // leaf node
        if (curr->Lbit == 0 && curr->Rbit == 0)
        {
            if (parent->left == curr)
            {
                parent->left = curr->left;
                parent->Lbit = 0;
            }
            else
            {
                parent->right = curr->right;
                parent->Rbit = 0;
            }
            delete curr;
        }

        // left thread
        if (curr->Lbit==0 && curr->Rbit==1)
        {
            Node* temp=curr->right;
            if (parent->left=curr)
            {
                parent->left=temp;
            }
            else
            {
                parent->right=temp;
            }
            
            
            while (temp->Lbit!=0)
            {
            temp=temp->left;
            }
            temp->left=curr->left;
            delete curr;
            
        }


        // right thread
        if (curr->Rbit==0 && curr->Lbit==1)
        {
            Node* temp=curr->left;
            if (parent->left=curr)
            {
                parent->right=temp;
            }
            else
            {
                parent->left=temp;
            }
            
            
            while (temp->Rbit!=0)
            {
            temp=temp->right;
            }
            temp->right=curr->right;
            delete curr;
            
        }

        // no thread
        if (curr->Rbit==1 && curr->Lbit==1)
        {
            Node *temp=curr->right;
            Node *p=curr;
            while (temp->Lbit!=0)
            {
                p=temp;
                temp=temp->left;
            }
            curr->data=temp->data;
            Delete(p,temp);
        }
        
        
    }
};
int main()
{
    TBST b;
    int n;
    cout << "how many nodes to enter" << endl;
    cin >> n;

    while (n--)
    {
        int data;
        cout << "enter data" << endl;
        cin >> data;
        b.Insert(data);
    }
    cout << endl;

    // traversal
    // Lbit<-data->Rbit
    cout<<"Inorder=";b.Inorder();
    cout << endl;
    cout<<"Preorder="; b.PreOrder();
    cout<<endl;



    // delete
    Node *parent = NULL;
    Node *curr = b.root;
   if (b.Search(10, parent, curr))
    {
        b.Delete(parent,curr);
    }
    cout<<"Inorder=";b.Inorder();

    return 0;
}