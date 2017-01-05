// ------------------------------------- poly.cpp -----------------------------
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


#include <iostream>
#include "poly.h"

using namespace std;

// ------------------------ Default Constructor -------------------------------
// Zero polynomial, initialized to 0x^0 if PolyX given no parameters but
// array size will be 1 which at index 0 stores value 0
// ----------------------------------------------------------------------------
Poly::Poly()
{
	exp = 1;
	coeffPtr = new int[exp]; // sets array size 1, starting at 0
	coeffPtr[0] = 0; // at index 0 of array, value is 0
} //end of Default Constructor

// ------------------ (One Paramter:coefficient) Constructor ------------------
// Takes one parameter, coefficient and initialized, example +2x^0 if PolyB(2).
// Array size is still set to 1, but value is the coefficent in parameter.
// ----------------------------------------------------------------------------
Poly::Poly(int c)
{
	exp = 1;
	coeffPtr = new int[exp]; // array size 1 at index 0 is coefficient
	coeffPtr[0] = c;
} // end of (One Paramter:coefficient) Constructor

// --------------- (Two Paramter: coefficient, exponent) Constructor ----------
// Takes two parameter and coefficient and an exponent, example is +5x^7 if 
// PolyA(5,7). Array size is exponent + 1, setting paramater coefficent value,
// if exponent is 0 then both coefficient and exponent set to 0.
// ----------------------------------------------------------------------------
Poly::Poly(int c, int e)
{
	if (e < 0) // if exponent is less then 0, coefficient and exp set to 0
	{
		e = 0;
		c = 0;
	}

	exp = e + 1;
	coeffPtr = new int[exp]; // array size +1 to adjust for starting at 0

	for (int i = 0; i < exp; i++)
	{
		coeffPtr[i] = 0; // all values before are 0 in array
	}

	coeffPtr[e] = c; // last index of array with highest exp given coeff value
} // end of (Two Paramter: coefficient, exponent) Constructor

// ------------------------ Copy Constructor ----------------------------------
// Deep copy made, exact copy of poly object in parameter into array. 
// ----------------------------------------------------------------------------
Poly::Poly(const Poly &a)
{
	exp = a.exp; // sets size to poly in parameter passed in
	coeffPtr = new int[exp]; // array has same size as parameter Poly

	for (int i = 0; i < exp; i++)
	{
		coeffPtr[i] = a.coeffPtr[i]; // goes through Poly, adds to lhs poly
	}
} // end of Copy Constructor

// ------------------------ Destructor ----------------------------------------
// Sets to NULL and deletes the *coeffPtr.
// ----------------------------------------------------------------------------
Poly::~Poly()
{
	delete[] coeffPtr;
	coeffPtr = NULL; // set to NULL to stop memory problems.
} // end of Destructor

// ------------------------ Operator Overload + -------------------------------
// Operator Overload +, add together lhs and rhs Poly to return their Sum.
// ----------------------------------------------------------------------------
Poly Poly::operator+(const Poly &rhs) const
{
	int newExp;
	if (exp > rhs.exp) // check if left poly is > right, assings size of left
	{
		newExp = exp;
	}

	else
	{
		newExp = rhs.exp;
	}

	Poly sum(0, newExp); // sum of polynomials

	for (int i = 0; i < sum.exp; i++) // array of sum sizes 
	{
		*(sum.coeffPtr + i) = 0; // sets all to 0 in array
	}

	for (int i = 0; i < exp; i++) // lhs
	{
		*(sum.coeffPtr + i) += *(coeffPtr + i); // adds left side to sum 
	}

	for (int i = 0; i < rhs.exp; i++) // rhs
	{
		*(sum.coeffPtr + i) += *(rhs.coeffPtr + i); // adds right side to sum 
	}

	return sum; // returns sum
} // end of Operator Overload +

