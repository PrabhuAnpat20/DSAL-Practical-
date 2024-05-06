#include <iostream>
#include <queue>
#include <stack>
#include <string>

#define MAX_VERTICES 100 // Maximum number of vertices

using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(string val) {
        data = val;
        next = NULL;
    }
};

class Graph {
private:
    string cities[MAX_VERTICES]; // Array to store city names
    int V; // Number of vertices
    Node* adjList[MAX_VERTICES]={NULL}; // Adjacency list

public:
    Graph() {
        V = 0;
    }

    void addVertex(string city) {
        cities[V] = city;
        V++;
    }

    int getIndex(string city) {
        for (int i = 0; i < V; ++i) {
            if (cities[i] == city)
                return i;
        }
        return -1; // City not found
    }

    void addEdge(string u, string v) {
        int uIndex = getIndex(u);
        int vIndex = getIndex(v);
        if (uIndex == -1 || vIndex == -1) {
            cout << "One or both of the cities are not present in the graph!" << endl;
            return;
        }

        Node* newNode = new Node(v);
        newNode->next = adjList[uIndex];
        adjList[uIndex] = newNode;

        newNode = new Node(u); 
        newNode->next = adjList[vIndex];
        adjList[vIndex] = newNode;
    }

    void printAdjList() {
        for (int i = 0; i < V;i++) {
            cout << "Adjacency list of vertex " << cities[i] << ": ";
            Node* temp = adjList[i];
            while (temp != NULL) {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void BFS(string startVertex) {
        int startVertexIndex = getIndex(startVertex);
        if (startVertexIndex == -1) {
            cout << "City not present in the graph!" << endl;
            return;
        }

        bool visited[MAX_VERTICES] = {false};
        visited[startVertexIndex] = true;
        queue<int> q;
        q.push(startVertexIndex);
        while (!q.empty()) {
            int front = q.front();
            q.pop();
            cout << cities[front] << " ";
            Node* temp = adjList[front];
            while (temp != NULL) {
                int adjVertex = getIndex(temp->data);
                if (!visited[adjVertex]) {
                    q.push(adjVertex);
                    visited[adjVertex] = true;
                }
                temp = temp->next;
            }
        }
        cout << endl;
    }

void DFS(string startVertex) {
    int startVertexIndex = getIndex(startVertex);
    if (startVertexIndex == -1) {
        cout << "City not present in the graph!" << endl;
        return;
    }

    bool visited[MAX_VERTICES] = {false};
    stack<int> stack;
    visited[startVertexIndex] = true;
    stack.push(startVertexIndex);

    while (!stack.empty()) {
        int currentVertex = stack.top();
        stack.pop();
        cout << cities[currentVertex] << " ";

        Node* temp = adjList[currentVertex];
        while (temp != nullptr) {
            int adjVertex = getIndex(temp->data);
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                stack.push(adjVertex);
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

void degree(){
            for (int i = 0; i < V;i++) {
            cout << "Degree of node " << cities[i] << ": ";
            Node* temp = adjList[i];
            int c=0;
            while (temp != NULL) {
                c++;
                temp = temp->next;
            }
            cout << c;
            cout<<endl;
        }
}

};

int main() {
    // Create a graph
    Graph g;

    // Add vertices (cities)
    g.addVertex("Pune");
    g.addVertex("Mumbai");
    g.addVertex("Delhi");
    g.addVertex("Bangalore");
    g.addVertex("Chennai");

    // Add edges (connections between cities)
    g.addEdge("Pune", "Mumbai");
    g.addEdge("Pune", "Bangalore");
    g.addEdge("Mumbai", "Delhi");
    g.addEdge("Bangalore", "Chennai");
    g.addEdge("Chennai", "Delhi");

    // Display graph
    g.printAdjList();

    // Perform BFS traversal starting from a city
    cout << "BFS traversal starting from Pune: ";
    g.BFS("Pune");

    // Perform DFS traversal starting from a city
    cout << "DFS traversal starting from Pune: ";
    g.DFS("Pune");

    // degree of each node
    g.degree();
    return 0;
}
