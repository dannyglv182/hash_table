//********************************************
// Daniel Galvez
// Hash Table Project
// table.cpp
// *******************************************
#include "table.h"
#include <iostream>
#include <string.h>
using namespace std;



//********************************************
// Constructor
// input: none
// output: none
// *******************************************
node::node()
{
	word = nullptr;
	next = nullptr;
}


//********************************************
// Destructor
// input: none
// output: none
// This function deallocates the memory used
// for node objects
// *******************************************
node::~node()
{
	delete[] this->word;
}


//********************************************
// set_word
// input: char* word
// output: none
// This function allocates the memory for a 
// word and copies the argument into the new
// char array
// *******************************************
int node::set_word(char* word)
{
	this->word = new char[strlen(word) + 1];
	strcpy(this->word, word);
	return 0;
}


//********************************************
// get_word
// input: none
// output: none
// This function returns a word.
// *******************************************
char* node::get_word()
{
	return this->word;
}


//********************************************
// get_next
// input: none
// output none
// This function returns the next node in a 
// lll
// *******************************************
node*& node::get_next()
{
	return this->next;
}


int node::set_next(node*& head)
{
	this->next = head;
	return 0;
}


//********************************************
// print
// input: none
// output: char* 
// this function outputs a word
// *******************************************
int node::print()
{
	cout << this->word;
}


//********************************************
// recur_a
// input: int i
// This function sets each node pointer to
// null when the table object is created.
// *******************************************
int table::recur_a(int i)
{
	// Base case
	if (i >= this->size)
	{
		return 0;
	}

	// Set the index to null
	hash_table[i] = nullptr;

	// recur
	recur_a(i+1);
}


//********************************************
// Constructor
// input: int size
// *******************************************
table::table(int size)
{
	this->size = size;
	hash_table = new node*[size];
	recur_a(0);
}


//********************************************
// recur_b
// input: int i
// This function traverses the hash table 
// recursively and calls the function that
// deletes every node for the given index.
// *******************************************
int table::recur_b(int i)
{
	// Base case
	if (i >= this->size)
	{
		return 0;
	}

	// deallocate evey node in hash_tabe[i]
	if (hash_table[i])
	{
		recur_c(hash_table[i]);
	}

	// recur
	recur_b(i+1);
}


//**********************************************
// recur_c
// input: node*& head
// This function takes the head of any list in
// the hash table as its argument. It traverses
// the list recursively and deletes every node.
// *********************************************
int table::recur_c(node* &head)
{
	if (!head)
	{
		return 0;
	}

	// Recur
	recur_c(head->get_next());

	// Delete on stack unwind
	delete head;
}


//**********************************************
// get_last
// input: node*& head
// This function takes the head of any list in 
// the hash table as its argument. It returns
// the last node in that list
// *********************************************
node*& table::get_last(node*& head)
{
	if (!head->get_next())
	{
		return head;
	}
	get_last(head->get_next());
}


table::~table()
{
	recur_b(0);
	delete[] hash_table;
}


//********************************************
// hash_function
// input: char* word
// This function takes a C string argument and
// maps it into an interger value within the 
// bounds of the hash_table array. It adds the 
// ASCII values of the string and mods it by 
// the size of the table.
// *******************************************
int table::hash_function(char* word)
{
	int total = 0;
	for (int i = 0; i < strlen(word); ++i)
	{
		total += word[i];
	}
	return total % this->size;
}


//********************************************
// add
// input: char* word
// This function inserts the new node at the
// index generated by the hash_function. 
// Chaining is used so that each index is a 
// pointer to the first node in linked list.
// *******************************************
int table::add(char* word)
{
	int i = hash_function(word);

	if (hash_table[i] == nullptr)						// Case: index is null.
	{
		this->hash_table[i] = new node;
		this->hash_table[i]->set_word(word);
	}
	else									// Case: i is not null. Collision. Add new node alphabetically
	{
		alpha_insert(hash_table[i], word);
	}
	return 0;
} 


//********************************************
// recur_d
// input: node*&, char*
// output: none
// This function traverses a lll recursively
// and deletes a node if its word matches the
// char* argument. 
// *******************************************
int table::recur_d(node*&head, char* word)
{
	if (!head)
	{
		return 0;
	}
	recur_d(head->get_next(), word);

	if (strcmp(head->get_word(), word) == 0)
	{
		node* temp;
		temp = head;
		head = head->get_next();
		delete temp;
	}
}


//***********************************************
// recur_e
// input: node*&, char* 
// output: none
// This function inserts a new word into the list
// in alphabetical order. Cases for an empty list
// or a one node list are handled outside of here
// in the alpha_insert function.
// **********************************************
int table::recur_e(node*& head, char* word)
{
	if (!head)
	{
		return 0;
	}
	if (!head->get_next())	// Last node in the list
	{
		node* new_word;
		new_word = new node;
		new_word->set_word(word);
		head->set_next(new_word);
		return 0;
	}
	node* ahead;
	ahead = head->get_next();
	if (strcmp(word, ahead->get_word()) > 0)	// is word > next->word?
	{
		recur_e(head->get_next(), word);
	}
	else						// We are at the insertion point
	{
		node* new_word;
		new_word = new node;
		new_word->set_word(word);
		new_word->set_next(ahead);
		head->set_next(new_word);
		return 0;
	}
}


//***********************************************
// remove
// input: char*
// output: none
// This function removes a word from the table.
// It uses the hash function to get the index
// where the word is located and then calls the
// private function, recur_d, to remove the node. 
// **********************************************
int table::remove(char* word)
{
	int i = hash_function(word);
	return recur_d(hash_table[i], word);
}


//***********************************************
// alpha_insert
// input: node*&, char*
// output: none
// This function adds a chain in the table passed
// in as the head argument. Cases with more than 
// one node are handled in the recursive function
// called from here.
// **********************************************
int table::alpha_insert(node*& head, char* word)
{
	// Case: no list
	if (!head)
	{
		return 0;
	}

	// Case: One node
	if (!head->get_next())
	{
		if (strcmp(head->get_word(), word) > 0)	// head's word is > word argument
							// The new word becomes the head of the list
		{
			node* old_head = head;
			head = new node;
			head->set_word(word);
			head->set_next(old_head);
			return 0;
		}
		else					// head's word is < word argument
							// The new word is added to the end
		{
			node* temp;
			temp = new node;
			temp->set_word(word);
			head->set_next(temp);
			return 0;
		}
	}

	// Case: recur	
	return recur_e(head, word);
}


//***********************************************
// display_all
// input: none
// output: char* 
// Displays every entry in the table
// **********************************************
int table::display_all()
{
	for (int i = 0; i < size; ++i)
	{
		if (hash_table[i])
		{
			node* curr;
			curr = hash_table[i];
			while (curr)
			{
				curr->print();
				cout << "\n";
				curr = curr->get_next();
			}
		}
	}
	return 0;
}


//***********************************************
// retrieve
// input: char*
// output: char*
// This function prints a word if it is in the 
// table.
// **********************************************
int table::retrieve(char* word)
{
	int index = hash_function(word);
	node* curr = hash_table[index];
	while (curr)
	{
		if (strcmp(curr->get_word(), word) == 0)
		{
			curr->print();
			cout << " is in the table.\n";
			curr = curr->get_next();
		}
	}
	return 0;
}