// ------------------------ Operator Overload - -------------------------------
// Operator Overload -, subtracts lhs and rhs Poly to return new total.
// New size is adjusted if needed to be.
// ----------------------------------------------------------------------------
Poly Poly::operator-(const Poly &rhs) const
{
	int newExp;
	if (exp > rhs.exp) // checks for greater size between left and right side
	{ 
		newExp = exp;
	}

	else 
	{
		newExp = rhs.exp;
	}

	Poly sub(0, newExp); // poly sub to be returned

	for (int i = 0; i < sub.exp; i++)
	{
		*(sub.coeffPtr + i) = 0; // first sets all in sub to 0
	}

	for (int i = 0; i < exp; i++)
	{
		*(sub.coeffPtr + i) += *(coeffPtr + i); // subs left side
	}

	for (int i = 0; i < rhs.exp; i++)
	{
		*(sub.coeffPtr + i) -= *(rhs.coeffPtr + i); // sub right side
	}

	return sub; // returns sub
} // end of Operator Overload -

// ------------------------ Operator Overload * -------------------------------
// Operator Overload *, multiplies together lhs and rhs Poly to return their 
// multiplied total.
// ----------------------------------------------------------------------------
Poly Poly::operator*(const Poly &rhs) const
{
	int newExp;
	newExp = ((exp + rhs.exp) - 2); // new size -2 due to constructors + 1 each

	Poly mult(0, newExp);

	for (int i = 0; i < exp; i++) // left side polynomial
	{
		for (int j = 0; j < rhs.exp; j++) // right side
		{ // multiplies together and inserts at new index
		  *(mult.coeffPtr + (i + j)) += *(coeffPtr + i) * *(rhs.coeffPtr + j); 
		}
	}
	return mult; // returns mult
} // end of Operator Overload *

// ------------------------ Operator Overload += ------------------------------
// Operator Overload +=, assigns the left polyninomial the sum of two 
// polynomials added together. Addition of two polynomials.
// ----------------------------------------------------------------------------
Poly& Poly::operator+=(const Poly &rhs) 
{
	*this = (*this) + rhs; // left + right side
	return (*this);
} // end of Operator Overload +=

// ------------------------ Operator Overload -= ------------------------------
// Operator Overload -=, assigns the left polyninomial the subtracted total of
// the two polynomials subtracted together. Subtraction of two polynomials.
// ----------------------------------------------------------------------------
Poly& Poly::operator-=(const Poly &rhs) 
{
	*this = (*this) - rhs; // left - right side
	return (*this);
} // end of Operator Overload -=

// ------------------------ Operator Overload *= ------------------------------
// Operator Overload *=, assigns the left polyninomial the multiplied total of 
// the two polynomials multiplied together. Multiplication of two polynomials
// ----------------------------------------------------------------------------
Poly& Poly::operator*=(const Poly &rhs) 
{
	*this = (*this) * rhs; // left * right side
	return (*this);
} // end of Operator Overload *=

// ------------------------ Operator Overload = -------------------------------
// Operator Overload =, assigns the left polynomial the right polynomial
// ----------------------------------------------------------------------------
Poly& Poly::operator=(const Poly &rhs)
{
	if (*this == rhs)  // checks to see if their equal
	{
		return *this;
	}

	delete[] coeffPtr;
	coeffPtr = NULL; // deletes coeffPtr and sets to NULL

	exp = rhs.exp;
	coeffPtr = new int[exp]; // right poly size equals new size of coeffPtr

	for (int i = 0; i < exp; i++)
	{  // Everything from right side now gets copied onto left side
		*(coeffPtr + i) = *(rhs.coeffPtr + i); 
	}

	return *this; // returned left to be what righ was
} // end of Operator Overload =

// ------------------------ Operator Overload == ------------------------------
// Operator Overload =, examines two polynomials and returns true if they are
// alike, and a false if they are not the same
// ----------------------------------------------------------------------------
bool Poly::operator==(const Poly &rhs) const
{ 
	// maxSize set to larger poly's size, left vs right side
	int maxSize = (exp > rhs.exp) ? exp : rhs.exp; 

	for (int i = 0; i < maxSize; i++)
	{ 
		if (getCoeff(i) != rhs.getCoeff(i)) // // getCoeff help account for 0's
			return false; // returns false if right side does not match left. 
	}
	return true; // right matches left, returns true
} // end of Operator Overload ==

