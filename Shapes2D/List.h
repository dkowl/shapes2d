#pragma once

#include <initializer_list>

template<bool flag, class TTrue, class TFalse>
struct Choose {};

template<class TTrue, class TFalse>
struct Choose<true, TTrue, TFalse> {
	typedef TTrue Type;
};

template<class TTrue, class TFalse>
struct Choose<false, TTrue, TFalse> {
	typedef TFalse Type;
};

template<typename T>
class List {

	class Node;

	Node *head;
	Node *tail;

public:

	template<bool isConst = false>
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

	~List() {
		Clear();
	}

	List(List const &other) :
		List()
	{
		for (auto elem = other.begin(); elem != other.end(); elem++) {
			Add(*elem);
		}
	}

	List& operator=(const List& other) {
		Clear();
		for (auto elem = other.begin(); elem != other.end(); elem++) {
			Add(*elem);
		}
		return *this;
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

	void Clear() {
		Node* currentNode = head;
		while (currentNode != nullptr) {
			Node* nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
	}

	Iterator<true> begin() const {
		return Iterator<true>(this, head);
	}

	Iterator<true> end() const {
		return Iterator<true>(this, nullptr);
	}

	Iterator<false> begin() {
		return Iterator<false>(this, head);
	}

	Iterator<false> end() {
		return Iterator<false>(this, nullptr);
	}

	template<bool isConst>
	class Iterator {
		friend class List;

		typedef typename Choose<isConst, const List*, List*>::Type Listptr;
		typedef typename Choose<isConst, const Node*, Node*>::Type Nodeptr;

		Listptr list;
		Nodeptr currentNode;

		Iterator(Listptr list, Nodeptr node) :
			list(list),
			currentNode(node)
		{
		}

	public:
		Iterator(const Iterator<false> &other) :
			list(other.list),
			currentNode(other.currentNode)
		{
		}

		Iterator& operator=(const Iterator &other)
		{
			list = other.list;
			currentNode = other.currentNode;
			return *this;
		}

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

		const T& operator *() {
			return (*currentNode).value;
		}

		const T& operator *() const {
			return (*currentNode).value;
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

		~Node() {
		}
	};
};