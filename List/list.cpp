#include "list.h"

using namespace std;

List::List(int count)
{
	if (count < 0)
		count = 0;

	count_ = 0;
	head_ = new Node();
	head_->prev = head_;
	head_->next = head_;

	for (int i = 0; i < count; i++)
		*this += 0;
}

List::List(const int *array, int count)
{
	if (count < 0)
		count_ = 0;

	count_ = 0;
	head_ = new Node();
	head_->prev = head_;
	head_->next = head_;

	for (int i = 0; i < count; i++)
		*this += array[i];
}

List::List(const List &list)
{
	count_ = 0;
	head_ = new Node();
	head_->prev = head_;
	head_->next = head_;

	*this = list;
}

List::~List(void)
{
	this->clear();
	delete head_;
}

int &List::operator[](int index)
{
	Node *node = this->at(index);
	if (node)
		return node->value;

	return head_->value;
}

List &List::operator=(const List &list)
{
	if (this == &list)
		return *this;

	this->clear();

	Node *node = list.head_->next;
	for (int i = 0; i < list.count_; i++, node=node->next)
		*this += node->value;

	return *this;
}

List List::operator+(int value)
{
	List list(*this);
	list += value;

	return list;
}

List List::operator-(int key)
{
	List list(*this);
	list -= key;

	return list;
}

List &List::operator+=(int value)
{
	Node *node = new Node(value, head_->prev, head_);
	head_->prev->next = node;
	head_->prev = node;

	count_++;

	return *this;
}

List &List::operator-=(int key)
{
	Node *node = this->find(key);
	if (!node)
		return *this;

	node->prev->next = node->next;
	node->next->prev = node->prev;
	
	delete node;
	count_--;

	return *this;
}

List List::operator+(const List &list)
{
	List newList(*this);
	newList += list;

	return newList;
}

List &List::operator+=(const List &list)
{
	Node *node = list.head_->next;
	for (int i = 0; i < list.count_; i++, node=node->next)
		*this += node->value;

	return *this;
}

bool List::operator==(const List &list)
{
	if (count_ != list.count_)
		return false;

	Node *a = head_->next;
	Node *b = list.head_->next;
	for (int i = 0; i < count_; i++, a=a->next, b=b->next)
		if (a->value != b->value)
			return false;

	return true;
}

List operator+(int value, const List &list)
{
	List newList(list);

	Node *node = new Node(value, newList.head_, newList.head_->next);
	newList.head_->next->prev = node;
	newList.head_->next = node;
	newList.count_++;

	return newList;
}

ostream &operator<<(ostream &out, const List &list)
{
	out << "count=" << list.count_ << ": ";

	Node *node = list.head_->next;
	for (int i = 0; i < list.count_-1; i++, node=node->next)
		out << node->value << " -> ";

	if (list.count_ != 0)
		out << node->value;

	return out;
}

istream &operator>>(istream &in, List &list)
{
	int value;
	in >> value;

	list += value;

	return in;
}

Node *List::at(int index)
{
	if (count_ == 0)
		return nullptr;

	index %= count_;
	if (index < 0)
		index += count_;

	Node *node = head_->next;
	while (index--)
		node = node->next;

	return node;
}

void List::insert(int value, int index)
{
	count_++; // so that when you call at () you can insert an element at the end
	Node *prev = this->at(index);
	if (!prev) {
		count_--;
		return;
	}

	prev = prev->prev;
	Node *node = new Node(value, prev, prev->next);
	prev->next->prev = node;
	prev->next = node;

}

void List::insertAfterKey(int value, int key)
{
	Node *prev = this->find(key);
	if (!prev)
		return;

	Node *node = new Node(value, prev, prev->next);
	prev->next->prev = node;
	prev->next = node;

	count_++;
}

void List::remove(int index)
{
	Node *node = this->at(index);
	if (!node)
		return;

	node->prev->next = node->next;
	node->next->prev = node->prev;
	
	delete node;
	count_--;
}

int List::partition(int *arr, int start, int end)
{
	int mid = start;
	for (int i = start; i < end; i++) {
		if (arr[i] <= arr[end]) {
			swap(arr[mid], arr[i]);
			mid++;
		}
	}

	swap(arr[mid], arr[end]);
	return mid;
}

void List::quickSort(int *arr, int start, int end)
{
	if (start < end) {
		int mid = partition(arr, start, end);
		
		quickSort(arr, start, mid-1);
		quickSort(arr, mid+1, end);
	}
}

void List::sort(void)
{
	int count = count_;
	int *array = new int[count];

	Node *node = head_->next;
	for (int i = 0; i < count; i++, node=node->next)
		array[i] = node->value;

	this->quickSort(array, 0, count-1);
	this->clear();

	for (int i = 0; i < count; i++)
		*this += array[i];
}

void List::clear(void)
{
	Node *node = head_->next;
	for (int i = 0; i < count_; i++) {
		Node *next = node->next;
		delete node;

		node = next;
	}

	count_ = 0;
	head_->prev = head_;
	head_->next = head_;
}

bool List::empty(void)
{
	return count_ == 0;
}

Node *List::find(int key)
{
	Node *node = head_->next;
	for (int i = 0; i < count_; i++, node=node->next)
		if (node->value == key)
			return node;

	return nullptr;
}

int List::max(void)
{
	Node *node = head_->next;
	int max = node->value;

	for (int i = 0; i < count_; i++, node=node->next)
		if (node->value > max)
			max = node->value;

	return max;
}

int List::min(void)
{
	Node *node = head_->next;
	int min = node->value;

	for (int i = 0; i < count_; i++, node=node->next)
		if (node->value < min)
			min = node->value;

	return min;
}

