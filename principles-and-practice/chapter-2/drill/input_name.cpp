#include <iostream>
#include <string>

int main()
{
	std::cout << "Please enter your first name (followed by 'enter'):\n";
	std::string name; // name is a variable of type string
	std::cin >> name; // read characters into name
	std::cout << "Hello," << name << "!\n";
	return 0;
}
