#include <iostream>
#include <string>
#include <fstream>
//#include <map>
#include <vector>

using namespace std;

struct ListNode {
	ListNode* prev = nullptr;
	ListNode* next = nullptr;
	ListNode* rand = nullptr;
	std::string data;
};

class ListWork
{
	public:
	std::vector <std::string> file_data;
	

	ListNode* SearchNode(ListNode* head, int node_index)
	{
		ListNode* current_node = head;
		int counter = 0;
		for (int i = 0; i < file_data.size() / 2; i++)
		{
			current_node = current_node->next;
			//std::cout << "mmm: " << counter << std::endl;
			if (counter == node_index)
			{
				return current_node;
			}
			else
			{
				counter++;
			}
		}
	}

	void MakeAndFillList()
	{
		ListNode node;
		ListNode* head;
		head = &node;
		ListNode* current_node = head;
		for (int i = 0; i < file_data.size() / 2; i++)
		{
			ListNode node;
			ListNode* new_node;
			new_node = &node;
			current_node->next = new_node;
			new_node->prev = current_node;
			current_node = new_node;
		}
		node.data = ListWork::file_data[0];
		if (std::stoi(file_data[1]) == -1)
		{
			node.rand = nullptr;
		}
		else
		{
			int rand_node_number = std::stoi(ListWork::file_data[1]);
			node.rand = SearchNode(head, std::stoi(ListWork::file_data[1]));
		}
		ListNode* temp_node;
		temp_node = head;
		for (int i = 0; i < file_data.size() / 2; i++)
		{
			if (std::stoi(file_data[i+1]) == -1)
			{
				temp_node->rand = nullptr;
			}
			else
			{
				int rand_node_number = std::stoi(ListWork::file_data[i+1]);
				temp_node->rand = SearchNode(head, std::stoi(ListWork::file_data[i+1]));
			}
			temp_node->rand = SearchNode(head, std::stoi(ListWork::file_data[i+1]));
			temp_node->data = file_data[i];
			temp_node->prev = temp_node;
			temp_node = temp_node->next;
		}
	}

	void ExtractFileData()
	{

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
						file_data.push_back(first_value_of_the_line);
						file_data.push_back(second_value_of_the_line);
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
						symbol_mark = true;
					}
					else
					{
						first_value_of_the_line += line_data[i];
					}
				}
			}
		}
	}
};

int main()
{
	ListWork* list_work = new ListWork();
	list_work->ExtractFileData();
	list_work->MakeAndFillList();

	return 0;
}