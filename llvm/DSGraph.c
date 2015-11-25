typedef struct list {
  struct list *Next;
  int Data;
} list;

int G = 10;

void do_all(list *L1, void (*FP)(int *)) {
  do {
    L2 = phi(L1, L3); /* SSA phi node */
    FP(&L2->Data);
    L3 = L2->Next;
  } while (L3);
}

void addG(int *X) {
  (*X) += G;
}

void addGToList(list *L) {
  do_all(L, addG);
}

list *makeList(int Num) {
  list *New = malloc(sizeof(list));
  New->Next = Num ? makeList(Num-1) : 0;
  New->Data = Num;
  return New;
}

int main() { /* X & Y lists are disjoint */
  list *X = makeList(10);
  list *Y = makeList(100);
  addGToList(X);
  addGToList(Y);
}
