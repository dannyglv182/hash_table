#include "table.h"
using namespace std;

int main()
{
	table myHashTable;
	char x[25]= "actxyz";
	char y[25]= "tacxyz";
	char z[25] = "xyzcat";
	char a[25] = "BobDylan";
	char b[25] = "TupacShakur";
	

	myHashTable.add(x);
	myHashTable.add(y);
	myHashTable.add(z);
	myHashTable.add(a);
	myHashTable.add(b);
	myHashTable.retrieve(b);
	myHashTable.remove(x);
	myHashTable.remove(y);
	myHashTable.display_all();
	return 0;
}
