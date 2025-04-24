//***********************************************************************
 // Team # 3                    
// CSCI 2380                                
// Fall 2024                     
// Homework # 10 
// Kasandra Ornelas
// Isabella Morgan
//  
//*********************************************************************** 

#include "autocompleter.h"
#include <string>
using namespace std;

// Creates a new, empty autocompleter. Initial capacity is 100 elements.
//constructor
Autocompleter::Autocompleter()
{

	capacity = 10;
	count = 0;
	//allocates dynamic arrau
	A = new string[capacity];
}

// Adds x to the list of potential suggestions in the Autocompleter in the position that will keep
// Autocompleter sorted after the insertion.
// MUST double the capacity when necessary.
// If the word is already in the Autocompleter, does nothing.
//
// MUST run in O(n) time.
void Autocompleter::insert(string word)
{
	//binary search to find insert position
	int low = 0, high = count;
	while (low < high)
	{
		int mid = (low + high) / 2;
		if (A[mid] < word)
			low = mid + 1;
		else
			high = mid;
	}

	//if word already exists @ insert index,, return
	if (low < count && A[low] == word)
		return;

	//resize if count reaches capacity 
	if (count == capacity)
	{
		capacity *= 2;
		string* newA = new string[capacity];
		for (int i = 0; i < count; ++i)
			newA[i] = A[i];
		delete[] A;
		A = newA;
	}

	//shift elements to make space for the new word
	for (int i = count; i > low; --i)
		A[i] = A[i - 1];
		
	//insert new word & increment count
	A[low] = word;
	++count;
}

// Returns the number of strings in the Autocompleter.
int Autocompleter::size()
{
	return count;
}

// Returns the number of strings that are completions of
// the parameter string x. 
//
// MUST run in O(log(n)) time.
int Autocompleter::completion_count(string prefix)
{
	int len = prefix.length();
	int matchCount = 0;

	//binary search to find the first word >= prefix
	int low = 0, high = count;
	while (low < high)
	{
		int mid = (low + high) / 2;
		if (A[mid].compare(0, len, prefix) < 0)
			low = mid + 1;
		else
			high = mid;
	}

	//count how many words begin w the prefix
	for (int i = low; i < count; ++i)
	{
		if (A[i].compare(0, len, prefix) == 0)
			++matchCount;
		else
		    //stop when matches end
			break;
	}
	return matchCount;
}

// Takes a string (parameter x) and string array of length 5 (parameter suggestions) 
// Sets the first five elements of suggestions equal 
// to the first five (in lexicographic order) strings
// in the Autocompleter that start with x. 
//
// If there are less than five such strings, the remaining
// entries of the suggestions array are set to "" (the empty string) 
//
// MUST run in O(log(n)) time.
void Autocompleter::completions(string prefix, string* suggestions)
{
	int len = prefix.length();

	//clear suggestions
	for (int i = 0; i < 5; ++i)
		suggestions[i] = "";

	//use binary searh to find first match
	int low = 0, high = count;
	while (low < high)
	{
		int mid = (low + high) / 2;
		if (A[mid].compare(0, len, prefix) < 0)
			low = mid + 1;
		else
			high = mid;
	}

	//collect up to 5 lexicographically sorted matches
	int found = 0;
	for (int i = low; i < count && found < 5; ++i)
	{
		if (A[i].compare(0, len, prefix) == 0)
		{
			suggestions[found++] = A[i];
		}
		// stop once matches end 
		else
			break; 
	}
}
