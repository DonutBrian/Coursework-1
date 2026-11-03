// Implementation of the list module.
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each node in a doubly linked list is stored in this structure.
struct node { struct node *back; itemload x; struct node *next; };
typedef struct node node;

// A list is to be represented as a circular list. It has to contain a doubly linked list
// of nodes that hold an itemload each and one special sentinel node that links to the two ends of the list.
// The none field holds this sentinel node. It has a default itemload, must always be present for
// a list and always sits before the first itemload node and after the last itemload node. For a list
// that holds no nodes the back and next fields of the sentinel node point to the sentinel
// node itself. The current node refers to the currently selected itemload node in the list. If
// the current node is the none node then no itemload is selected.
struct list { node *none, *current; };
typedef struct list list;




// ---------- ADD YOUR 14 FUNCTIONS HERE TO SOLVE THE COURSEWORK ----------

// Github Repository for code: https://github.com/DonutBrian/Coursework-1

list *newList(itemload e) {

    list *xs = malloc(sizeof(list));
    node *sentinel = malloc(sizeof(node));
    sentinel -> x = e;

    xs -> none = sentinel;
    xs -> current = sentinel;

    sentinel -> next = sentinel;
    sentinel -> back = sentinel;

    return xs;
}

// Explanation

/*

 28: Created a new list with a pointer called listPointer, then using the malloc function assigns the pointer to the address in memory where the allocated memory for the new list is stored.
 29: Created a pointer called sentinel which points to a newly allocated node.
 30: Assigned the itemLoad x for the sentinel node as e.
 32: The none pointer in the new list is assigned to the sentinel node.
 33: Due to the list upon initialisation being empty, the current pointer also gets assigned to the sentinel node.
 35-36: Created a cyclical linked list where the list loops back to the sentinel node when empty whether you go to the next node or the previous node.
 38: Returns the listPointer, which holds the memory address of the new list.

*/


void freeList(list *xs) {

    while (xs -> current != xs -> none) {

        node *nextNode = xs -> current -> next;
        free(xs -> current);
        xs -> current = nextNode;

    }

    free(xs -> none);
    free(xs);

}

// Explanation

/*

 58 Created a while loop that checks to whether the current node has reached sentinel node.
 60: Created a new pointer called nextNode which points to the memory address of the next node.
 61: Frees the memory allocated to the current node.
 62: Assigns the current node to the next node.
 60-62: This was done to ensure the program remembers the next node when the current node gets freed.
 66: Frees the memory allocated to the sentinel node.
 67: Frees the memory allocated to the list.

*/


void first(list *xs) {

    if (xs -> none -> next != xs -> none) {

        xs -> current = xs -> none -> next;

    }
}

// Explanation

/*

 88: If statement that checks if the next pointer from the sentinel points to the sentinel, if it does then nothing happens.
 90: If the next node is not on the sentinel node, the current pointer gets set back to the first node.

*/


void last(list *xs) {

    if (xs -> none -> back != xs -> none) {

        xs -> current = xs -> none -> back;

    }
}

// Explanation
/*
 107: If statement that checks if the previous pointer from the sentinel node points to the sentinel, if it does then nothing happens.
 109: if the previous node is not on the sentinel node, the current pointer gets set back to the last node.
*/

bool none(list *xs) {

    return xs -> current == xs -> none;

}

// Explanation

/*

 122: Since a comparison statement already returns a true or false, a simple return of a comparison statement would output true if the current pointer is pointing at the sentinel node, and false if it wasn't.

*/

bool after(list *xs) {

    if (xs -> current == xs -> none) return false;

    xs -> current = xs -> current -> next;
    return true;

}

// Explanation

/*

 136: Checks if the current pointer is pointing to the sentinel node, if it is return false.
 138-139: Otherwise the current pointer moves on to the next node and returns true.

*/

bool before(list *xs) {

    if (xs -> current == xs -> none) return false;

    xs -> current = xs -> current -> back;
    return  true;

}

// Explanation

