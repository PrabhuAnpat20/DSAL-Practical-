// PS 1 2 3 4

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

    friend class BinaryTree;
};

class BinaryTree
{
public:
    Node *root;
    BinaryTree()
    {
        root == NULL;
    }

    void CreateTree()
    {
        int data;
        cout << "enter data for root" << endl;
        cin >> data;
        Node *newnode = new Node(data);
        root = newnode;
    }
    void Insert()
    {
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {

            Node *node = q.front();
            q.pop();
            int LeftData;
            cout << "enter data for left of :" << node->data << endl;
            cin >> LeftData;

            if (LeftData != -1)
            {
                Node *newnode = new Node(LeftData);
                node->left = newnode;
                q.push(newnode);
            }
            int RightData;
            cout << "enter data for right of :" << node->data << endl;
            cin >> RightData;

            if (RightData != -1)
            {
                Node *newnode = new Node(RightData);
                node->right = newnode;
                q.push(newnode);
            }
        }
    }

    void InOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        InOrder(root->left);
        cout << root->data << " ";
        InOrder(root->right);
    }
    void PreOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }
    void PostOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->data << " ";
    }

    void NonRecursivePreorder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }

        stack<Node *> st;
        st.push(root);
        while (!st.empty())
        {
            Node *top = st.top();
            st.pop();
            cout << top->data << " ";
            if (top->right)
            {
                st.push(top->right);
            }
            if (top->left)
            {
                st.push(top->left);
            }
        }
    }

    void NonRecursiveInorder(Node *root)
    {

        Node *node = root;

        stack<Node *> st;

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

                node = st.top();
                cout << node->data << " ";
                st.pop();
                node = node->right;
            }
        }
    }

    void LevelwisePrinting(Node *root)
    {
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
    void DisplayInternalNodes(Node *root)
    {
        if (!root)
            return;

        if (root->left || root->right)
        {
            cout << root->data << " ";
        }

        DisplayInternalNodes(root->left);
        DisplayInternalNodes(root->right);
    }

    void DisplayLeafNodes(Node *root)
    {
        if (!root)
            return;

        if (!root->left && !root->right)
        {
            cout << root->data << " ";
        }

        DisplayLeafNodes(root->left);
        DisplayLeafNodes(root->right);
    }

    void MirrorImage(Node *root)
    {
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
                if (node->right)
                {
                    q.push(node->right);
                }
                if (node->left)
                {
                    q.push(node->left);
                }
            }
        }
    }

    void NumNodes(Node *root, int &NodeCount)
    {
        if (root == NULL)
        {
            return;
        }
        NumNodes(root->left, NodeCount);
        NodeCount++;
        NumNodes(root->right, NodeCount);
    }
    void LeafNodes(Node *root, int &LeafCount)
    {

        if (root == NULL)
        {

            return;
        }
        if (root->left == NULL && root->right == NULL)
        {
            LeafCount++;
            return;
        }
        LeafNodes(root->left, LeafCount);
        LeafNodes(root->right, LeafCount);
    }

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
};
int main()
{
    BinaryTree b;

    b.CreateTree();
    b.Insert();

    // display/print
    b.LevelwisePrinting(b.root);
    cout << endl;

    cout << "Internal Nodes:";
    b.DisplayInternalNodes(b.root);
    cout << endl;

    cout << "Leaf Nodes:";
    b.DisplayLeafNodes(b.root);
    cout << endl;

    // recursive traversal
    cout << "InOrder:";
    b.InOrder(b.root);
    cout << endl;
    cout << "PreOrder:";
    b.PreOrder(b.root);
    cout << endl;
    cout << "PostOrder:";
    b.PostOrder(b.root);
    cout << endl;

    // Non Recursive Traversal
    cout << "Non Recursive PreOrder:";
    b.NonRecursivePreorder(b.root);
    cout << endl;
    cout << "Non Recursive InOrder:";
    b.NonRecursiveInorder(b.root);
    cout << endl;

    // Num of Leaf Nodes
    int LeafCount = 0;
    b.LeafNodes(b.root, LeafCount);
    cout << "No of Leaf Nodes=" << LeafCount << endl;

    // Num Of Internal Nodes
    int NodeCount = 0;
    b.NumNodes(b.root, NodeCount);
    cout << "No of Internal Nodes=" << NodeCount - LeafCount << endl;

    // Height of Tree
    cout << "Height of tree=" << b.Height(b.root) << endl;

    // Mirror Image
    cout << "mirror image" << endl;
    b.MirrorImage(b.root);

    return 0;
}