

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L
// Pre: L != null
int length(List L);

// index()
// Returns index of the cursor element
// Pre: L != null
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: length() > 0, L != null
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: length() > 0, L != null
int back(List L);

// get()
// Returns cursor element.
// Pre: length() > 0, index() >= 0, L != null
int get(List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
// Pre: A != null, B != null
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets this List to its original empty state
// Pre: L != null
void clear(List L);

// moveFront()
// Places cursor under the front element, does nothing if empty
// Pre: L != null
void moveFront(List L);

// moveBack()
// Places cursor under the back element, does nothing if empty
// Pre: L != null
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward
// front of List. If cursor is defined and at front, cursor becomes undefined.
// If cursor is undefined, does nothing
// Pre: L != null
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one step toward
// back of List. If cursor is defined and at back, cursor becomes undefined.
// If cursor is undefined, does nothing
// Pre: L != null
void moveNext(List L);

// prepend(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
// Pre: L != null
void prepend(List L, int data);

// append(int data)
// Insert new element into this List. If List is non-empty,
// insertion takes place after back element
// Pre: L != null
void append(List L, int data);

// insertBefore(int data)
// Insert new element before cursor.
// Pre: length() > 0, index() >= 0, L != null
void insertBefore(List L, int data);

// insertAfter(int data)
// Insert new element after cursor.
// Pre: length() > 0, index() >= 0, L != null
void insertAfter(List L, int data);

// deleteFront()
// Deletes the front element.
// Pre: length() > 0, L != null
int deleteFront(List L);

// deleteBack()
// Deletes the back element.
// Pre: length() > 0, L != null
void deleteBack(List L);

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length() > 0; index() >= 0, L != null
void delete(List L);


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
// Pre: L != null,
void printList(FILE* out, List L);

// copyList()
// Returns a new List representing the same integer sequence
// Pre: L != null
List copyList(List L);


#endif