/*

 154: Checks if the current pointer is pointing to the sentinel node, if it is return false.
 156-157: Otherwise the current pointer moves back to the previous node and returns true.

*/

itemload get(list *xs) {

    return xs -> current -> x;

}

// Explanation

/*

 172: returns the current node's itemload, if no node is selected ie. its on the sentinel node, the default value will be returned in this case e.

*/

bool set(list *xs, itemload x) {

    if (xs -> current == xs -> none) return false;

    xs -> current -> x = x;
    return true;
}

// Explanation

/*

 186: Checks if the current node is the sentinel node, if it is false is returned.
 188-189: Otherwise the current node's itemload gets changed to the value of x.

*/

void insertAfter(list *xs, itemload x) {

    node *newNode = malloc(sizeof (node));
    newNode -> x = x;

    if (xs -> current  == xs -> none) {

        if (xs -> current -> next == xs -> none) {

            xs -> current -> back = newNode;
            newNode -> next = xs -> current;

        }

        else {

            xs -> current -> next -> back = newNode;
            newNode -> next = xs -> current -> next;

        }

        xs -> current -> next = newNode;
        newNode -> back = xs -> current;

    }

    else if ( xs -> current -> next == xs -> none) {

        xs -> current -> next = newNode;
        newNode -> back = xs -> current;
        xs -> none -> back = newNode;
        newNode -> next = xs -> none;

    }

    else {

        xs -> current -> next -> back = newNode;
        newNode -> next = xs -> current -> next;
        xs -> current -> next = newNode;
        newNode -> back = xs -> current;

    }

    xs -> current = newNode;

}

void insertBefore(list *xs, itemload x) {

    node *newNode = malloc(sizeof (node));
    newNode -> x = x;

    if (xs -> current  == xs -> none) {

        if (xs -> current -> next == xs -> none) {

            xs -> current -> back = newNode;
            newNode -> next = xs -> current;
            xs -> current -> next = newNode;
            newNode -> back = xs -> current;

        }

        else {

            xs -> current -> back -> next = newNode;
            newNode -> back = xs -> current -> back;
            xs -> current -> back = newNode;
            newNode -> next = xs -> current;

        }
    }

    else if ( xs -> current -> back == xs -> none) {

        xs -> current -> back = newNode;
        newNode -> next = xs -> current;
        xs -> none -> next = newNode;
        newNode -> back = xs -> none;

    }

    else {

        xs -> current -> back -> next = newNode;
        newNode -> back = xs -> current -> back;
        xs -> current -> back = newNode;
        newNode -> next = xs -> current;

    }

    xs -> current = newNode;

}

bool deleteToAfter(list *xs) {

    if (xs -> current == xs -> none) {

        return false;

    }

    xs -> current -> next -> back = xs -> current -> back;
    xs -> current -> back -> next = xs -> current -> next;

    node *tempPointer = xs->current->next;

    free (xs -> current);
    xs -> current = tempPointer;
    return true;

}

bool deleteToBefore(list *xs) {

    if (xs -> current == xs -> none) {

        return false;

    }

    xs -> current -> next -> back = xs -> current -> back;
    xs -> current -> back -> next = xs -> current -> next;

    node *tempPointer = xs->current->back;

    free (xs -> current);
    xs -> current = tempPointer;
    return true;

}

void reverse(list *xs) {

    node *currentTempNode = xs -> current;

    do {

        node *nextTempNode = xs -> current -> next;
        xs -> current -> next = xs -> current -> back;
        xs -> current -> back = nextTempNode;
        xs -> current = xs -> current -> next;

    }
    while ( xs -> current != currentTempNode);

    xs -> current = currentTempNode;
}

// Test the list module, using int as the itemload type. Strings are used as
// 'pictograms' to describe lists. Single digits represent itemloads and the '|' symbol
// in front of a digit indicates that this is the current itemload. If the '|' symbol
// is at the end of the string then 'none' of the itemloads is selected. The strings
// "|37", "3|7", "37|" represent a list of two itemloads, with the current position
// at the first itemload, the last itemload, and a situation where 'none' of the itemloads
// is selected.
#ifdef test_list

