/*
 * sorter.h
 *
 * Declares a template function:
 *    
 *   sorter() : k-way merge sort.
 * 
 * 
 * You may add other functions if you wish, but this template function
 * is the only one that need to be exposed for the testing code.
 * 
 * Authors: C. Painter-Wakefield & Tolga Can
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <string>
#include <cstddef>
#include <vector>
#include <cmath>

using namespace std;
template <class T>
T findMax(vector< vector <T> >& splitVectors) {
	unsigned long maxIndex = 0;										//Set the max element as the first element in the first vector
	for(unsigned long i = 0; i < splitVectors.size(); i++) {
		if(splitVectors[i].size() != 0) {
			maxIndex = i;
			break;
		}
	}
	T max = splitVectors[maxIndex].back();												
	for(unsigned long i = 0; i < splitVectors.size(); i++) {					//For each of the vectors in split vectors, we need to check the front
		if(splitVectors[i].size() != 0 && splitVectors[i].back() > max) {		//If the size is not zero, compare the last element to the max
			max = splitVectors[i].back();										//If the element was greater, then update the max
			maxIndex = i;														//Track where the maximum is
		}
	}
	splitVectors[maxIndex].pop_back();											//Pop the back of the vector, since this element will be placed in the final
	return max;									//Return the maximum in the list
}

template <class T>
void merge2(vector< vector<T> >& vectorContainer, unsigned long originalSize, vector<T>& vec) {
	if(originalSize == 0 || originalSize == 1) {				//If the original size was 0 or 1, then there should be no merge
		vec = vectorContainer[0];
		return;
	} else {
		vector<T> finalVec(originalSize);						//Make a vector that is the same size as vec originally was 
		unsigned long current = originalSize - 1;				//Create a variable to control where elements are placed
		for(unsigned long i = 0; i < originalSize; i++) {		//For each element in the vector,
			finalVec[current] = findMax(vectorContainer);		//The next element from the end is the max in the vector container
			current--;											//Next iteration, update the element before
		}
		vec = finalVec;											//Set vec as the final merged vec
		return;
	}
}

template <class T>
void sorter(vector<T> &vec, int k) {  
	// write your solution for k-way merge sort below	
	if(vec.size() == 0 || vec.size() == 1) {
		return;
	} else {
		unsigned long originalSize = vec.size();					//Save the original size of the vector
		unsigned int numLarge = vec.size() % k;						//Number of large arrays is the remainder when dividing by k
		unsigned int numSmall = k - numLarge;						//The rest of the arrays will be small (see above)
		unsigned int sizeOfSmallArrays = floor(vec.size()/k);		//The size of the small arrays is the floor of dividing by k
		unsigned int sizeOfLargeArrays = sizeOfSmallArrays + 1;		//All large arrays will have an extra element
		vector< vector<T> > arrayContainer;							//Final container to hold split arrays
		for(unsigned int i = 0; i < numSmall; i++) {				//Create numSmall arrays that are of the smaller size
			vector<T> splitter;										//Create a vector to hold the elements that we split
			for(unsigned int j = 0; j < sizeOfSmallArrays; j++) {	
				splitter.push_back(vec.back());						//Push the element to the splitter vector
				vec.pop_back();										//Then delete from the original in order to acess the next element
			}
			arrayContainer.push_back(splitter);						//Push the splitter to the vector container
		}
		for(unsigned int i = 0; i < numLarge; i++) {				//Like above, create num large arrays of the larger size
			vector<T> splitter;
			for(unsigned int j = 0; j < sizeOfLargeArrays; j++) {
				splitter.push_back(vec.back());
				vec.pop_back();
			}
			arrayContainer.push_back(splitter);
		}
		for(int i = 0; i < k; i++) {
			sorter(arrayContainer[i], k);							//Call sorter on each of the split arrays, also passing in k
		}
		merge2(arrayContainer, originalSize, vec);	//Merge function, merges array container and places it in vec
		return;
	}
	return;
}


#endif
