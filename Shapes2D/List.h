#pragma once

#include <initializer_list>

template<typename T>
class List {

	class Node;

	Node *head;
	Node *tail;

public:

	class Iterator;

	List() :
		head(nullptr),
		tail(nullptr)
	{
	}

	List(std::initializer_list<T> initList) :
		List()
	{
		for (T elem : initList) {
			Add(elem);
		}
	}

	List(List& other) :
		List()
	{
		for (auto elem : other) {
			Add(elem);
		}
	}

	~List() {
		Node* currentNode = head;
		while (currentNode != nullptr) {
			Node* nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
	}

	void Add(const T &value) {
		Node *newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	Iterator begin() {
		return Iterator(this, head);
	}

	Iterator end() {
		return Iterator(this, nullptr);
	}

	class Iterator {
		friend class List;

		List *list;
		Node *currentNode;

		Iterator(List *list, Node *node) :
			list(list),
			currentNode(node)
		{
		}

	public:
		bool operator==(const Iterator &b) {
			return currentNode == b.currentNode;
		}

		bool operator!=(const Iterator &b) {
			return currentNode != b.currentNode;
		}

		Iterator& operator++() {
			if (currentNode != nullptr) {
				currentNode = currentNode->next;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp(*this);
			operator++();
			return temp;
		}

		Iterator& operator--() {
			if (currentNode != list->head) {
				if (currentNode == nullptr) {
					currentNode = list->tail;
				}
				else {
					currentNode = currentNode->prev;
				}
			}
			return *this;
		}

		Iterator operator--(int) {
			Iterator temp(*this);
			operator--();
			return temp;
		}

		T& operator *() {
			return currentNode->value;
		}
	};

private:

	class Node {
	public:
		T value;
		Node *prev;
		Node *next;

		Node(T value) :
			value(value),
			prev(nullptr),
			next(nullptr)
		{
		}
	};
};