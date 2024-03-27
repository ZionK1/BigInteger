/******************************************************************************
 * Zion Kang, zkang5
 * 2023 Spring CSE101 PA6
 * List.cpp
 * Source code for List ADT
 * ***************************************************************************/
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state
List::List() {
    frontDummy = new Node(12345);
    backDummy = new Node(12345);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor for List ADT
List::List(const List& L) {
    // Create new List in empty state
    frontDummy = new Node(12345);
    backDummy = new Node(12345);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // Load elements of L into this List
    Node *N = L.frontDummy->next;
    while (N != L.backDummy) { // until we reach back sentinel Node
        this->insertBefore(N->data);
        N = N->next;
    }
}

// Destructor for List ADT
List::~List() {
    this->clear(); // delete all elements in List
    delete(frontDummy); // deallocate mem for frontDummy 
    delete(backDummy); // deallocate mem for backDummy 
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements; // num_elements denotes length of List
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if( length()==0 ){ // check precondition
      throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if( length()==0 ){ // check precondition
      throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (position() >= length()) { // check precondition
        throw std::range_error("List: peekNext(): out of range in List");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (position() <= 0) { // check precondition
        throw std::range_error("List: peekPrev(): out of range in List");
    }
    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (num_elements > 0) { // loop thru list while there are Nodes
        eraseAfter(); // delete Node after cursor (which is between frontDummy and next Node)
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy; // cursor should point back to frontDummy
    afterCursor = frontDummy->next; // cursor should point next to node after frontDummy
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = length();
    beforeCursor = backDummy->prev; // cursor should point back to node before backDummy
    afterCursor = backDummy; // cursor should point next to backDummy
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (position() >= length()) { // check precondition
        throw std::range_error("List: moveNext(): out of range in List");
    }
    pos_cursor += 1; // inc cursor index
    beforeCursor = beforeCursor->next; // move right one node
    afterCursor = afterCursor->next; // move right one node
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (position() <= 0) { // check precondition
        throw std::range_error("List: movePrev(): out of range in List");
    }
    pos_cursor -= 1;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *N = new Node(x); // create new node N with data x
    beforeCursor->next = N; // node before cursor points next to N
    afterCursor->prev = N; // node after cursor points back to N
    N->prev = beforeCursor; // N points back to node before cursor
    N->next = afterCursor; // N points next to node after cursor
    afterCursor = N; // node after cursor is now N
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node *N = new Node(x); // create new node N with data x
    beforeCursor->next = N; // node before cursor points next to N
    afterCursor->prev = N; // node after cursor points back to N
    N->prev = beforeCursor; // N points back to node before cursor
    N->next = afterCursor; // N points next to node after cursor
    beforeCursor = N; // node after cursor is now N
    num_elements += 1;
    pos_cursor += 1; // inc cursor index to compensate for new Node
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (position() >= length()) { // check precondition
        throw std::range_error("List: setAfter(): out of range in List");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (position() <= 0) { // check precondition
        throw std::range_error("List: setBefore(): out of range in List");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if (position() >= length()) { // check precondition
        throw std::range_error("List: setAfter(): out of range in List");
    }
    Node *currAfter = afterCursor;
    beforeCursor->next = afterCursor->next; // beforeCursor points next to node after afterCursor
    afterCursor->next->prev = beforeCursor; // node after afterCursor points back to beforeCursor
    afterCursor = afterCursor->next; // update afterCursor
    delete currAfter; // free old afterCursor
    num_elements -= 1; // decrement num elements
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (position() <= 0) { // check precondition
        throw std::range_error("List: setBefore(): out of range in List");
    }
    Node *currBefore = beforeCursor;
    afterCursor->prev = beforeCursor->prev; // afterCursor points back to node before beforeCursor
    beforeCursor->prev->next = afterCursor; // node before beforeCursor points next to afterCursor
    beforeCursor = beforeCursor->prev; // update beforeCursor
    delete currBefore; // free old beforeCursor
    num_elements -= 1; // decrement num elements
    pos_cursor -= 1;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    while (position() < length()) {
        int curr = moveNext();
        if (curr == x) {
            return position();
        }
    }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    while (position() > 0) {
        int curr = movePrev();
        if (curr == x) {
            return position();
        }
    }
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    // main loop that removes dups
    int new_pos = position(), index = 1; // save initial pos_cursor and update as we go
    for (Node* curr = frontDummy->next; curr != backDummy; curr = curr->next) { // loop thru List
        //debug print: cout << "curr->data = " << curr->data << endl;
        // move the cursor to right after the curr element we're checking dups for
        moveFront();
        for (int i = 0; i < index; i += 1) {
            moveNext();
        }
        //debug print: cout << "pos_cursor = " << pos_cursor << endl;
        while (curr->next != backDummy) { // loop checking elements after curr
            int dup = findNext(curr->data); // checks for next dup in List
            //debug print: cout << "dup = " << dup << endl;
            if (dup != -1) { // if there is a dup
                if (position() <= new_pos) { // if dup index is <= updated pos_cursor
                    new_pos -= 1; // update position of cursor
                    //debug print: cout << "new_pos = " << new_pos << endl;
                }
                eraseBefore(); // cursor is after dup, so erase element before cursor
            } // no dup found, break and move onto next element in List
            else {
                break;
            }
        }
        index += 1;
    }

    // after cleaning up dups, move cursor to updated position
    moveFront();
    for (int i = 0; i < new_pos; i += 1) {
        moveNext();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
// following Queue.c example
List List::concat(const List& L) const {
    List C;
    Node* N = this->frontDummy->next;
    Node* M = L.frontDummy->next;
    while( N!=this->backDummy ){
        C.insertBefore(N->data);
        N = N->next;
    }
    while( M!=L.backDummy ){
        C.insertBefore(M->data);
        M = M->next;
    }
    // move cursor back to front, since we used insertBefore to append elements
    C.moveFront();
    return C;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
// following Queue.c example
std::string List::to_string() const {
    Node* N = nullptr;
    std::string s = "(";

    for(N=frontDummy->next; N!=backDummy->prev; N=N->next){
        s += std::to_string(N->data)+", ";
    }
    s += std::to_string(N->data) + ")";

    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
// following Queue.c example
bool List::equals(const List& R) const {
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = ( this->length() == R.length() );
    N = this->frontDummy;
    M = R.frontDummy;
    while( eq && N!=backDummy ){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
// following Queue.c example
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
// following Queue.c example
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
// following Queue.c example
List& List::operator=( const List& L ) {
    if( this != &L ){ // not self assignment
        // make a copy of L
        List temp = L;

        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}
