#include <iostream>
#include <queue>
#include <stack>
#define MAX_VERTICES 100 // Maximum number of vertices

using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int val)
    {
        data = val;
        next = NULL;
    }
};

class Graph
{
private:
    int V;                       // Number of vertices
    Node *adjList[MAX_VERTICES]; // Adjacency list

public:
    Graph(int vertices)
    {
        V = vertices;
        for (int i = 0; i < V; i++)
            adjList[i] = NULL;
    }

    void addEdge(int u, int v)
    {
        Node *newNode = new Node(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;

        newNode = new Node(u); // For undirected graph
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }

    void printAdjList()
    {
        for (int i = 0; i < V; i++)
        {
            Node *temp = adjList[i];
            cout << "Adjacency list of vertex " << i << ": ";
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    void BFS(int startVertex)
    {
        int visited[V] = {0};
        visited[startVertex] = 1;
        queue<int> q;
        q.push(startVertex);
        while (!q.empty())
        {
            int front = q.front();
            q.pop();
            cout << front << " ";
            Node *temp = adjList[front];
            while (temp != NULL)
            {
                if (!visited[temp->data])
                {
                    q.push(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

    
    void DFS(int startVertex) {
        bool visited[V] = {0};
        stack <int> stack;
         

        visited[startVertex] = 1;
        stack.push(startVertex);

        while (!stack.empty()) {
            int currentVertex = stack.top();
            stack.pop();
            cout << currentVertex << " ";

            Node* temp = adjList[currentVertex];
            while (temp != NULL) {
                int adjVertex = temp->data;
                if (!visited[adjVertex]) {
                    visited[adjVertex] = 1;
                    stack.push(adjVertex);
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }
};

int main()
{
    // Create a graph with 4 vertices
    Graph g(8);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(4, 7);
    g.addEdge(5, 7);

    // Display graph
    g.printAdjList();

    // traversal
    g.BFS(0);
    g.DFS(0);

    return 0;
}
