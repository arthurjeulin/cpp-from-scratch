#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter the name of the person you wan to write to\n";
	std::string name;
	std::cin >> name;
	std::cout << "Dear " << name << "!\n";
	std::cout << "How are you ? I am fine. I miss you.\n";
	std::cout << "Bye Bro!\n";
	std::string another_friend;
	std::cin >> another_friend;
	std::cout << "Have you seen " << another_friend << " lately ?\n";
	return 0;
}
