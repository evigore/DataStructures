#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>

class List;
class Node;

class Node {
public:
	int value;
	Node *prev;
	Node *next;

	Node(int value_ = 0, Node *prev_=nullptr, Node *next_=nullptr)
	{
		value = value_;
		prev = prev_;
		next = next_;
	}
};

class List {
private:
	Node *head_; // contains a dummy head
	int count_;

	Node *at(int);
	int partition(int *, int start, int end);
	void quickSort(int *, int start, int end);
public:
	List(int count = 0);
	List(const int *, int);
	List(const List &);
	~List(void);

	List operator+(int);
	List operator-(int);
	List &operator+=(int);
	List &operator-=(int);

	List operator+(const List &);
	List &operator+=(const List &);
	bool operator==(const List &);

	int &operator[](int);
	List &operator=(const List &);

	friend List operator+(int, const List &);
	friend std::ostream &operator<<(std::ostream &, const List &);
	friend std::istream &operator>>(std::istream &, List &);

	void insert(int value) {*this += value;}
	void insert(int value, int index);
	void insertAfterKey(int value, int key);

	void removeFirst(void) {this->remove(0);}
	void remove(void) {this->remove(count_-1);}
	void remove(int index);

	void sort(void);
	void clear(void);
	bool empty(void);
	Node *find(int key);
	int max(void);
	int min(void);
};

#endif
