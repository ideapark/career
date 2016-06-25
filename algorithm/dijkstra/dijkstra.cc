/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 *
 * Dijkstra's Algorithm
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

typedef vector<Edge>::const_iterator EdgeIter;
typedef set<Vertex>::const_iterator VertexIter;

void Dijkstra(const vector<Edge> &Graph, Vertex src)
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

		// Vertex u can not be reached
		if (Distance[u] == ~0)
			continue;

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
	for (int i = 0; i < 50; i++) {
		Edge edge = {i, i+3, i+i};
		Graph.push_back(edge);
		cout << " S:" << edge.src
		     << " D:" << edge.dst
		     << " W:" << edge.weight
		     << endl;
	}

	Dijkstra(Graph, 5);

	return 0;
}
