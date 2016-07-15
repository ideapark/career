/**
 *  FixedSizeAllocator class
 *  Copyright 2001 Justin Heyes-Jones
 *
 *  This class is a constant time O(1) memory manager for objects of
 *  a specified type. The type is specified using a template class.
 *
 *  Memory is allocated from a fixed size buffer which you can specify
 *  in the class constructor or use the default.
 *
 *  Using GetFirst and GetNext it is possible to iterate through the
 *  elements one by one, and this would be the most common use for the
 *  class.
 *
 *  I would suggest using this class when you want O(1) add and delete
 *  and you don't do much searching, which would be O(n). Structures
 *  such as binary trees can be used instead to get O(logn) access time.
 */

#ifndef FSA_H
#define FSA_H

#include <string.h>
#include <stdio.h>

template <class USER_TYPE>
class FixedSizeAllocator {
public:
	enum { FSA_DEFAULT_SIZE = 100 };

	struct FSA_ELEMENT {
		USER_TYPE UserType;
		FSA_ELEMENT *pPrev;
		FSA_ELEMENT *pNext;
	};

public:
	FixedSizeAllocator(unsigned int MaxElements = FSA_DEFAULT_SIZE)
		: m_pFirstUsed(NULL), m_MaxElements(MaxElements) {
			char *pMem = new char[m_MaxElements * sizeof(FSA_ELEMENT)];
			m_pMemory = (FSA_ELEMENT*) pMem;
			memset(m_pMemory, 0, sizeof(FSA_ELEMENT) * m_MaxElements);
			m_pFirstFree = m_pMemory;
			m_pFirstFree->pPrev = NULL;
			FSA_ELEMENT *pElement = m_pFirstFree;
			for (unsigned int i = 0; i < m_MaxElements; i++) {
				pElement->pPrev = pElement-1;
				pElement->pNext = pElement+1;
				pElement++;
			}
			(pElement-1)->pNext = NULL;
		}

	~FixedSizeAllocator() {
		delete [] (char*) m_pMemory;
	}

	USER_TYPE *alloc() {
		FSA_ELEMENT *pNewNode = NULL;
		if (!m_pFirstFree) {
			return NULL;
		} else {
			pNewNode = m_pFirstFree;
			m_pFirstFree = pNewNode->pNext;
			if (pNewNode->pNext) {
				pNewNode->pNext->pPrev = NULL;
			}
			pNewNode->pPrev = NULL;
			if (m_pFirstUsed == NULL) {
				pNewNode->pNext = NULL;
			} else {
				m_pFirstUsed->pPrev = pNewNode;
				pNewNode->pNext = m_pFirstUsed;
			}
			m_pFirstUsed = pNewNode;
		}
		return reinterpret_cast<USER_TYPE*>(pNewNode);
	}

	void free(USER_TYPE *user_data) {
		FSA_ELEMENT *pNode = reinterpret_cast<FSA_ELEMENT*>(user_data);
		if (pNode->pPrev) {
			pNode->pPrev->pNext = pNode->pNext;
		} else {
			m_pFirstUsed = pNode->pNext;
		}
		if (pNode->pNext) {
			pNode->pNext->pPrev = pNode->pPrev;
		}
		if (m_pFirstFree == NULL) {
			m_pFirstFree = pNode;
			pNode->pPrev = NULL;
			pNode->pNext = NULL;
		} else {
			m_pFirstFree->pPrev = pNode;
			pNode->pNext = m_pFirstFree;
			m_pFirstFree = pNode;
		}
	}

	void Debug() {
		printf("free list ");
		FSA_ELEMENT *p = m_pFirstFree;
		while (p) {
			printf("%x!%x ", p->pPrev, p->pNext);
			p = p->pNext;
		}
		printf("\n");
		printf("used list ");
		p = m_pFirstUsed;
		while (p) {
			printf("%x!%x ", p->pPrev, p->pNext);
			p = p->pNext;
		}
		printf("\n");
	}

	USER_TYPE *GetFirst() {
		return reinterpret_cast<USER_TYPE*>(m_pFirstUsed);
	}

	USER_TYPE *GetNext(USER_TYPE *node) {
		return reinterpret_cast<USER_TYPE*>((reinterpret_cast<FSA_ELEMENT*>(node))->pNext);
	}

private:
	FSA_ELEMENT *m_pFirstFree;
	FSA_ELEMENT *m_pFirstUsed;
	FSA_ELEMENT *m_pMemory;
	unsigned int m_MaxElements;
};

#endif // FSA_H
