// Nathan Smith
// Assignment 6 part 4
// Using the quadratic equation, the user is asked to enter real values (floating point)
// of a, b, and c, then the program finds the two real roots and displays them.
// for x1 = (-b + sqrt( (b^2 - (4 * a * c) ) / (2 * a)
// for x2 = (-b - sqrt( (b^2 - (4 * a * c) ) / (2 * a)

// Notes:
// 		Input and output are done in C++ using function calls from assembly.
// 		All calcuation is done in assembly.

#include <iostream>
#include <iomanip>
using namespace std;

void EnterInput();
void DisplayResults();

// Variable names come from the typical quadratic expression: ax^2 + bx + c
float a = 3, b, c, x1, x2, root_part, neg_b;
float two = 2, four = 4, neg_one = -1;

int main()
{
	// Lines commented to keep track of stack values
	_asm
	{
		call EnterInput
		
		// Square Root section (stored for later use)
		;doing sqrt ( (b * b) - ( 4 * a * c) )		(root part)
		fld b				;st = b
		fld b				;st[1] = b
		fmul				;st = b * b
		fld c				;st = c, st[1] = b * b
		fld a				;st = a, st[1] = c, st[2] = b * b
		fld four			;st = 4, st[1] = a, st[2] = c, st[3] = b * b
		fmul				;st = a * 4, st[1] = c, st[2] = b * b
		fmul				;st = (4 * a * c), st[1] = b * b
		fsub				;st = (b * b) - ( 4 * a * c)
		fsqrt				;st = sqrt( (b * b) - ( 4 * a * c) )
		fstp root_part		;root_part = sqrt( (b * b) - ( 4 * a * c) )
		
		// Calculating -b
		;doing -b
		fld b				;st = b
		fld neg_one			;st = -1, st[1] = b
		fmul				;st = -b
		fstp neg_b			;neg_b = -b
		
		// Calculating first root (positive)
		;doing x1
		fld neg_b			;st = -b
		fld root_part		;st = sqrt( (b * b) - ( 4 * a * c) ), st[1] = -b
		fadd				;st = [-b + sqrt( (b * b) - ( 4 * a * c) )]
		fld two				;st = 2, st[1] = [-b + sqrt( (b * b) - ( 4 * a * c) )]
		fld a				;st = a, st[1] = 2, st[2] = [-b + sqrt( (b * b) - ( 4 * a * c) )]
		fmul				;st = (2 * a), st[1] = [-b + sqrt( (b * b) - ( 4 * a * c) )]
		fdiv				;st = [-b + sqrt((b * b) - ( 4 * a * c))] / [2 * a] 
		fstp x1				;x1 = [-b + sqrt((b * b) - ( 4 * a * c))] / [2 * a]

		// Calculating first root (negative)
		;doing x2
		fld neg_b			;st = -b
		fld root_part		;st = sqrt( (b * b) - ( 4 * a * c) ), st[1] = -b
		fsub				;st = -b - sqrt( (b * b) - ( 4 * a * c) )
		fld two				;st = 2, st[1] = [-b - sqrt( (b * b) - ( 4 * a * c) )]
		fld a				;st = a, st[1] = 2, st[2] = [-b - sqrt( (b * b) - ( 4 * a * c) )]
		fmul				;st = (2 * a), st[1] = [-b - sqrt( (b * b) - ( 4 * a * c) )]
		fdiv				;st = [-b - sqrt((b * b) - ( 4 * a * c))] / [2 * a] 
		fstp x2				;x1 = [-b - sqrt((b * b) - ( 4 * a * c))] / [2 * a]

		call DisplayResults
	}
	system("PAUSE");
	return 0;
}

void EnterInput()
{
	cout << "To see the roots of ax^2 + bx + c = 0,\n"
		 << "Enter a, b, and c: ";
	cin >> a >> b >> c;
}

void DisplayResults()
{
	cout << showpoint << fixed << setprecision(2)
		 << "X1 = " << x1 << endl
		 << "X2 = " << x2 << endl;
}