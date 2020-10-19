

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      while( length(*pL) != 0 ) {
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L
// Pre: L != null
int length(List L) {
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// index()
// Returns index of the cursor element
// Pre: L != null
int index(List L) {
	if( L==NULL ){
	   printf("List Error: calling index() on NULL List reference\n");
	   exit(EXIT_FAILURE);
	}
	return(L->index);
}

// front()
// Returns the value at the front of L.
// Pre: length() > 0, L != null
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length <= 0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: length() > 0, L != null
int back(List L) {
	if( L==NULL ){
	   printf("List Error: calling back() on NULL List reference\n");
	   exit(EXIT_FAILURE);
	}
	if( L->length <= 0 ){
	   printf("List Error: calling back() on an empty List\n");
	   exit(EXIT_FAILURE);
	}
	return (L->back->data);
}

// get()
// Returns cursor element.
// Pre: length() > 0, index() >= 0, L != null
int get(List L) {
	if( L==NULL ){
		printf("List Error: calling get() on NULL List reference\n");
	    exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		printf("List Error: calling get() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		printf("List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->cursor->data);
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
// Pre: A != null, B != null
int equals(List A, List B) {
	if( A==NULL || B==NULL){
		printf("List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (length(A) != length(B)) {
		return 0;
	}
	Node curr1 = A->front;
	Node curr2 = B->front;
	for (int i = 0; i < length(A); i++) {
		if (curr1->data != curr2->data) {
			return 0;
		}
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
	return 1;

}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this List to its original empty state
// Pre: L != null
void clear(List L) {
	if (L == NULL) {
		printf("List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	while( length(L) != 0 ) {
		deleteFront(L);
	}
	L->length = 0;
	L->index = -1;


}

// moveFront()
// Places cursor under the front element, does nothing if empty
// Pre: L != null
void moveFront(List L) {
	if (L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		return;
	}
	L->cursor = L->front;
	L->index = 0;
}

// moveBack()
// Places cursor under the back element, does nothing if empty
// Pre: L != null
void moveBack(List L) {
	if (L == NULL) {
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		return;
	}
	L->cursor = L->back;
	L->index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward
// front of List. If cursor is defined and at front, cursor becomes undefined.
// If cursor is undefined, does nothing
// Pre: L != null
void movePrev(List L) {
	if (L == NULL) {
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor == L->front) {
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	L->cursor = L->cursor->prev;
	L->index--;
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward
// back of List. If cursor is defined and at back, cursor becomes undefined.
// If cursor is undefined, does nothing
// Pre: L != null
void moveNext(List L) {
	if (L == NULL) {
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	L->cursor = L->cursor->next;
	L->index++;
}

// prepend(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
// Pre: L != null
void prepend(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(data);
	if (L->length == 0) {
		L->front = L->back = N;
	} else {
		if (L->length == 1) {
			N->next = L->front;
			L->front->prev = N;
			L->back = L->front;
			L->front = N;
		} else {
			N->next = L->front;
			L->front->prev = N;
			L->front = N;
		}
		if (L->cursor != NULL) {
			L->index++;
		}
	}
	L->length++;

}

// append(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element
// Pre: L != null
void append(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(data);
	if (L->length == 0) {
		L->front = L->back = N;
	} else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;

	}
	L->length++;
}


// insertBefore(int data)
// Insert new element before cursor.
// Pre: length() > 0, index() >= 0, L != null
void insertBefore(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		printf("List Error: calling insertBefore() on length() <= 0\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		printf("List Error: calling insertBefore() on index() < 0\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->front) {
		prepend(L, data);
		return;
	}
	Node before = L->cursor->prev;
	Node N = newNode(data);
	before->next = N;
	N->next = L->cursor;
	L->cursor->prev = N;
	N->prev = before;
	L->length++;
	L->index++;
}

// insertAfter(int data)
// Insert new element after cursor.
// Pre: length() > 0, index() >= 0, L != null
void insertAfter(List L, int data) {
	if (L == NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		printf("List Error: calling insertAfter() on length() <= 0\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		printf("List Error: calling insertAfter() on index() < 0\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->back) {
		append(L, data);
		return;
	}
	Node N = newNode(data);
	Node after = L->cursor->next;
	after->prev = N;
	N->prev = L->cursor;
	L->cursor->next = N;
	N->next = after;
	L->length++;
}

// deleteFront()
// Deletes and returns the front element.
// Pre: length() > 0, L != null
int deleteFront(List L) {
	Node N = NULL;
	int n = L->front->data;
	if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		printf("List Error: calling deleteFront() on length() <= 0\n");
		exit(EXIT_FAILURE);
	}
	N = L->front;
	if (L->cursor == L->front) {
		L->cursor = NULL;
		L->index = -1;
	}
	if (L->length == 1) {
		L->front = L->back = NULL;
		L->index = -1;
	} else {
		if (L->length == 2) {
			L->front = L->back;
			L->front->prev = NULL;
			L->front->next = NULL;
		} else {
			L->front = L->front->next;
			L->front->prev = NULL;
		}
		if (L->cursor != NULL) {
			L->index--;
		}
	}
	L->length--;
	freeNode(&N);
	return n;
}

// deleteBack()
// Deletes the back element.
// Pre: length() > 0, L != null
void deleteBack(List L) {
	Node N = NULL;
	if (L == NULL) {
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		printf("List Error: calling deleteBack() on length() <= 0\n");
		exit(EXIT_FAILURE);
	}
	N = L->back;
	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->index = -1;
	}
	if (L->length == 1) {
		L->front = L->back = NULL;
		L->index = -1;
	} else {
		if (L->length == 2) {
			L->back = L->front;
			L->front->prev = NULL;
			L->front->next = NULL;
		} else {
			L->back = L->back->prev;
			L->back->next = NULL;
		}

	}
	L->length--;
	freeNode(&N);

}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length() > 0; index() >= 0, L != null
void delete(List L) {
	Node N = NULL;
	if (L == NULL) {
		printf("List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length <= 0) {
		printf("List Error: calling delete() on length() <= 0\n");
		exit(EXIT_FAILURE);
	}
	if (L->index < 0) {
		printf("List Error: calling delete() on index() < 0\n");
		exit(EXIT_FAILURE);
	}
	N = L->cursor;
	if (L->cursor == L->front) {
		deleteFront(L);
		return;
	}
	if (L->cursor == L->back) {
		deleteBack(L);
		return;
	}
	Node previous = L->cursor->prev;
	Node after = L->cursor->next;
	previous->next = after;
	after->prev = previous;
	L->length--;
	L->cursor = NULL;
	L->index = -1;
	freeNode(&N);
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to outfile.
// Pre: L != null,
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for(N = L->front; N != NULL; N = N->next){
     fprintf(out, "%d ", N->data);
   }
   fprintf(out, "\n");

}

// copyList()
// Returns a new List representing the same integer sequence
// Pre: L != null
List copyList(List L) {
	if (L == NULL) {
		printf("List Error: calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	List A = newList();
	Node N = L->front;

	while (N != NULL) {
		append(A, N->data);
		N = N->next;
	}
	return A;
}


