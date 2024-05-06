#include <iostream>
#include <climits>
#define MAX_VERTICES 100
using namespace std;
class Node
{
    int data;
    int weight;
    Node *next;

    Node(int data, int weight)
    {
        this->data = data;
        this->weight = weight;
        next = NULL;
    }
    friend class Graph;
};
class Graph
{
    int V;
    Node *adjList[MAX_VERTICES];

public:
    Graph(int v)
    {
        V = v;
        for (int i = 0; i < v; i++)
        {
            adjList[i] = NULL;
        }
    }
    void AddEdge(int v, int u, int w)
    {
        Node *newnode = new Node(v, w);
        newnode->next = adjList[u];
        adjList[u] = newnode;

        newnode = new Node(u, w);
        newnode->next = adjList[v];
        adjList[v] = newnode;
    }
    void PrintAdjList()
    {
        for (int i = 0; i < V; i++)
        {
            Node *temp = adjList[i];
            cout << "node :" << i << "->";
            while (temp != NULL)
            {
                cout << temp->data << "," << temp->weight << "->";
                temp = temp->next;
            }
            cout << "x" << endl;
        }
    }
    void Prims()
    {
        int key[V];
        bool mst[V];
        int parent[V];

        for (int i = 0; i < V; i++)
        {
            key[i] = INT_MAX;
            parent[i] = -1;
            mst[i] = false;
        }

        key[0] = 0;
        int u;
        for (int i = 0; i < V; i++)
        {
            int mini = INT_MAX;
            for (int i = 0; i < V; i++)
            {
                if (key[i] < mini && !mst[i])
                {
                    u = i;
                    mini = key[u];
                }
            }
            mst[u] = true;

            Node *temp = adjList[u];
            while (temp != NULL)
            {
                int v = temp->data;
                int w = temp->weight;

                if (key[v] > w && !mst[v])
                {
                    key[v] = w;
                    parent[v] = u;
                }
                temp = temp->next;
            }
        }

        for (int i = 0; i < V; i++)
        {
            if (parent[i] != -1)
            {
                cout << i << "->" << parent[i] << endl;
            }
        }

        int minW = 0;
        for (int i = 0; i < V; i++)
        {
            minW += key[i];
        }
        cout << "!! Minimum Cost = " << minW;
    }
};
int main()
{

    int nv;
    cout << "No . of Offices" << endl;
    cin >> nv;
    Graph G(nv);
    for (int i = 0; i <= nv; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G.AddEdge(u, v, w);
    }
    G.PrintAdjList();
    cout << "********** connect the phone lines as follows **********" << endl;
    G.Prims();
    return 0;
}