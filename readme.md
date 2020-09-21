# Hash Table Project
## Project by Daniel Galvez
## C++ 

A hash table implementation that stores strings. The table index
where the string is to be stored is calculated by adding the ascii value of
each letter in the string and modding that value by the table size.

Chains of linked nodes are used to resolve collisions and dynamic memory is deallocated recursively.
