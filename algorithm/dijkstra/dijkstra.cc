/**
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

typedef unsigned int Vertex;
typedef unsigned int Weight;

typedef struct {
    Vertex src;
    Vertex dst;
    Weight weight;
} Edge;

static vector<Edge> Graph;

typedef vector<Edge>::iterator EdgeIter;
typedef set<Vertex>::iterator VertexIter;

void Dijkstra(vector<Edge> &Graph, Vertex src)
{
    map<Vertex, Weight> Distance;
    map<Vertex, Vertex> Previous;
    set<Vertex> Q;

    for (EdgeIter iter = Graph.begin(); iter != Graph.end(); iter++) {
        Distance[iter->src] = ~0;
        Distance[iter->dst] = ~0;

        Previous[iter->src] = ~0;
        Previous[iter->dst] = ~0;

        Q.insert(Q.begin(), iter->src);
        Q.insert(Q.begin(), iter->dst);
    }

    Distance[src] = 0;

    while (!Q.empty()) {

        VertexIter minIter = Q.begin();

        for (VertexIter iter = Q.begin(); iter != Q.end(); iter++) {
            if (Distance[*iter] < Distance[*minIter])
                minIter = iter;
        }

        Vertex u = *minIter;

        // Print out shortest path
        {
            stack<Vertex> S;
            Vertex backVertex = u;

            while (Previous[backVertex] != ~0) {
                S.push(backVertex);
                backVertex = Previous[backVertex];
            }
            S.push(backVertex);

            cout << " T: " << setw(3) << u
                 << " D: " << setw(10) << Distance[u]
                 << " P: ";
            while (!S.empty()) {
                cout << setw(3) << S.top() << " -> ";
                S.pop();
            }
            cout << endl;
        }

        Q.erase(minIter);

        for (EdgeIter iter = Graph.begin(); iter != Graph.end(); ++iter) {
            if (iter->src == u) {
                Weight alt = Distance[u] + iter->weight;
                if (alt < Distance[iter->dst]) {
                    Distance[iter->dst] = alt;
                    Previous[iter->dst] = u;
                }
            }
        }

    }

}

int main(int argc, char *argv[])
{
    Edge testEdges[] = {
        {1,2,10},
        {1,3,20},
        {1,4,15},
        {2,5,13},
        {2,6,1},
        {2,7,8},
        {3,8,10},
        {3,9,20},
        {3,10,15},
        {3,12,1},
        {4,13,12},
    };

    cout << "==Graph==" << endl;

    for (int i = 0; i < sizeof(testEdges)/sizeof(testEdges[0]); i++) {
        Graph.push_back(testEdges[i]);
        cout << " s: " << testEdges[i].src
             << " d: " << testEdges[i].dst
             << " w: " << testEdges[i].weight
             << endl;
    }

    Dijkstra(Graph, 2);

    return 0;
}
