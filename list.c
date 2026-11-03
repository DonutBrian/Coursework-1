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

// FUNCTION #1: Create a new empty list on the Heap and make itemload e the default itemload. This default itemload
// can be returned by other functions in case no itemload is selected. No itemload is selected in an empty list.

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

// FUNCTION #2: Free up the list and all the data in it. Does not have to run in O(1).

void freeList(list *xs) {

    while (xs -> current != xs -> none) {

        node *nextNode = xs -> current -> next;
        free(xs -> current);
        xs -> current = nextNode;

    }

    free(xs -> none);
    free(xs);

}

// FUNCTIONS #3/#4: Set the current itemload to the first itemload or to the last
// itemload of the list, respectively. If the list has no itemloads the functions do nothing
// and no itemload is selected.

void first(list *xs) {

    if (xs -> none -> next != xs -> none) {

        xs -> current = xs -> none -> next;

    }
}

void last(list *xs) {

    if (xs -> none -> back != xs -> none) {

        xs -> current = xs -> none -> back;

    }
}

// FUNCTION #5: Returns true if no itemload is selected.
// Otherwise it returns false.

bool none(list *xs) {

    return xs -> current == xs -> none;

}

// FUNCTION #6: Make the itemload in the node following the currently selected itemload the current itemload
// and return true. If after is called while the last itemload is the current itemload, then no itemload is
// selected and true is returned. If the function is called while no itemload
// is selected then the function does nothing and returns false.

bool after(list *xs) {

    if (xs -> current == xs -> none) return false;

    xs -> current = xs -> current -> next;
    return true;

}

// FUNCTION #7: Make the itemload in the node before the currently selected itemload the current itemload
// and return true. If before is called while the first itemload is the current itemload, then no itemload
// is selected and true is returned. If the function is called while no itemload
// is selected then the function does nothing and returns false.

bool before(list *xs) {

    if (xs -> current == xs -> none) return false;

    xs -> current = xs -> current -> back;
    return  true;

}

// FUNCTION #8: Return the current itemload. If get is called and no itemload is selected
// then the default itemload is returned.

itemload get(list *xs) {

    return xs -> current -> x;

}

// FUNCTION #9: Set the current itemload to be the value of argument x and return true. If set is called
// while no itemload is selected then the function does nothing and returns false.

bool set(list *xs, itemload x) {

    if (xs -> current == xs -> none) return false;

    xs -> current -> x = x;
    return true;
}

// FUNCTION #10: Insert a new node with itemload x after the current itemload and make it the current itemload.
// If insertAfter is called while no itemload is selected then the function inserts the itemload into a new node
// placed at the very beginning of the list.

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

// FUNCTION #11: Insert a new node with itemload x before the current itemload and make it the current itemload.
// If insertAfter is called while no itemload is selected then the function inserts the itemload into a new node
// placed at the very end of the list.

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

// FUNCTION #12: Delete the node with the current itemload and make its successor the current itemload,
// then return true. If deleteToAfter is called while the last itemload is the current itemload then
// the node with the last itemload is deleted, no itemload is selected, and true is returned. If
// deleteToAfter is called while no itemload is selected then the function does nothing and returns false.

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

// FUNCTION #13: Delete the node with the current itemload and make its predecessor the current itemload,
// then return true. If deleteToBefore is called while the first itemload is the current itemload then
// the node with thw first itemload is deleted, no itemload is selected, and true is returned. If
// deleteToBefore is called while no itemload is selected then the function does nothing and returns false.

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

// FUNCTION #14: Invert the sequence of the list items, that is make the list start with the node and itemload that originally had
// the last position and ensure that itemloads originally situated before a itemload will now be situated after it, and vice versa.
// The selected itemload is not changed by this function. Does not have to run in O(1).

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