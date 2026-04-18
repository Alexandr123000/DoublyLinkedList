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
		using namespace std;
		ListNode node;
		ListNode* head;
		head = &node;
		ListNode* current_node = head;
		for (int i = 0; i < (file_data.size() / 2); i++)
		{
			ListNode node;
			ListNode* new_node;
			new_node = &node;
			current_node->next = new_node;
			new_node->prev = current_node;
			current_node = new_node;
		}
		head->data = ListWork::file_data[0];
		if (std::stoi(file_data[1]) == -1)
		{
			head->rand = nullptr;
		}
		else
		{
			int rand_node_number = std::stoi(ListWork::file_data[1]);
			head->rand = SearchNode(head, std::stoi(ListWork::file_data[1]));
		}
		ListNode* temp_node;
		temp_node = head->next;
		
		ListNode* temp_node2;
		temp_node2 = head->next;

		for (int i = 0, j = 3; i < (file_data.size() / 2); i++, j += 2)
		{
			temp_node->data = file_data[j - 1];
			if (temp_node->next != nullptr)
			{
				temp_node = temp_node->next;
				cout << temp_node->data;
				//cout << temp_node->prev->data;
			}
			else
			{
				break;
			}
		}
		/*ListNode* temp_node3;
		temp_node3 = head;
		while (temp_node != nullptr)
		{
			cout << temp_node->data;
			temp_node3 = temp_node->next;
		}*/
		//cout << head->prev->data << endl;
		/*for (int i = 0; i < (file_data.size() / 2); i++)
		{
			cout << "dfdf:  " << head->rand->data << endl;
			//head = head->next;
		}*/
		//========================================================================================================
		//========================================================================================================
		//========================================================================================================
		//========================================================================================================
		//========================================================================================================
		//========================================================================================================
		/*for (int i = 2, j = 3; i < (file_data.size() / 2) + 1; i++, j += 2)
		{
			if (std::stoi(file_data[j]) == -1)
			{
				temp_node2->rand = nullptr;
			}
			else
			{
				int rand_node_number = std::stoi(ListWork::file_data[j]);
				temp_node2->rand = SearchNode(head, std::stoi(ListWork::file_data[j]));
				std::cout << "qqqqqqqqq: " << temp_node2->data << std::endl;
			}
		}*/
		/*
		for (int i = 0; i < file_data.size() / 2; i++)
		{
			if (temp_node3->rand != nullptr)
			{
				std::cout << "dddnnn: " << head->rand->data << std::endl;
				temp_node3 = temp_node3->next;
			}
			else
			{
				temp_node3 = temp_node3->next;
				continue;
			}

		}*/
		this->head = head;
		//std::cout << "dddrrr: " << this->head->rand->data << std::endl;
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
	/*void ShowList(ListNode* nnn)
	{
		for (int i = 0; i < file_data.size() / 2; i++)
		{
			std::cout << "lll:   " << nnn->data << std::endl;
			//nnn = nnn.next;
		}

	}*/
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
		deserialized_list.data = "";
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



int main()
{
	ListWork* list_work = new ListWork();
	
	ListNode* head;
	list_work->ExtractFileData();
	list_work->MakeAndFillList();
	head = list_work->head;
	//std::cout << "dddfff: " << head->data << std::endl;
	SerializeAndDeserializeList* serialize_and_deserialize_list = new SerializeAndDeserializeList();
	serialize_and_deserialize_list->SerializeList(head, "data.bin");
	ListNode deserialized_list = serialize_and_deserialize_list->DeserializeList("data.bin");
	//std::cout << "ddd: " << deserialized_list.data.size() << std::endl;
	ListNode* deserialized_list1;
	deserialized_list1 = &deserialized_list;
	//list_work->ShowList(deserialized_list1);
	/*if (deserialized_list1 != nullptr)
	{
		std::cout <<  << std::endl;
	}
	else
	{
		std::cout << deserialized_list1->data << std::endl;
	}*/


	return 0;
}