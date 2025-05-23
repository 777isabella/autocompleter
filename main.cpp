
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "autocompleter.h"

using namespace std;

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	//abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


string random_string(int length)
{
	string s;
	for (int i = 0; i < length; ++i)
		s += 'a' + (rand() % 26);
	return s;
}

void pause()
{
	cout << "Press Enter to continue ";
	cin.ignore();
}

//void interactive_mode()
//{
//	Autocompleter dictionary;
//
//	// Fill autocompleter with words
//	ifstream f;
//	f.open("words.txt");
//	assert(f.is_open()); // If this fails, you're missing above file
//	string line;
//	while (getline(f, line))
//		dictionary.insert(line);
//	f.close();
//
//	char answer;
//	string results[5];
//	while (true)
//	{
//		cout << "\nPlease enter p to print, i to insert, c to check a word, x to exit: ";
//		cin >> answer;
//		if (answer == 'i')
//		{
//			cin.ignore(100, '\n');
//			cout << "\nEnter the word to be inserted: ";
//			getline(cin, line);
//			dictionary.insert(line);
//		}
//		else if(answer == 'c')
//		{
//			cin.ignore(100, '\n');
//			cout << "\nPlease enter the word to be checked: ";
//			getline(cin, line);
//			dictionary.completions(line, results);
//			for (int i = 0; i < 5; ++i)
//				if (results[i] != "")
//					cout << "    " << results[i] << endl;
//		}
//		else if (answer == 'p')
//		{
//			cout << "\nCurrent content of Autocompleter\n";
//			for (int i = 0; i < dictionary.size(); ++i)
//			{
//				if (i > 0 && i % 100 == 0)
//					pause();
//				cout << i + 1 << ") " << dictionary.get(i) << endl;
//			}
//		}
//		else
//			break;
//	}
//	exit(0);
//}

