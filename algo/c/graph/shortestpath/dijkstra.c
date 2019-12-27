typedef int Vertex;

struct TableEntry
{
	List     Header;  /* Adjacency list */
	int      Known;
	DistType Dist;
	Vertex   Path;
};

/* Vertices are numbered from 0 */
#define NotAVertex  (-1)
typedef struct TableEntry Table[NumVertex];

void InitTable(Vertex Start, Graph G, Table T)
{
	int i;

	ReadGraph(G, T);  /* Read graph somehow */
	for (i = 0; i < NumVertex; i++) {
		T[i].Known = False;
		T[i].Dist = Infinity;
		T[i].Path = NotAVertex;
	}
	T[Start].dist = 0;
}

/* Print shortest path to V after Dijkstra has run */
/* Assume that the path exists */
void PrintPath(Vertex V, Table T)
{
	if (T[V].Path != NotAVertex) {
		PrintPath(T[V].Path, T);
		printf(" to");
	}
	printf("%v", V);  /* %v is pseudocode */
}

void Dijkstra(Table T)
{
	Vertex V, W;

	for (;;) {
		V = smallest unknown distance vertex;
		if (V == NotAVertex)
			break;

		T[V].Known = True;
		for each W adjacent to V
			if (!T[V].Known)
				if (T[V].Dist + Cvw < T[W].Dist) {
					/* Update W */
					Decrease(T[W].Dist to T[V].Dist + Cvw);
					T[W].Path = V;
				}
	}
}
