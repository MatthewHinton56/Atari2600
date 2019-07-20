#include <iostream>
using namespace std;
int main()
{
	unsigned int i = 1;
	char* c = (char*)& i;
	if (*c)
		cout << "Little endian";
	else
		cout << "Big endian";
	cout << sizeof(uint8_t);

	return 0;
}