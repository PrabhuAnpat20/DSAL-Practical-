#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Node
{
private:
    int data;
    Node *left;
    Node *right;

    Node(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }

    friend class BST;
};

class BST
{
public:
    Node *InsertInBST(Node *root, int data)
    {
        if (root == NULL)
        {
            root = new Node(data);
            return root;
        }
        if (data < root->data)
        {
            root->left = InsertInBST(root->left, data);
        }
        else
        {
            root->right = InsertInBST(root->right, data);
        }

        return root;
    }

    void TakeInput(Node *&root)
    {
        cout << "Enter data " << endl;
        int data;
        cin >> data;
        while (data != -1)
        {
            root = InsertInBST(root, data);
            cin >> data;
        }
    }

    // level order
    void Display(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        queue<Node *> q;
        q.push(root);
        q.push(NULL);
        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();
            if (node == NULL)
            {
                cout << endl;
                if (!q.empty())
                {
                    q.push(NULL);
                }
            }
            else
            {
                cout << node->data << " ";
                if (node->left)
                {
                    q.push(node->left);
                }
                if (node->right)
                {
                    q.push(node->right);
                }
            }
        }
    }

    void AscendingOrder(Node *root)
    {
        stack<Node *> st;
        Node *node = root;
        while (true)
        {
            if (node != NULL)
            {
                st.push(node);
                node = node->left;
            }
            else
            {
                if (st.empty())
                {
                    break;
                }

                if (node == NULL)
                {
                    node = st.top();
                    cout << node->data << " ";
                    st.pop();
                    node = node->right;
                }
            }
        }
    }

    void DescendingOrder(Node *root)
    {
        stack<Node *> st;
        Node *node = root;
        while (true)
        {
            if (node != NULL)
            {
                st.push(node);
                node = node->right;
            }
            else
            {
                if (st.empty())
                {
                    break;
                }

                if (node == NULL)
                {
                    node = st.top();
                    cout << node->data << " ";
                    st.pop();
                    node = node->left;
                }
            }
        }
    }

    bool Search(Node *root, int data, int &c)
    {
        if (root == NULL)
        {
            return false;
        }
        if (root->data == data)
        {
            c++;
            return true;
        }
        if (root->data > data)
        {
            c++;
            Search(root->left, data, c);
        }
        else
        {
            c++;
            Search(root->right, data, c);
        }
    }

    void Max(Node *root)
    {
        while (root->right != NULL)
        {
            root = root->right;
        }

        cout << "Max Data=" << root->data << endl;
    }

    void Min(Node *root)
    {
        while (root->left != NULL)
        {
            root = root->left;
        }

        cout << "Min Data=" << root->data << endl;
    }
    // *******************************************
    Node *DeleteNode(Node *root, int data)
    {
        if (root->data==data)
        {
            return helper(root);
        }
        
        Node *dummy = root;
        while (root != NULL)
        {
            if (root->data > data)
            {
                if (root->left != NULL && root->left->data == data)
                {
                    root->left = helper(root->left);
                    break;
                }
                else
                {
                    root = root->left;
                }
            }
            else
            {

                if (root->right != NULL && root->right->data == data)
                {
                    root->right = helper(root->right);
                    break;
                }
                else
                {
                    root = root->right;
                }
            }
        }
        return dummy;
    }

    Node *helper(Node *root)
    {
        if (root->left == NULL)
        {
            return root->right;
        }
        else if (root->right == NULL)
        {
            return root->left;
        }

        Node *ltemp = root->left;
        Node *rtemp = root->right;
        Node *r = rightmost(ltemp);
        r->right = rtemp;
        return ltemp;
    }

    Node *rightmost(Node *root)
    {
        if (root->right == NULL)
        {
            return root;
        }
        return rightmost(root->right);
    }
    // *******************************************

    int Height(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        int LeftHeight = Height(root->left);
        int RightHeight = Height(root->right);
        return 1 + max(LeftHeight, RightHeight);
    }

    void NodesInLongestPath(Node *root, int &nc)
    {
        if (root == NULL)
        {
            return;
        }

        int leftHeight = Height(root->left);
        int rightHeight = Height(root->right);

        nc = max(nc, 1 + leftHeight + rightHeight);

        NodesInLongestPath(root->left, nc);
        NodesInLongestPath(root->right, nc);
    }

    void Swap(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        Node *ltemp = root->left;
        Node *rtemp = root->right;
        root->right = ltemp;
        root->left = rtemp;
        Swap(root->left);
        Swap(root->right);
    }
};

int main()
{
    BST b;
    Node *root = NULL;

    // create bst
    b.TakeInput(root);

    // insert a node
    b.InsertInBST(root, 20);

    // printing bst
    b.Display(root);
    b.AscendingOrder(root);
    cout << endl;
    b.DescendingOrder(root);
    cout << endl;

    // searching
    int c = 0;
    if (b.Search(root, 4, c))
    {
        cout << "Element found" << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }
    cout << "No of comparisons=" << c << endl;

    //  min/max
    b.Max(root);
    b.Min(root);

    // delete node
    root = b.DeleteNode(root, 4);
    b.Display(root);
    cout << endl;

    // No Of Nodes In Longest Path
    int nc = 0;
    b.NodesInLongestPath(root, nc);
    cout << "No. of Nodes In Longest Path=" << nc << endl;

    // Swap nodes
    b.Display(root);
    b.Swap(root);
    b.Display(root);
    return 0;
}