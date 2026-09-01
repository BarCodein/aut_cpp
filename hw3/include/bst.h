#ifndef BST_H
#define BST_H

#include<iostream>
#include<functional>


class BST
{
	
public:
	BST();
	BST(std::initializer_list<int> list);
	BST(const BST& other);
	BST(BST&& other);
	~BST();

	BST& operator=(const BST& other);
	BST& operator=(BST&& other);
	class Node
	{
	public:
		Node(int value, Node* left, Node* right);
		Node();
		Node(const Node& node);
		int value;
		Node* left;
		Node* right;

		friend bool operator==(const Node& a, const int& b);
		friend bool operator>=(const Node& a, const int& b);
		friend bool operator<=(const Node& a, const int& b);
		friend bool operator>(const Node& a, const int& b);
		friend bool operator<(const Node& a, const int& b);

		friend bool operator==(const int& a, const Node& b);
		friend bool operator>=(const int& a, const Node& b);
		friend bool operator<=(const int& a, const Node& b);
		friend bool operator>(const int& a, const Node& b);
		friend bool operator<(const int& a, const Node& b);
	};

	

	Node*& get_root();
	void bfs(std::function<void(Node*& node)> fuc);
	size_t length();
	bool add_node(int value);
	Node** find_node(int value);
	Node** find_parrent(int value);
	Node** find_successor(int value);
	bool delete_node(int value);
	BST& operator++();
	BST operator++(int);

private:
	Node* root;
};

std::ostream& operator<<(std::ostream& os,BST::Node& node);

std::ostream& operator<<(std::ostream& os,BST& bst);
#endif //BST_H