int main()
{
	srand(2017); // Initialize random number generation, e.g. rand()
	string results[5]; // Used to hold output suggestions in some tests


	// Uncomment the statement below to use your Autocompleter interactively.
	// You will need to uncomment its function definition above and 
	// the function definition for get() in autocompleter.h too
	// 
	// interactive_mode();


	// Test a small Autocompleter with animal names
	Autocompleter animals;
	test(animals.size() == 0);

	animals.insert("aardvark");
	animals.insert("albatross");
	animals.insert("alpaca");
	animals.insert("armadillo");
	animals.insert("camel");
	animals.insert("cat");
	animals.insert("crocodile");
	animals.insert("crow");
	animals.insert("giraffe");
	animals.insert("goat");
	animals.insert("goose");
	animals.insert("gorilla");
	test(animals.size() == 12);

	animals.insert("gorilla"); // Already in the Autocompleter
	test(animals.size() == 12);

	// Test completion_count() on animals Autocompleter.
	test(animals.completion_count("a") == 4);
	test(animals.completion_count("al") == 2);
	test(animals.completion_count("cro") == 2);
	test(animals.completion_count("gir") == 1);
	test(animals.completion_count("go") == 3);

	test(animals.completion_count("") == 12);

	test(animals.completion_count("an") == 0);
	test(animals.completion_count("q") == 0);
	test(animals.completion_count("goats") == 0);
	test(animals.completion_count("goat-billed carp") == 0);

	// Test completions() on animals Autocompleter.
	animals.completions("a", results);
	test(results[0] == "aardvark");
	test(results[1] == "albatross");
	test(results[2] == "alpaca");
	test(results[3] == "armadillo");
	test(results[4] == "");

	animals.completions("al", results);
	test(results[0] == "albatross");
	test(results[1] == "alpaca");
	test(results[2] == "");
	test(results[3] == "");
	test(results[4] == "");

	animals.completions("cro", results);
	test(results[0] == "crocodile");
	test(results[1] == "crow");
	test(results[2] == "");
	test(results[3] == "");
	test(results[4] == "");

	animals.completions("gir", results);
	test(results[0] == "giraffe");
	test(results[1] == "");
	test(results[2] == "");
	test(results[3] == "");
	test(results[4] == "");

	animals.completions("go", results);
	test(results[0] == "goat");
	test(results[1] == "goose");
	test(results[2] == "gorilla");
	test(results[3] == "");
	test(results[4] == "");

	animals.completions("", results);
	test(results[0] == "aardvark");
	test(results[1] == "albatross");
	test(results[2] == "alpaca");
	test(results[3] == "armadillo");
	test(results[4] == "camel");

	animals.completions("an", results);
	test(results[0] == "");
	test(results[1] == "");
	test(results[2] == "");
	test(results[3] == "");
	test(results[4] == "");

	animals.completions("q", results);
	test(results[0] == "");
	test(results[1] == "");
	test(results[2] == "");
	test(results[3] == "");
	test(results[4] == "");

	animals.completions("goat-billed carp", results);
	test(results[0] == "");
	test(results[1] == "");
	test(results[2] == "");
	test(results[3] == "");
	test(results[4] == "");

	// Create an autocompleter of 12800 common English words
	Autocompleter dictionary;

	// Fill autocompleter with words
	cout << "Filling Autocompleter with 12800 words" << endl;
	string* words = new string[12800];
	ifstream f;
	f.open("words.txt");
	assert(f.is_open()); // If this fails, you're missing words.txt
	string line;
	int i = 0;
	while (getline(f, line))
	{
		words[i] = line;
		++i;
	}
	f.close();
	assert(i == 12800); // If this fails, words.txt does not have exactly 12800 words

	for (int i = 0; i < 12800; ++i)
		dictionary.insert(words[i]);
	test(dictionary.size() == 12800);

	// Uncomment the statements below to see the content of Autocompleter
	// You will need to uncomment the function definition for get() in autocompleter.h too
/*
	cout << "\nCurrent content of Autocompleter\n";
	for (int i = 0; i < dictionary.size(); ++i)
	{
		if (i > 0 && i % 100 == 0)
			pause();
		cout << i + 1 << ") " << dictionary.get(i) << endl;
	}
*/

	// Test inserting at the end of the dictionary (after the current last word)
	dictionary.insert("zuz");

	// Test inserting at the beginning of the dictionary (before the current first word)
	dictionary.insert("A");

	test(dictionary.size() == 12802);

	// Uncomment the statements below to see the content of Autocompleter
	// You will need to uncomment the function definition for get() in autocompleter.h too
/*
	cout << "\nCurrent content of Autocompleter\n";
	for (int i = 0; i < dictionary.size(); ++i)
	{
		if (i > 0 && i % 100 == 0)
			pause();
		cout << i + 1 << ") " << dictionary.get(i) << endl;
	}
*/

	// Test completion_count() on dictionary Autocompleter.
	test(dictionary.completion_count("bir") == 7);
	test(dictionary.completion_count("hap") == 6);
	test(dictionary.completion_count("program") == 8);
	test(dictionary.completion_count("foo") == 10);
	test(dictionary.completion_count("way") == 3);
	test(dictionary.completion_count("zeros") == 0);

	// Test completions() on dictionary Autocompleter.
	dictionary.completions("bir", results);
	test(results[0] == "bird");
	test(results[1] == "birds");
	test(results[2] == "birmingham");
	test(results[3] == "birth");
	test(results[4] == "birthday");

	dictionary.completions("hap", results);
	test(results[0] == "happen");
	test(results[1] == "happened");
	test(results[2] == "happening");
	test(results[3] == "happens");
	test(results[4] == "happiness");

	dictionary.completions("program", results);
	test(results[0] == "program");
	test(results[1] == "programmable");
	test(results[2] == "programme");
	test(results[3] == "programmer");
	test(results[4] == "programmers");
	
	dictionary.completions("foo", results);
	test(results[0] == "foo");
	test(results[1] == "food");
	test(results[2] == "foods");
	test(results[3] == "fool");
	test(results[4] == "foot");

	dictionary.completions("way", results);
	test(results[0] == "way");
	test(results[1] == "wayne");
	test(results[2] == "ways");
	test(results[3] == "");
	test(results[4] == "");

	dictionary.completions("zeros", results);
	test(results[0] == "");
	test(results[1] == "");
	test(results[2] == "");
	test(results[3] == "");
	test(results[4] == "");

	// Uncomment the statements below to see the content of Autocompleter
	// You will need to uncomment the function definition for get() in autocompleter.h too

// 	cout << "\nCurrent content of Autocompleter\n";
// 	for (int i = 0; i < dictionary.size(); ++i)
// 	{
// 		if (i > 0 && i % 100 == 0)
// 			pause();
// 		cout << i + 1 << ") " << dictionary.get(i) << endl;
// 	}

	// Test Autocompleter for completing 100000 words
	cout << "Testing Autocompleter for completing 100000 words" << endl;
	for (int i = 0; i < 100000; ++i)
		dictionary.completion_count(random_string(5));

	for (int i = 0; i < 100000; ++i)
		dictionary.completions(random_string(5), results);


	cout << "Assignment complete." << endl;
	return 0;
}