// Build a list from a pictogram, with -1 as the default itemload.
// Note: You do not need to understand this function to solve the coursework.
list *build(char *s) {
  list *xs = malloc(sizeof(list));
    int n = strlen(s);
    node *nodes[n];
    for (int i = 0; i < n; i++) nodes[i] = malloc(sizeof(node));
    for (int i = 0; i < n; i++) nodes[i]->next = nodes[(i + 1) % n];
    for (int i = 1; i < n + 1; i++) nodes[i % n]->back = nodes[i - 1];
    xs->none = nodes[0];
    xs->none->x = -1;
    node *p = xs->none->next;
    for (int i = 0; i < strlen(s); i++) {
      if (s[i] == '|') xs->current = p;
      else {
        p->x = s[i] - '0';
        p = p->next;
      }
    }
  return xs;
}

// Destroy a list which was created with the build function and which matches a pictogram.
// Note: You do not need to understand this function to solve the coursework.
void destroy(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i-1]->next;
  for (int i = 0; i < n; i++) free(nodes[i]);
  free(xs);
}

// Check that a list matches a pictogram.
// Note: You do not need to understand this function to solve the coursework.
bool match(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i - 1]->next;
  if (nodes[n - 1]->next != xs->none) return false;
    for (int i = 1; i < n; i++) {
      if (nodes[i]->back != nodes[i - 1]) return false;
    }
  node *p = xs->none->next;
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == '|') {
      if (p != xs->current) return false;
    }
    else {
      if (p->x != s[i] - '0') return false;
      p = p->next;
    }
  }
  return true;
}

// The tests use an enumeration to say which function to call.
enum { First, Last, None, After, Before, Get, Set, InsertAfter, InsertBefore, DeleteToAfter, DeleteToBefore, Reverse};
typedef int function;

// A replacement for the library assert function.
void assert(int line, bool b) {
  if (b) return;
  printf("The test on line %d fails.\n", line);
  exit(1);
}

// Call a given function with a possible integer argument, returning a possible
// integer or boolean result (or -1).
// Note: You do not need to understand this function to solve the coursework.
int call(function f, list *xs, int arg) {
  int result = -1;
  switch (f) {
    case None: result = none(xs); break;
    case First: first(xs); break;
    case Last: last(xs); break;
    case After: result = after(xs); break;
    case Before: result = before(xs); break;
    case Get: result = get(xs); break;
    case Set: result = set(xs, arg); break;
    case InsertAfter: insertAfter(xs, arg); break;
    case InsertBefore: insertBefore(xs, arg); break;
    case DeleteToBefore: result = deleteToBefore(xs); break;
    case DeleteToAfter: result = deleteToAfter(xs); break;
    case Reverse: reverse(xs); break;
    default: assert(__LINE__, false);
  }
  return result;
}

// Check that a given function does the right thing. The 'in' value is passed to
// the function or is -1. The 'out' value is the expected result, or -1.
bool check(function f, int in, char *before, char *after, int out) {
  list *xs = build(before);
  int result = call(f, xs, in);
  //check your list has indeed a circular list structure
  assert(__LINE__, (xs->none == xs->none->next->back));
  assert(__LINE__, (xs->none == xs->none->back->next));
  //check that your function works correctly as the tests demand
  bool ok = (match(xs, after) && (result == out));
  destroy(xs, after);
  return ok;
}

// Test newList, and call freeList. The test for freeList is that the memory
// leak detector in the -fsanitize=address or -fsanitize=leak compiler option
// reports no problems.
void testNewList(void) {
    list *xs = newList(-1);
    //check circular list structure
    assert(__LINE__, (xs->none == xs->none->next));
    assert(__LINE__, (xs->none == xs->none->back));
    //check that an empty list is produced with a sentinel correctly
    assert(__LINE__, match(xs, "|"));
    freeList(xs);
}

