// ------------------------------------- poly.h -----------------------------
// Programmer: Jasenko Cordalija. 
// Course Number: CS343A
// Creation Date: 01/09/2016
// Date of Last Modification: 01/16/2016
// ----------------------------------------------------------------------------
// Purpose - poly Class implements internal reprisentation of a polynomial as
// an array of terms. The polynomials can be manipulated to subtract, add, 
// multiple, assign to eachother. The constructor will receive 0-2 inputs, a 
// coefficient and the exponent expected. Indexs of the array equal to the 
// exponent of the coefficient which is the value stored inside the index. 
// Intial memory for array is dynamically allocated for array. If any exponents
// are negative, 0 is returned for coefficient and exponent. 
// ----------------------------------------------------------------------------
// Special Notes and Assumptions - Assumed that any negtive exponents that are 
// given will return 0 for coefficient and 0 for exponent. Assumed that all 
// data will be accurate and correct so that there is no need for special error 
// handling.
//-----------------------------------------------------------------------------

#ifndef POLY_H
#define POLY_H
#include <iostream>

using namespace std;

class Poly 
{
	// ------------------------ Operator Overload >> --------------------------
	// Operator Overload (>>), sets coefficient with setCoeff into array
	// position depending on exponent entered. This is Input.
	// ------------------------------------------------------------------------
	friend istream& operator>>(istream &instream, Poly &inP);

	// ------------------------ Operator Overload << --------------------------
	// Operator Overload (<<), prints out entire Poly expression. Check to 
	// sure there is values left to print, if the array is 0 or empty prints 0.
	// ------------------------------------------------------------------------
	friend ostream& operator<<(ostream &outstream, const Poly &outP);

public:

	// ------------------------ Default Constructor ---------------------------
	// Zero polynomial, initialized to 0x^0 if PolyX given no parameters but
	// array size will be 1 which at index 0 stores value 0.
	// ------------------------------------------------------------------------
	Poly();

	// ------------------ (One Paramter:coefficient) Constructor --------------
	// Takes one parameter, coefficient and initialized, example +2x^0 if 
	// PolyB(2). Array size is still set to 1, but value is the coefficent in 
	// parameter.
	// ------------------------------------------------------------------------
	Poly(int coeff);

	// --------------- (Two Paramter: coefficient, exponent) Constructor ------
	// Takes two parameter and coefficient and an exponent, example is +5x^7 if 
	// PolyA(5,7). Array size is exponent + 1, setting paramater coefficent 
	// value, if exponent is 0 then both coefficient and exponent set to 0.
	// ------------------------------------------------------------------------
	Poly(int coeff, int exp);

	// ------------------------ Copy Constructor ------------------------------
	// Deep copy made, exact copy of poly object in parameter into array. 
	// ------------------------------------------------------------------------
	 Poly(const Poly& P); 

	 // ------------------------ Destructor -----------------------------------
	 // Sets to NULL and deletes the *coeffPtr.
	 // -----------------------------------------------------------------------
	 ~Poly();

	 // ------------------------ Operator Overload + --------------------------
	 // Operator Overload +, add together lhs and rhs Poly to return their Sum.
	 // -----------------------------------------------------------------------
	 Poly operator+(const Poly &rhs) const;

	 // ------------------------ Operator Overload - --------------------------
	 // Operator Overload -, subtracts lhs and rhs Poly to return new total.
	 // New size is adjusted if needed to be.
	 // -----------------------------------------------------------------------
	 Poly operator-(const Poly &rhs) const;

	 // ------------------------ Operator Overload * --------------------------
	 // Operator Overload *, multiplies together lhs and rhs Poly to return 
	 // their multiplied total.
	 // -----------------------------------------------------------------------
	 Poly operator*(const Poly &rhs) const;

	 // ------------------------ Operator Overload += -------------------------
	 // Operator Overload +=, assigns the left polyninomial the sum of two 
	 // polynomials added together. Addition of two polynomials.
	 // -----------------------------------------------------------------------
	 Poly& operator+=(const Poly &rhs);

	 // ------------------------ Operator Overload -= -------------------------
	 // Operator Overload -=, assigns the left polyninomial the subtracted 
	 // total of the two polynomials subtracted together. Subtraction of two
	 // polynomials.
	 // -----------------------------------------------------------------------
	 Poly& operator-=(const Poly &rhs);

	 // ------------------------ Operator Overload *= -------------------------
	 // Operator Overload *=, assigns the left polyninomial the multiplied 
	 // total of the two polynomials multiplied together. Multiplication of 
	 // two polynomials.
	 // -----------------------------------------------------------------------
	 Poly& operator*=(const Poly &rhs);

	 // ------------------------ Operator Overload = --------------------------
	 // Operator Overload =, assigns the left polynomial the right polynomial.
	 // -----------------------------------------------------------------------
	 Poly& operator=(const Poly &rhs);

	 // ------------------------ Operator Overload == -------------------------
	 // Operator Overload =, examines two polynomials and returns true if they
	 // are alike, and a false if they are not the same.
	 // -----------------------------------------------------------------------
	 bool operator==(const Poly &rhs) const;

	 // ------------------------ Operator Overload != -------------------------
	 // Operator Overload !=, examines two polynomials and returns true if they 
	 // are NOT alike, else a false is returned.
	 // -----------------------------------------------------------------------
	 bool operator!=(const Poly &rhs) const;

	 // ------------------------ getCoeff -------------------------------------
	 // getCoefficient will return the coefficient value of index choosen. 
	 // Any index not accurate in range will have a 0 returned.
	 // -----------------------------------------------------------------------
	 int getCoeff(int exp) const;

	 // ------------------------ setCoeff -------------------------------------
	 // setCoefficient accepts an coefficient and exponent and inserts into 
	 // array. Any array not large enough, size will be increased to make 
	 // enough room.
	 // -----------------------------------------------------------------------
	 void setCoeff(int coeff, int exp);

private:
	int *coeffPtr; // coefficient
	int exp; // exponent/ degree, THIS IS FOR SIZE of array
};

#endif
