/*
 * Red Black Tree
 */

/* Print the tree, watch out for NullNode, and skip header */
static void DoPrint(RedBlackTree T)
{
    if (T != NullNode) {
        DoPrint(T->Left);
        Output(T->Element);
        DoPrint(T->Right);
    }
}

void PrintTree(RedBlackTree T)
{
    DoPrint(T->Right);
}

typedef enum ColorType {Red, Black} ColorType;

struct RedBlackNode
{
    ElementType  Element;
    RedBlackTree Left;
    RedBlackTree Right;
    ColorType    Color;
};

Position NullNode = NULL;  /* Needs initialization */

/* Initialization procedure */
RedBlackTree Initialize(void)
{
    RedBlackTree T;

    if (NullNode == NULL) {
        NullNode = malloc(sizeof(struct RedBlackNode));
        if (NullNode == NULL)
            FatalError("Out of space!!!");
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Color = Black;
        NullNode->Element = Infinity;
    }

    /* Create the header node */
    T = malloc(sizeof(struct RedBlackNode));
    if (T == NULL)
        FatalError("Out of space!!!");
    T->Element = NegInfinity;
    T->Left = T->Right = NullNode;
    T->Color = Black;

    return T;
}

/* Perform a rotation at node X */
/* (whose parent is passed as a parameter) */
/* The child is deduced by examining Item */
static Position Rotate(ElementType Item, Position Parent)
{
    if (Item < Parent->Element) {
        return Parent->Left = Item < Parent->Left->Element ?
            SingleRotateWithLeft(Parent->Left) :
            SingleRotateWightRight(Parent->Left);
    } else {
        return Parent->Right = Item < Parent->Right->Element ?
            SingleRotateWithLeft(Parent->Right) :
            SingleRotateWightRight(Parent->Right);
    }
}

static Position X, P, GP, GGP;

static HandleReorient(ElementType Item, RedBlackTree T)
{
    X->Color = Red;  /* Do the color flip */
    X->Left->Color = Black;
    X->Right->Color = Black;

    if (P->Color == Red) {  /* Have to rotate */
        GP->Color = Red;
        if ((Item < GP->Element) != (Item < P->Element))
            P->Rotate(Item, GP);  /* Start double rotation */
        X = Rotate(Item, GGP);
        X->Color = Black;
    }
    T->Right->Color = Black;  /* Make root black */
}

RedBlackTree Insert(ElementType Item, RedBlackTree T)
{
    X = P = GP = T;
    NullNode->Element = Item;
    while (X->Element != Item) {  /* Descend down the tree */
        GGP = GP;
        GP = P;
        P = X;
        if (Item < X->Element)
            X = X->Left;
        else
            X = X->Right;
        if (X->Left->Color == Red && X->Right->Color == Red)
            HandleReorient(Item, T);
    }

    if (X != NullNode)
        return NullNode;  /* Duplicate */

    X = malloc(sizeof(struct RedBlackNode));
    if (X == NULL)
        FatalError("Out of space!!!");
    X->Element = Item;
    X->Left = X->Right = NullNode;

    if (Item < P->Element)  /* Attach to its parent */
        P->Left = X;
    else
        P->Right = X;
    HandleReorient(Item, T);  /* Color red; maybe rotate */

    return T;
}