// Test the various 14 functions.
void testFirst(void) {
    assert(__LINE__, check(First, -1, "|", "|", -1));
    assert(__LINE__, check(First, -1, "|37", "|37", -1));
    assert(__LINE__, check(First, -1, "3|7", "|37", -1));
    assert(__LINE__, check(First, -1, "37|", "|37", -1));
}

void testLast(void) {
    assert(__LINE__, check(Last, -1, "|", "|", -1));
    assert(__LINE__, check(Last, -1, "|37", "3|7", -1));
    assert(__LINE__, check(Last, -1, "3|7", "3|7", -1));
    assert(__LINE__, check(Last, -1, "37|", "3|7", -1));
}

void testNone(void) {
    assert(__LINE__, check(None, -1, "|", "|", true));
    assert(__LINE__, check(None, -1, "|37", "|37", false));
    assert(__LINE__, check(None, -1, "3|7", "3|7", false));
    assert(__LINE__, check(None, -1, "37|", "37|", true));
}

void testAfter(void) {
    assert(__LINE__, check(After, -1, "|", "|", false));
    assert(__LINE__, check(After, -1, "|37", "3|7", true));
    assert(__LINE__, check(After, -1, "3|7", "37|", true));
    assert(__LINE__, check(After, -1, "37|", "37|", false));
}

void testBefore(void) {
    assert(__LINE__, check(Before, -1, "|", "|", false));
    assert(__LINE__, check(Before, -1, "|37", "37|", true));
    assert(__LINE__, check(Before, -1, "3|7", "|37", true));
    assert(__LINE__, check(Before, -1, "37|", "37|", false));
}

void testGet(void) {
    assert(__LINE__, check(Get, -1, "|", "|", -1));
    assert(__LINE__, check(Get, -1, "|37", "|37", 3));
    assert(__LINE__, check(Get, -1, "3|7", "3|7", 7));
    assert(__LINE__, check(Get, -1, "37|", "37|", -1));
}

void testSet(void) {
    assert(__LINE__, check(Set, 5, "|", "|", false));
    assert(__LINE__, check(Set, 5, "|37", "|57", true));
    assert(__LINE__, check(Set, 5, "3|7", "3|5", true));
    assert(__LINE__, check(Set, 5, "37|", "37|", false));
}

void testInsertAfter(void) {
    assert(__LINE__, check(InsertAfter, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "|37", "3|57", -1));
    assert(__LINE__, check(InsertAfter, 5, "3|7", "37|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "37|", "|537", -1));
}

void testInsertBefore(void) {
    assert(__LINE__, check(InsertBefore, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertBefore, 5, "|37", "|537", -1));
    assert(__LINE__, check(InsertBefore, 5, "3|7", "3|57", -1));
    assert(__LINE__, check(InsertBefore, 5, "37|", "37|5", -1));
}

void testDeleteToAfter(void) {
    assert(__LINE__, check(DeleteToAfter, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|37", "|7", true));
    assert(__LINE__, check(DeleteToAfter, -1, "3|7", "3|", true));
    assert(__LINE__, check(DeleteToAfter, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|5", "|", true));
}

void testDeleteToBefore(void) {
    assert(__LINE__, check(DeleteToBefore, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|37", "7|", true));
    assert(__LINE__, check(DeleteToBefore, -1, "3|7", "|3", true));
    assert(__LINE__, check(DeleteToBefore, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|5", "|", true));
}

void testReverse(void) {
    assert(__LINE__, check(Reverse, -1, "|", "|", -1));
    assert(__LINE__, check(Reverse, -1, "|37", "7|3", -1));
    assert(__LINE__, check(Reverse, -1, "3|7", "|73", -1));
    assert(__LINE__, check(Reverse, -1, "37|", "73|", -1));
}

int main(void) {
    testNewList();
    testFirst();
    testLast();
    testNone();
    testAfter();
    testBefore();
    testGet();
    testSet();
    testInsertAfter();
    testInsertBefore();
    testDeleteToAfter();
    testDeleteToBefore();
    testReverse();
    printf("List module tests run OK.\n");
    return 0;
}
#endif