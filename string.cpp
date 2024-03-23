// NAME: Benjamin Ward
// FILE: string.cpp 
// COURSE: CS23001
// DATE: 03/02/2024

#include "string.hpp"
#include <iostream>
#include <cassert>
#include <vector>

// Default constructor
String::String() {
    stringSize = 1;
    str = new char[stringSize];
    str[0] = '\0'; // Null-terminate the string
}

// Constructor with a single character
String::String(char ch) {
    stringSize = (ch == '\0') ? 1 : 2;
    str = new char[stringSize];
    str[0] = ch;
    str[1] = '\0'; // Null-terminate the string
}

// Constructor with a character array
String::String(const char chArray[]) {
    int i = 0;
    while (chArray[i] != '\0')
        ++i;

    stringSize = i + 1;
    str = new char[stringSize];

    for (i = 0; chArray[i] != '\0'; ++i)
        str[i] = chArray[i];
    str[stringSize - 1] = '\0'; // Null-terminate the string
}

// Copy constructor
String::String(const String& rhs) {
    stringSize = rhs.stringSize;
    str = new char[stringSize];
    for (int i = 0; i < stringSize - 1; ++i)
        str[i] = rhs.str[i];
    str[stringSize - 1] = '\0'; // Null-terminate the string
}

// Destructor
String::~String() {
    delete[] str;
}

// Swap function to exchange contents with another String
void String::swap(String& rhs) {
    std::swap(str, rhs.str);
    std::swap(stringSize, rhs.stringSize);
}

// Assignment operator
String& String::operator=(String rhs) {
    swap(rhs);
    return *this;
}

// Method to get the length of the string
int String::length() const {
    int len = 0;
    while (str[len] != '\0')
        ++len;
    return len;
}

// Method to get the capacity of the string
int String::capacity() const {
    return stringSize - 1;
}

// Concatenation operator
String operator+(String lhs, const String& rhs) {
    return (lhs += rhs);
}

// Compound concatenation operator
String& String::operator+=(const String& rhs) {
    int offset = length();
    int newSize = offset + rhs.length();
    char* temp = new char[newSize + 1];

    for (int i = 0; i < offset; ++i)
        temp[i] = str[i];
    for (int i = 0; i < rhs.length(); ++i)
        temp[offset + i] = rhs.str[i];

    temp[newSize] = '\0'; // Null-terminate the string
    delete[] str;
    str = temp;
    stringSize = newSize + 1; // Update string size

    return *this;
}

// Indexing operator (const version)
char String::operator[](int i) const {
    if (i < 0)
        i = 0;
    return str[i];
}

// Indexing operator
char& String::operator[](int i) {
    return str[i];
}
bool operator<(const char lhs[], const String& rhs) {
	return String(lhs) < rhs;
}
bool operator<(char lhs, const String&rhs) {
	return String(lhs) < rhs;
}
// Overloaded less-than operator for comparing two String objects
bool String::operator<(const String& rhs) const {
    // Determine the minimum length between the two strings
    int minLength = length() < rhs.length() ? length() : rhs.length();

    // Iterate through the characters of both strings up to the minimum length
    for (int i = 0; i < minLength; ++i) {
        // Compare characters at the same position in both strings
        if (str[i] != rhs.str[i])
            return str[i] < rhs.str[i]; // If characters are different, return the result of comparison
    }

    // If the loop completes without finding a difference in characters,
    // compare the lengths of the strings to determine the result
    return length() < rhs.length();
}


bool operator==(char lhs, const String& rhs) {
    return String(lhs) == rhs;
}

// Comparison operator for equality
bool operator==(const char lhs[], const String& rhs) {
    return String(lhs) == rhs;
}

// Comparison operator for equality
bool String::operator==(const String& rhs) const {
    if (length() == rhs.length()) {
        for (int i = 0; str[i] != '\0' && rhs[i] != '\0'; ++i) {
            if (str[i] != rhs[i])
                return false;
        }
        return true;
    }
    return false;
}

bool operator<=(const String& lhs, const String& rhs) {
	return (lhs < rhs || lhs == rhs);
}

// Output stream operator
std::ostream& operator<<(std::ostream& out, const String& rhs) {
    return out << rhs.str;
}

// Input stream operator
std::istream& operator>>(std::istream& in, String& rhs) {
    const int buffSize = 1024;
    char buff[buffSize];
    in >> buff;
    rhs = String(buff);
    return in;
}
// Method to find a substring in the string starting from a given position
int String::findstr(int pos, const String& rhs) const {
    int foundAt = -1;
    if (pos == 0 && str[0] == rhs[0]) {
        foundAt = 0;
        for (int j = 0; j < rhs.length(); ++j) {
            if (str[foundAt + j] != rhs[j]) {
                foundAt = -1;
                break;
            }
        }
        return foundAt;
    }

    for (int i = pos; i <= length(); ++i) {
        if (str[i] == rhs[0]) {
            foundAt = i;
	    for (int j = 1; j < rhs.length(); ++j) {
		    if (str[i+j] != rhs[j]) {
			    foundAt = -1;
			    break;
		    }
	    }
	    if (foundAt != -1)// If the match is found, return the index
		    return foundAt;
	}
    }
    return foundAt; // Return -1 if not found
}

// Find the index of the first occurrence of character 'ch' starting from 'begin'
int String::findch(int begin, char ch) const {
    for (int i = begin; i < length(); ++i) {
        if (str[i] == ch) 
            return i; // Return the index if 'ch' is found
    }
    return -1; // Return -1 if 'ch' is not found
}

// Extracts a substring from index 'lhs' to index 'rhs'
String String::substr(int lhs, int rhs) const {
    // Handle invalid indices or empty string
    if (rhs < 0 || lhs >= length() || lhs > rhs)
        return String();

    // Adjust 'rhs' if it's greater than or equal to the length of the string
    if (rhs >= length())
        rhs = length() - 1;

    // Calculate the length of the substring
    int len = rhs - lhs + 1;

    // Allocate memory for the substring
    char* temp = new char[len + 1];

    // Copy characters from the original string to the substring
    for (int i = 0; i < len; ++i)
        temp[i] = str[lhs + i];
    temp[len] = '\0'; // Null-terminate the substring

    // Return the substring as a String object
    return String(temp);
}
// Split the string into substrings based on the separator character
std::vector<String> String::split(char separator) const {
    std::vector<String> substrings; // New variable to hold the split substrings
    int start = 0;
    int position = 0;

    while (position <= length()) {
        // Check for the separator or the end of the string
        if (position == length() || str[position] == separator) {
            // Reached the end of a segment. Extract the segment.
            String part = substr(start, position - 1);
            substrings.push_back(part);  // Add the extracted segment to the substrings vector.
            start = position + 1;  // Update the start to the character after the separator.
        }
        ++position;  // Move to the next character.
    }

    return substrings;  // Return the vector of split substrings.
}
