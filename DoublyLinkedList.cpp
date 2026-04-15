#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

struct ListNode {
	ListNode* prev = nullptr;
	ListNode* next = nullptr;
	ListNode* rand = nullptr;
	std::string data;
};

class ListWork
{
	void FillList(ListNode& list)
	{
		std::map <std::string, std::string> file_data;
		std::string line_data;
		std::string first_value_of_the_line;
		std::string second_value_of_the_line;
		bool symbol_mark = false;
		std::ifstream in("inlet.in");
		if (in.is_open())
		{
			while (std::getline(in, line_data))
			{
				for (int i = 0; i < line_data.length(); i++)
				{
					if (symbol_mark == true)
					{
						//std::cout << "first: " << first_value_of_the_line << std::endl;
						file_data[second_value_of_the_line] = first_value_of_the_line;
						first_value_of_the_line = "";
						second_value_of_the_line = "";
						symbol_mark = false;
						break;
					}
					if (line_data[i] == ';')
					{
						for (int j = i + 1; j < line_data.length(); j++)
						{
							second_value_of_the_line += line_data[j];

						}
						//std::cout << "second: " << second_value_of_the_line << std::endl;
						//second_value_of_the_line = "";
						symbol_mark = true;
					}
					else
					{
						first_value_of_the_line += line_data[i];
					}
				}
			}
		}
		std::cout << "NNN: " << file_data["-1"] << std::endl;
	}
};

int main()
{
	ListNode* HEAD;
	ListWork lll;
	return 0;
}