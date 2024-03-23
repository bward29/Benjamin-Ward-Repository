/*
* NAME: Benjamin Ward
* FILE: bigint.cpp
* COURSE: CS23001
* DATE: 02/12/24
*/
#include "bigint.hpp"
#include <iostream>
#include <cassert>

void bigint::initializeArray() { // function to initialize the array elements to zero
       	for (int i = 0; i < CAPACITY; ++i) {
        numArray[i] = 0; // numArray stores the digits of the large integers
    }
}

bigint::bigint() { 
    initializeArray(); // initializes all elements of numArray to zero
}

bigint::bigint(int numbers) { // constructor that converts an integer into a bigint
    initializeArray();
   
    int i = 0;
    while (numbers > 0) { // extracts digits from the integer and stores them in the array
        numArray[i] = numbers % 10;
        numbers = numbers / 10;
        i++;
    }
}

bigint::bigint(const char charArray[]) { // constructor to convert a character array into a bigint
    initializeArray();
    	
    	int length = 0;
	for (; charArray[length] != '\0'; ++length) // finds the length of the character array

    	for (int i = 0; i < length; ++i) { // converts char to int and stores them in reverse order
        	numArray[i] = charArray[length - 1 - i] - '0';
    }
}

void bigint::debugPrint(std::ostream& out) const { // debug print function to display the contents of the bigint array
    
	for (int i = CAPACITY - 1; i >= 0; --i) {
     		out << numArray[i] << "|"; // prints the content of numArray in reverse order seperated by "|"
    }
    

    out << std::endl;
}

std::ostream& operator<<(std::ostream& out, const bigint& obj) { // overloaded output stream operator to print the big int
    
	int i = CAPACITY - 1;
	while (i >= 0 && obj.numArray[i] == 0)
        --i;

    int count = 0;
    for (; i >= 0; --i) {
    	out << obj.numArray[i];

       	 if (++count % 80 == 0) // inserts a newline after every 80 characters
         	out << std::endl;
    }

    if (count == 0)
    	out << '0';

    return out;
}

std::istream& operator>>(std::istream& in, bigint& obj) { // overloaded input stream operator to read the big int from input
   
    obj.initializeArray();

    char character; // declares variable character and it is used to read characters from istream
    int index = 0; 

    while (in >> character && character != ';') { // reads characters from the input stream until a semicolon is encountered

        if (character >= '0' && character <= '9') { // shifts exisiting digits to the left before adding new ones at the beginning

            for (int n = index; n > 0; --n) {
                obj.numArray[n] = obj.numArray[n - 1];
            }

            obj.numArray[0] = character - '0'; // converts the character to an integer, then stores at the beginning 
            ++index;
        }
    }

    return in; 
}

bool bigint::operator==(const bigint& obj) const { // overloaded equality operator to compare two bigint objects
   
       	for (int i = 0; i < CAPACITY; ++i) {
        
	    if (numArray[i] != obj.numArray[i])
            	return false; 
    }

    return true;
}

bigint bigint::operator+(const bigint& obj) const { // overloaded addition operator to perform addition of two bigint objects
    bigint result;
    int carry = 0;

    for (int i = 0; i < CAPACITY; ++i) {
        int sum = numArray[i] + obj.numArray[i] + carry; 
        result.numArray[i] = sum % 10; // stores the single digit
        carry = sum / 10; // calculates for the next digit
    }

    return result; // returns result, which contains the sum of two bigint objects
}

bigint bigint::timesDigit(int x) const {
	bigint temp;
	int rem = 0;
	int result = 0;

	for (int i = 0; i < CAPACITY; i++) { // multiply each digit in numArray by x
		rem = numArray[i] * x + rem; // multiply digit by x and adds previous remainder
		result = rem % 10; // calculate the current digit of the result
		rem /= 10; // updates the remainder for the next iteration
		temp.numArray[i] = result; // stores the result in temp
	}

	return temp;
}

bigint bigint::times10(int x) const {
	bigint temp; // create a temporary bigint to store the result


	for (int i = CAPACITY -1 - x; i >= 0; i--) { // shifts digits in numArray to the left by x digits
		temp.numArray[i + x] = numArray[i];
	}

	for (int j = 0; j < x; j++) { // fills the lower x positions with zeros
		temp.numArray[j] = 0;
	}

	return temp; // returns final result
}

bigint bigint::operator*(bigint & obj) const {
	bigint result = 0; // initializes the result to 0

	for (int i = 0; i < CAPACITY; i++) { // performs multiplication digit by digit and accumulates results
		
		result = result + (timesDigit(obj.numArray[i])).times10(i); // multiplies current digit with obj's corresponding digit and shifts the result to the left by i positions
	}

	return result; // returns final result
}


int bigint::operator[](int index) const { // overloaded subscript operator to access individual digits of the big int

	if (index < 0 || index >= CAPACITY) { // checks if the value of index out of bounds;  if true, the function returns zero
        return 0;
    }

    return numArray[index];
}
