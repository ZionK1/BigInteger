/******************************************************************************
 * Zion Kang, zkang5
 * 2023 Spring CSE101 PA6
 * ListTest.c
 * Test cases for List ADT
 * ***************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include<cassert>
#include"List.h"

using namespace std;

int main(){
    // create Lists A and B
    int n = 20, i = 0;
    List A, B;
    for(i = 1; i <= n; i += 1){
        A.insertAfter(i);
        B.insertBefore(i);
    }
    cout << endl;
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << endl;

    // basic checks for Lists A and B
    assert(A.length() == 20);
    assert(B.length() == 20);
    assert(A.front() == 20);
    assert(B.back() == 20);
    assert(A.back() == 1);
    assert(B.front() == 1);

    // check cursor move functions
    A.moveBack();
    B.moveFront();
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;

    // check lists for equality
    cout << endl;
    cout << "A==B is " << (A==B?"true":"false") << endl;

    // printing 1-9 in B
    cout << endl << "B: ";
    for(i = 1; i <= 9; i++){
        cout << B.moveNext() << " ";
    }
    cout << endl << "B.position() = " << B.position() << endl;

    // printing 20-11 in A
    cout << endl << "A: ";
    for(i = 1; i <= 9; i++){
        cout << A.movePrev() << " ";
    }
    cout << endl << "A.position() = " << A.position() << endl;
    cout << endl;
    

    // testing erase and find functions
    B.moveFront();
    cout << "B.findNext(7) = " << B.findNext(7) << endl;
    cout << B << endl;
    B.eraseBefore();
    B.eraseAfter();
    cout << endl;
    cout << "B after erasing: " << endl << B << endl;
    cout << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << endl;
    cout << "B.findPrev(2) = " << B.findPrev(2) << endl;
    B.eraseBefore();
    B.eraseAfter();
    cout << "B after erasing 1, 2" << endl << B << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << endl;
    cout << "findNext(20) and position() should be the same"<< endl; 
    cout << B.findNext(20) << endl; 
    cout << B.position() << endl;
    cout << endl;
    cout << "findPrev(20) and position() should be the same"<< endl; 
    cout << B.findPrev(20) << endl;
    cout << B.position() << endl;
    cout << endl;

    // adding random elements to List to test cleanup
    for( i=10; i>=1; i--){
        A.insertAfter(i);
        A.movePrev();
    }
    A.moveFront();
    for( i=5; i>=1; i--){
        A.insertBefore(i);
        A.moveNext();
    }
    cout << "A = " << A << endl;
    for( i=1; i<=15; i++){
        A.moveNext();
    }
    cout << A.position() << endl;
    A.cleanup();
    cout << "A = " << A << endl;
    cout << A.position() << endl;
    cout << endl;

    List E = A;
    cout << "E==A is " << (E==A?"true":"false") << endl; 

    cout << endl;

    // testing concat and peek functions
    List F = A.concat(B);
    cout << "F = " << F << endl;
    cout << "F.length(): " << F.length() << endl;
    cout << "F.front(): " << F.front() << endl;
    cout << "F.back(): " << F.back() << endl;
    cout << "F.position(): " << F.position() << endl;
    for( i=1; i<=7; i++){
        cout << "peekNext: " << F.peekNext() << endl;
        F.insertBefore(-i);
        cout << "peekPrev: " << F.peekPrev() << endl;
        cout << F.moveNext() << endl;
    }
    cout << "F = " << F << endl;

    // testing set functions
    A.moveBack();
    cout << endl << "A: " << endl;
    for(i = 1; i <= A.length(); i++){
        A.setBefore(21 - i);
        A.movePrev();
    }
    cout << A << endl;

    B.moveFront();
    cout << endl << "B: " << endl;
    for(i = 1; i <= B.length(); i++){
        B.setAfter(i);
        B.moveNext();
    }
    cout << B << endl;

    cout << endl;

    return( EXIT_SUCCESS );
}