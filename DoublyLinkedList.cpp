#include <iostream>
#include <string>
#include <fstream>
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
	ListNode* head;
	ListNode* SearchNode(ListNode* head, int node_index)
	{
		ListNode* current_node = head;
		int counter = 0;
		for (int i = 0; i < file_data.size() / 2; i++)
		{
			current_node = current_node->next;
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

	ListNode* MakeAndFillList()
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
		for (int i = 0, j = 1; i < file_data.size() / 2; i++, j += 2)
		{
			if (std::stoi(file_data[j]) == -1)
			{
				temp_node->rand = nullptr;
			}
			else
			{
				int rand_node_number = std::stoi(ListWork::file_data[j]);
				temp_node->rand = SearchNode(head, std::stoi(ListWork::file_data[j]));
			}
			temp_node->rand = SearchNode(head, std::stoi(ListWork::file_data[j]));

			temp_node->data = file_data[j - 1];
			temp_node->prev = temp_node;
			temp_node = temp_node->next;
		}
		this->head = head;
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
class SerializeAndDeserializeList
{
	public:
	void SerializeList(ListNode* head, std::string file_name)
	{
		ofstream file(file_name, ios::binary);
		if (!file.is_open())
		{
			std::cout << "The file is not open." << std::endl;
			return;
		}
		file.write(reinterpret_cast<const char*>(head), sizeof(*head));
		file.close();
		std::cout << "The list is serialized." << std::endl;
	}

	ListNode DeserializeList(std::string file_name)
	{
		ListNode deserialized_list;
		ifstream file(file_name, ios::binary);
		if (!file.is_open())
		{
			std::cout << "The file is not open." << std::endl;
			return deserialized_list;
		}
		file.read(reinterpret_cast<char*>(&deserialized_list), sizeof(deserialized_list));
		file.close();
		std::cout << "The list is deserialized." << std::endl;
		return deserialized_list;
	}
};

/*void ShowList(ListNode* nnn)
{
	for (int i = 0; i < file_data.size() / 2; i++)
	{
		std::cout << "lll:   " << nnn->data << std::endl;
		nnn = nnn->next;
	}

}*/

int main()
{
	ListWork* list_work = new ListWork();
	
	ListNode* head;
	list_work->ExtractFileData();
	list_work->MakeAndFillList();
	head = list_work->head;
	SerializeAndDeserializeList* serialize_and_deserialize_list = new SerializeAndDeserializeList();
	serialize_and_deserialize_list->SerializeList(head, "outlet.out");
	serialize_and_deserialize_list->DeserializeList("outlet.out");

	return 0;
}