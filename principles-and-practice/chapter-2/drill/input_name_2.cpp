#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter the name of the person you wan to write to\n";
	std::string name;
	std::cin >> name;
	std::cout << "Dear " << name << "!\n";
	std::cout << "How are you ? I am fine. I miss you.\n";
	return 0;
}
