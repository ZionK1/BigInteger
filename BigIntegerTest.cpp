/******************************************************************************
 * Zion Kang, zkang5
 * 2023 Spring CSE101 PA6
 * BigInteger.cpp
 * Test Cases for BigInteger ADT
 * ***************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>
#include <assert.h>
#include "BigInteger.h"

using namespace std;

int main(){
   // create BigInts to work with
   string a = "123456789890123892038109829390821309823";
   string b = "-330293847502398475";
   string c = "988958956895698569000000000389239229292000000000092929292";
   BigInteger A (a);
   BigInteger B (b);
   BigInteger C (c);

   // check print statements
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   // testing compare
   assert(A.compare(B) == 1);
   assert(A.compare(C) == -1);

   // test negate
   A.negate();
   assert(A.sign() == -1);
   A.negate();
   assert(A.sign() == 1);

   // testing makezero
   BigInteger x (A);
   x.makeZero();
   BigInteger y;
   assert(x.compare(y) == 0);

   // now checking arithmetic
   BigInteger D = A+B; // check add
   cout << "D = (A + B) = " << D << endl;

   BigInteger E = B+A; 
   cout << "E = (B + A) = " << E << endl;
   assert(D.compare(E) == 0);

   BigInteger F = D-E; // check sub
   cout << "F = (D - E) = " << F << endl;
   assert(F.compare(x) == 0);

   BigInteger G = 34*A + 45*B + 56*C; // check mult
   cout << "G = (34*A + 45*B + 56*C) = " << G << endl;

   BigInteger H = A*B; 
   cout << "H = (A * B) = " << H << endl;

   BigInteger I = B*A;
   cout << "I = (B * A) = " << I << endl;

   BigInteger J = G*H*I;
   cout << "J = (G * H * I) = " << J << endl << endl;

   // check equality
   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl;
   cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
   cout << "(H==I) = " << ((H==I)?"True":"False") << endl << endl;

   // check other overriden ops
   A += B; 
   B -= C;
   C *= J;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl << endl;
   cout << "A*B*C*D*E*G*H*I*J = " << A*B*C*D*E*G*H*I*J << endl << endl;

   // test exceptions
   try{
      BigInteger J = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   return EXIT_SUCCESS;
}
