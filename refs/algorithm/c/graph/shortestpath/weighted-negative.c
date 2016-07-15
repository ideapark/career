void WeightedNegative(Table T)
{
	Queue Q;
	Vertex V, W;

	Q = CreateQueue(NumVertex);
	MakeEmpty(Q);
	Enqueue(S, Q);  /* Enqueue the start vertex S */

	while (!IsEmpty(Q)) {
		V = Dequeue(Q);
		for each w adjacent to V
			if (T[V].Dist + Cvw < T[W].Dist) {
				/* Update W */
				T[W].Dist = T[V].Dist + Cvw;
				T[W].Path = V;
				if (W is not already in Q)
					Enqueue(W, Q);
			}
	}
	DisposeQueue(Q);
}
