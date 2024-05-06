#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph
{
    int NumVertices;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int nv)
    {
        NumVertices = nv;
        adj.resize(NumVertices);
    }
    void AddEdges(int src, int dest, int weight)
    {
        adj[src].push_back(make_pair(dest, weight));
        adj[dest].push_back(make_pair(src, weight));
    }

    void PrimsMST()
    {

        int key[NumVertices];
        bool mst[NumVertices];
        int parent[NumVertices];

        for (int i = 0; i < NumVertices; i++)
        {
            key[i] = INT_MAX;
            parent[i] = -1;
            mst[i] = false;
        }

        key[0] = 0;

        for (int i = 0; i < NumVertices; i++)
        {

            int mini = INT_MAX;
            int u;
            for (int v = 0; v < NumVertices; v++)
            {
                if (mst[v] == false && key[v] < mini)
                {
                    u = v;
                    mini = key[v];
                }
            }

            mst[u] = true;
            for (auto it : adj[u])
            {

                int v = it.first;
                int w = it.second;
                if (mst[v] == false && w < key[v])
                {
                    parent[v] = u;
                    key[v] = w;
                }
            }
        }
        for (int i = 0; i < NumVertices; i++)
        {
            if (parent[i] != -1)
            {
                cout << i << "->" << parent[i] << endl;
            }
        }

        int minW = 0;
        for (int i = 0; i < NumVertices; i++)
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
        G.AddEdges(u, v, w);
    }
    cout << "********** connect the phone lines as follows **********" << endl;
    G.PrimsMST();

    return 0;
}