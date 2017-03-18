#ifndef CCORE_BST_H
#define CCORE_BST_H

#include <stddef.h>

#define true   1
#define false  0

typedef struct Node {
        struct Node *left;  // point to left node
        struct Node *right; // point to right node
        size_t size;        // memory needed
        char data[];        // data
} Node_t;

typedef const void *GetKeyFunc_t(const void *dData);
typedef int CmpFunc_t(const void *pKey1, const void *pKey2);

typedef struct {
        struct Node  *pRoot;  // point to root of BST
        CmpFunc_t    *cmp;    // compare two keys
        GetKeyFunc_t *getKey; // convert data to key
} BST_t;

BST_t *newBST(CmpFunc_t *cmp, GetKeyFunc_t *getKey);

_Bool BST_insert(BST_t *pBST, const void *pData, size_t size);

const void *BST_search(BST_t *pBST, const void *pKey);

_Bool BST_erase(BST_t *pBST, const void *pKey);

void BST_clear(BST_t *pBST);

int BST_inorder(BST_t *pBST, _Bool (*action)(void *pData));

int BST_rev_inorder(BST_t *pBST, _Bool (*action)(void *pData));

int BST_preorder(BST_t *pBST, _Bool (*action)(void *pData));

int BST_postorder(BST_t *pBST, _Bool (*action)(void *pData));

#endif // CCORE_BST_H
