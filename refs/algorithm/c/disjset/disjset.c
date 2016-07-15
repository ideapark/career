#include "disjset.h"

void Initialize(DisjSet S)
{
	int i;

	for (i = NumSets; i > 0; i--)
		S[i] = 0;
}

/* Assumes Root1 and Root2 are roots */
/* union is a C keyword, so this routine */
/* is named SetUnion */
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
	S[Root2] = Root1;
}

/* Path compression */
SetType Find(ElementType X, DisjSet S)
{
	if (S[X] <= 0)
		return X;
	else
		return S[X] = Find(S[X], S);
}

/* Optimized SetUnion() algorithm */
void SetUnionByHeight(DisjSet S, SetType Root1, SetType Root2)
{
	if (S[Root2] < S[Root1])  /* Root2 is deeper set */
		S[Root1] = Root2; /* Make Root2 new root */
	else {
		if (S[Root1] == S[Root2])  /* Same height */
			S[Root1]--;        /* so update */
		S[Root2] = Root1;
	}
}