// ------------------------ Operator Overload != ------------------------------
// Operator Overload !=, examines two polynomials and returns true if they are 
// NOT alike, else a false is returned.
// ----------------------------------------------------------------------------
bool Poly::operator!=(const Poly &rhs) const
{
	return !(*this == rhs); // returns false if right side not equal to left
} // end of Operator Overload !=


// ------------------------ getCoeff ------------------------------------------
// getCoefficient will return the coefficient value of index choosen. Any index
// not accurate in range will have a 0 returned.
// ----------------------------------------------------------------------------
int Poly::getCoeff(int e) const
{ 
	// check to see if wanted index e is negative or out of range of array
	if ((e < 0) || (e >= exp)) 
	{
		return 0;  // returns 0 since index wanted is out of bounds
	}

	else
	{
		return *(coeffPtr + e);  // else if in range retrieves value at index e
	}
} // end of getCoeff

// ------------------------ setCoeff ------------------------------------------
// setCoefficient accepts a coefficient and exponent and inserts into array. 
// Any array not large enough, size will be increased to make correct room.
// ----------------------------------------------------------------------------
void Poly::setCoeff(int c, int e)
{
	if (e < 0) //	check if exponent negative
	{
		e = 0;
		c = 0; // exponent enter negative, sets exp and coefficient to 0
	}

	if (e < exp) // array is large enough, sets size immediatly
	{
		*(coeffPtr + e) = c; // sets coefficient into desired index
	}

	else
	{
		int *temp = new int[e + 1]; // temp array
		
		for (int i = 0; i < exp; i++) // adds into temp array original poly's values
		{
			*(temp + i) = *(coeffPtr + i); 
		}
		for (int i = exp; i < e + 1; i++)
		{
			*(temp + i) = 0; // adds to temp where current left filling with 0s
		}
		*(temp + e) = c; // last index in temp array set to wanted coefficient
		
		delete[] coeffPtr;
		coeffPtr = NULL; // coeffPtr delted and set to NULL
		
		coeffPtr = temp;
		temp = NULL; // temp set to NULL
		
		exp = e + 1; // e+ 1 set to size accounted for index at 0
	}
} // end of setCoeff

// ------------------------ Operator Overload >> ------------------------------
// Operator Overload (>>), sets coefficient with setCoeff into array
// position depending on exponent entered. This is Input.
// ----------------------------------------------------------------------------
istream &operator>>(istream &inStream, Poly &inP) 
{
	int coefficient;
	int exponent;
	inStream >> coefficient >> exponent;  // input of coefficient and exponent

	// while -1 -1 is not inputed set and ask again
	while (!((coefficient == -1) && (exponent == -1))) 
	{
		inP.setCoeff(coefficient, exponent);
		inStream >> coefficient >> exponent;
	}
	return inStream; // returns inputed data
} // end of Operator Overload >>

// ------------------------ Operator Overload << ------------------------------
// Operator Overload (<<), prints out entire Poly expression. Check to 
// sure there is values left to print, if the array is 0 or empty prints 0
// ----------------------------------------------------------------------------
ostream &operator<<(ostream &outStream, const Poly &outP)
{
	bool empty = true; // an empty array is all 0 polynomial

	for (int i = outP.exp - 1; i >= 0; i--) // start array backwards
	{
		if (*(outP.coeffPtr + i) != 0)
		{
			empty = false;

			outStream << " "; // first space between coefficients

			if (*(outP.coeffPtr + i) > 0)
			{
				outStream << "+"; // only positive coefficients receive + 
			}

			outStream << *(outP.coeffPtr + i); // coefficent at index output
			
			if (i != 0 && i != 1)
			{ // prints "x^" except for 0 or 1 coefficient
				outStream << "x^" << i;  
			}
			
			if (i == 1)
			{ // if exponent is 1, makes sense to only print 'x'
				outStream << "x"; 
			}
		}
	}

	if (empty == false)
	{
		return outStream; // returns the outstream because array not empty
	}

	else
	{
		return outStream << " 0"; // else just returns 0
	}
} // end of Operator Overload <<
