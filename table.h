//********************************************
// Daniel Galvez
// Hash Table Project
// table.h
// *******************************************


class node
{
	public:
		node();
		~node();
		int set_word(char* word);
		char* get_word();
		node*& get_next();
		int set_next(node*& head);
		int print();
	private:
		char* word;
		node* next;
};


class table
{
	public:
		table(int size = 10);
		~table();
		int add(char* word);				// Adds a word to the hash table
		int remove(char* word);				// Removes a word from the hash table
		int hash_function(char* word);			// Generates an index number from the word argument
		int display_all();				// Display every entry in the table
		int retrieve(char* word);			// Displays a word if it is in the table
	private:
		int recur_a(int i);				// Sets indices to null when table object is created
		int recur_b(int i);				// Recurs over table and uses recur_c to remove all nodes
		int recur_c(node*& head);			// Recurs over the lll's and removes all nodes in the list
		int recur_d(node*& head, char* word);   	// Recurs over a lll at a given index and removes word 
		int recur_e(node*& head, char* word);		// Recurs over a lll and inserts the new word alphabetically
		int alpha_insert(node*& head, char* word); 	// Inserts a node into a lll in the table
		node*& get_last(node*& head);			// Returns the last node of a lll at any given index
		node** hash_table;				// Array of node* type
		int size;					// Size of the hash table
};


