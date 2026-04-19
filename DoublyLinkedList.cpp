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
	ListNode* SearchNode(ListNode* head, int node_index) //+++++
	{
		ListNode* last_node = nullptr;
		while (head != nullptr)
		{
			last_node = head;
			head = head->next;
		}
		ListNode* current_node = last_node;
		int counter = 0;
		if (node_index == -1)
		{
			return nullptr;
		}
		for (int i = 0; i < (file_data.size() / 2); i++)
		{
			if (counter == node_index)
			{
				return current_node;
			}
			else
			{
				counter++;
			}
			current_node = current_node->prev;
		}
	}

	void FillList(ListNode** head) //+++++
	{
		for (int i = 0, j = 0; i < file_data.size() / 2; i++, j += 2)
		{
			AppendData(head, file_data[j]);
		}
	}

	void AddRandNode(ListNode* head) //+++++
	{
		int counter = 1;
		while (head != nullptr)
		{
			int index = std::stoi(file_data[counter]);
			head->rand = SearchNode(head, index);
			head = head->next;
			counter += 2;
		}
	}

	void AppendData(ListNode** head, std::string data) //+++++
	{
		ListNode* Node = new ListNode;
		Node->data = data;
		Node->next = (*head);
		Node->prev = nullptr;
		if ((*head) != nullptr)
		{
			(*head)->prev = Node;
		}
		(*head) = Node;
	}

	void ShowList(ListNode* head) //+++++
	{
		ListNode* last_node = nullptr;
		while (head != nullptr)
		{
			last_node = head;
			head = head->next;
		}
		while (last_node != nullptr)
		{
			std::cout << last_node->data << std::endl;
			last_node = last_node->prev;
		}
	}

	void ExtractFileData() //+++++
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

class SerializeAndDeserializeList  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
{
	public:
	void SerializeList(ListNode* head, std::string file_name) //+++++
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

	ListNode DeserializeList(std::string file_name) //+++++
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
	ListNode* head = nullptr;
	list_work->ExtractFileData();
	list_work->FillList(&head);
	list_work->AddRandNode(head);
	cout << "The doubly linked list" << endl;
	list_work->ShowList(head);
	SerializeAndDeserializeList* serialize_and_deserialize_list = new SerializeAndDeserializeList();
	serialize_and_deserialize_list->SerializeList(head, "outlet.out");
	ListNode deserialized_list = serialize_and_deserialize_list->DeserializeList("outlet.out");
	ListNode* pdeserialized_list;
	pdeserialized_list = &deserialized_list;
	cout << endl;
	cout << "The doubly linked list (deserialized)" << endl;
	list_work->ShowList(pdeserialized_list);
	return 0;
}