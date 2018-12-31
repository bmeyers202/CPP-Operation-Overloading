/**
 * A C++ program that demonstrates the operation overloading capabilities of the language.
 * The heart of this program is the IntArray class.
 * With it, the user can declare integer arrays of any size with automatic range checking of
 * indices.
 * The upper and lower indices can be any integer, positive or negative, rather than the fixed
 * limits of 0 to SIZE-1.
 * It is also possible to assign entire arrays to each other, compare two arrays for equality and
 * inequality, add two arrays, and output arrays using the overloaded << operator.
 *
 * @author	Blake Meyers
 * @version 1.0
 * @since 	1.0
 */

#include "intArray.h"
#include <stdio.h>

using namespace std;

/**
* IntArray default constructor.
* Initializes an int array to an array of size 10.
*/
IntArray::IntArray(){
    lo = 0;
    hi = 9;
    size = 10;
    pA = new int [size];
}

/**
* IntArray constructor initializing a int array given an array size.
*
* @param	userSize an array length defined by the user
*/
IntArray::IntArray(int userSize){
    lo = 0;
    hi = userSize-1;
    size = userSize;
    pA = new int [size];

}

/**
* IntArray constructor initializing a int array given upper and lower bounds for the array.
*
* @param 	lowerIndex the highest index of the array as defined by the user
* @param 	upperIndex the lowest index of the array as defined by user
*/
IntArray::IntArray(int lowerIndex, int upperIndex){
    if(lowerIndex > upperIndex){
        lo = lowerIndex;
        hi = upperIndex;
        pA = new int[0];
    }
    else if(lowerIndex == upperIndex)
    {
        lo = lowerIndex;
        hi = upperIndex;
        size = 1;
        pA = new int[size];
    }
    else{
        lo = lowerIndex;
        hi = upperIndex;
        size = (upperIndex - lowerIndex) + 1;
        pA = new int[size];
    }
}

/**
* IntArray constructor initializing a int array by copying another IntArray's values.
*
* @param	IntArray& copiedArray the address of another previously initialized IntArray object
*/
IntArray::IntArray(const IntArray& copiedArray){ // IntArray copy constructor
    lo = copiedArray.lo;
    hi = copiedArray.hi;
    size = copiedArray.size;
    pA = new int[size];
    for(int i = 0; i < size;i++){
        pA[i] = copiedArray.pA[i];
    }
}

/**
* IntArray deconstructor performing garbage collection on IntArray objects stored in the heap.
*/
IntArray::~IntArray(){
    delete [] pA;
}

/**
* Overloads the == operator to compare elements of two IntArray's and return true if they have the
* same number of elements and the same values.
*
* @param 	IntArray &array	the address of another previously initilized IntArray object to compare
* @return 	0 if size of compared arrays are different or the values are different
* @return 	1 if all the values in the compared arrays are the same
*/
int IntArray::operator ==(const IntArray& array) {
    if(size != array.size){
        return 0;
    }
    for(int i = 0; i < size; i++){
        if(pA[i] != array.pA[i]){
                return 0;
        }
    }
    return 1;
}

/**
* Overloads the != operator to compare elements of two IntArray's and return true if they have a
* different number of elements or different values.
*
* @param	IntArray &array	the address of another previously initilized IntArray object to compare
* @return 	1 if size of compared arrays are different or the values are different
* @return 	0 if all the values in the compared arrays are the same
*/
int IntArray::operator !=(const IntArray& array) {
	if(size != array.size){
		return 1;
	}
	for(int i = 0; i < size; i++){
		if(pA[i] == array.pA[i]){
            return 0;
		}
	}
	return 1;
}

/**
* Overloads the [] operator to offset the IntArray's index by the user defined indexes and access
* the array from base zero, as it is stored in memory.
*
* @param 	index the array index the user wishes to access the array element for
* @return	pA[0] the element at the int array base address
* @return	pA[index-lo] the element at the array location offsetted by the user specified lower index
*/
int& IntArray::operator[] (int index){
	if(index > hi || index < lo) {
		return pA[0];
	}
	else{
		return pA[index-lo];
	}
}

/**
* Overloads the = operator to copy the values of one IntArray object into another if they are of
* the same size.
*
* @param	IntArray &array	the address of the IntArray on the right side of the operator
* @return 	*this a pointer to the IntArray on the left side of the operator
*/
IntArray& IntArray::operator =(const IntArray& array) {
	if(array.size != size){
		return *this;
	}
	for(int i = 0; i < size; i++)
		pA[i] = array.pA[i];
	return *this;
}

/**
* Overloads the + operator to add the values of one IntArray object to another and return the new
* IntArray object.
*
* @param	IntArray &array the address of the IntArray on the right side of the operator
* @return 	temp a new IntArray object with the resulting values of adding the two arrays
*/
IntArray IntArray::operator +(const IntArray& array) {
	IntArray temp(array);
	temp.lo = 0;
	temp.hi = temp.size - 1;
	for(int i = 0; i < size; i++){
		temp.pA[i] += pA[i];
	}
	return temp;
}

/**
* Overloads the += operator to add the values of another IntArray object itself and return the
* original IntArray with it's updated values.
*
* @param	IntArray &array the address of the IntArray on the right side of the operator
* @return	*this a pointer to the IntArray on the left side of the operator
*/
IntArray& IntArray::operator +=(const IntArray& array) {
	if(array.size != size){
		return *this;
	}
	else{
		for(int i = 0; i < size; i++){
			pA[i] = array.pA[i] + pA[i];
		}
		return *this;
	}
}

/**
* Accesses the array how it is stored inside memory while outputting it as the index the
* user expects.
*
* @param	ostream& os	a reference to an output stream
* @param	IntArray& array the address of the IntArray on the right side of the operator
* @return	os an output stream
*/
ostream& operator<<(ostream& os, const IntArray& array){
	if(array.lo > array.hi){
		return os;
	}
	else if (array.lo == array.hi) {
		int i = array.lo;
		os << array.name << "[" << i << "] = " << array.pA[0] << endl;
	}
	else {
		for (int i = 0; i <array.size; i++) {
			os << array.name << "[" << i+array.lo << "] = " << array.pA[i] << endl;
		}
	}
	return os;
}

/**
* Assigns an IntArray object a character for a name.
*
* @param	*string	a pointer to a constant character to be used as a IntArray name
*/
void IntArray::setName(const char *string) {
	name = string;
}

/**
* Outputs the name of an IntArray object.
*/
void IntArray::getName() {
	if(name != NULL){
		cout << name << endl;
	}
}

/**
* Returns the highest index of an IntArray object.
*
* @return	hi the upper index set for the IntArray object
*/
int IntArray::high(){
	return hi;
}

/**
* Returns the lowest index of an IntArray object.
*
* @return	lo the lower index set for the IntArray object
*/
int IntArray::low(){
	return lo;
}
