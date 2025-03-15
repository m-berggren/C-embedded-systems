// --- Include section
#include <stdio.h>

// --- Function declarations
int gcd(int a, int b); // find the greatest common divisor
int addFraction(int a, int c, int b, int d); // add two fractions
int subFraction(int a, int c, int b, int d); // subtract two fractions
int mulFraction(int a, int c, int b, int d); // multiply two fractions

// --- Main section

int main(void) {

	int user_input[4];

	for (int i = 0; i < 4; i++) {
		scanf("%d", &user_input[i]);
	}
	
	/* Results from below functions are printed as simplified fractions */

    // Run function that prints sum of two fractions
	addFraction(user_input[0], user_input[1], user_input[2], user_input[3]);
	// Run function that subtract two fractions
	subFraction(user_input[0], user_input[1], user_input[2], user_input[3]);
	// Run function that multiplies two fractions
    mulFraction(user_input[0], user_input[1], user_input[2], user_input[3]);
}

// --- Function definitions

// Function that finds the greatest common divisor
int gcd(int a, int b) {
    
    // If a is less than 0 turn it to positive -(-a) = a
	a = (a < 0) ? -a : a;
	// If less than 0 turn value to be positive
	b = (b < 0) ? -b : b;
	
    // runs until a % b = 0
	while (b != 0) {
	    // stores temp variable
		int temp = b;
		// modulus remainder
		b = a % b;
		// stores temp as a
		a = temp;
	}
    // return a, this is the value where a % b gives 0
	return a;
}

// Function that adds two fractions
int addFraction(int a, int c, int b, int d) {

    // If denumerators are zero the division is invalid
	if (b == 0 || d == 0) {
		return 0;
	}

    // Define numerator & denominator
	int numerator = (a * d) + (b * c);
	int denumerator = b * d;

    // Calculate divisor through the greatest common divisor
	int divisor = gcd(numerator, denumerator);

    // Divide numerator & denumerator with gcd
	numerator /= divisor;
	denumerator /= divisor;

    // Print out the result
	printf("addFraction: %d/%d\n", numerator, denumerator);
	return 1;
}

int subFraction(int a, int c, int b, int d) {
    // If denumerators are zero the division is invalid
	if (b == 0 || d == 0) {
		return 0;
	}

    // Define numerator & denominator
	int numerator = (a * d) - (b * c);
	int denumerator = b * d;

    // Calculate divisor through the greatest common divisor
	int divisor = gcd(numerator, denumerator);

    // Divide numerator & denumerator with gcd
	numerator /= divisor;
	denumerator /= divisor;

    // Print out the result
	printf("subFraction: %d/%d\n", numerator, denumerator);
	return 1;
}

int mulFraction(int a, int c, int b, int d) {
    // If denumerators are zero the division is invalid
	if (b == 0 || d == 0) {
		return 0;
	}
	
	// Define numerator & denominator
	int numerator = a * c;
	int denumerator = b * d;

    // Calculate divisor through the greatest common divisor
	int divisor = gcd(numerator, denumerator);

    // Divide numerator & denumerator with gcd
	numerator /= divisor;
	denumerator /= divisor;

    // Print out the result
	printf("mulFraction: %d/%d\n", numerator, denumerator);
	return 1;
	
}

