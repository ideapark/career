/**
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */
#include <vector>
#include <stack>
#include <map>
#include <set>

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

  for (int i = 0; i < sizeof(testEdges)/sizeof(testEdges[0]); i++)
    Graph.push_back(testEdges[i]);

  Dijkstra(Graph, 2);

  return 0;
}
