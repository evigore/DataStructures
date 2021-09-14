#include <iostream>
#include <vector>

using namespace std;

class Leader;

class Trailer
{
public:
	Leader *out;
	Trailer *next;

	Trailer(Leader *out_=nullptr, Trailer *next_=nullptr)
	{
		out = out_;
		next = next_;
	}
};

class Leader
{
public:
	int key;
	int inCount;
	Leader *next;
	Trailer *outs;

	Leader(int key_, Leader *next_=nullptr)
	{
		key = key_;
		next = next_;
		inCount = 0;
		outs = nullptr;
	}

	Leader(Leader &leader)
	{
		key = leader.key;
		inCount = leader.inCount;

		outs = leader.outs;
		next = leader.next;
	}

	~Leader(void)
	{
		this->deleteOuts();
	}

	void deleteOuts(void)
	{
		Trailer *node = outs;
		while (node) {
			Trailer *next = node->next;
			delete node;

			node = next;
		}

	}

	void addOut(Leader *leader)
	{
		outs = new Trailer(leader, outs);
	}
};

class Graph
{
private:
	int size_;
	Leader *leader_;

public:
	Graph(void)
	{
		size_ = 0;
		leader_ = nullptr;
	}

	~Graph(void)
	{
		Leader *node = leader_;
		while (node) {
			Leader *next = node->next;
			delete node;

			node = next;
		}
	}

	int getSize(void)
	{
		return size_;
	}

	void addEdge(int a, int b)
	{
		Leader *pa = nullptr;
		Leader *pb = nullptr;
		Leader *i = leader_;

		while (i) {
			if (i->key == a)
				pa = i;

			if (i->key == b)
				pb = i;

			i = i->next;
		}

		if (pa == nullptr) {
			size_++;
			pa = leader_ = new Leader(a, leader_);
		}

		if (pb == nullptr) {
			size_++;
			pb = leader_ = new Leader(b, leader_);
		}

		pb->inCount++;
		pa->addOut(pb);
	}

	bool hasCircle(void)
	{
		Leader *newLeader = nullptr;

		Leader *node = leader_;
		while (node) {
			if (node->inCount == 0) {
				Leader *head = new Leader(*node);
				head->next = newLeader;
				newLeader = head;
			}

			node = node->next;
		}

		int count = 0;
		Leader *p = newLeader;
		while (p) {
			newLeader = p->next;
			count++;

			Trailer *T = p->outs;
			while (T) {
				if (--T->out->inCount == 0) {
					Leader *head = new Leader(*T->out);
					head->next = newLeader;
					newLeader = head;
				}

				T = T->next;
			}

			p->outs = nullptr;
			delete p;

			p = newLeader;
		}

		return size_ != count;
	}

	vector<int> topologicalSort(void)
	{
		vector<int> vertices;
		Leader *newLeader = nullptr;

		Leader *node = leader_;
		while (node) {
			if (node->inCount == 0) {
				Leader *head = new Leader(*node);
				head->next = newLeader;
				newLeader = head;
			}

			node = node->next;
		}

		Leader *p = newLeader;
		while (p) {
			newLeader = p->next;
			vertices.push_back(p->key);

			Trailer *T = p->outs;
			while (T) {
				if (--T->out->inCount == 0) {
					Leader *head = new Leader(*T->out);
					head->next = newLeader;
					newLeader = head;
				}

				T = T->next;
			}

			p->outs = nullptr;
			delete p;

			p = newLeader;
		}

		return vertices;
	}

	friend ostream &operator<<(ostream &, const Graph &);
	friend istream &operator>>(istream &, Graph &);
};

ostream &operator<<(ostream &out, const Graph &graph)
{
	vector<vector<int> *> vertices;

	int i = 0;
	Leader *node = graph.leader_;
	while (node) {
		vector<int> *vertex = new vector<int>();

		vertex->push_back(node->key);
		vertex->push_back(node->inCount);

		Trailer *tr = node->outs;
		while (tr) {
			vertex->push_back(tr->out->key);

			tr = tr->next;
		}

		vertices.push_back(vertex);
		i++;
		node = node->next;
	}

	int maxSize = 0;
	for (int i = 0; i < vertices.size(); i++)
		if (vertices[i]->size() > maxSize)
			maxSize = vertices[i]->size();

	for (int j = 0; j < maxSize; j++) {
		if (j == 0)
			cout << "Keys:    ";
		else if (j == 1)
			cout << "inCount: ";
		else
			cout << "         ";

		for (int i = 0; i < vertices.size(); i++) {
			if (j < vertices[i]->size())
				out << vertices[i]->at(j) << ' ';
			else
				out << "  ";

		}

		out << endl;
	}

	return out;
}

istream &operator>>(istream &in, Graph &graph)
{
	cout << "Enter (a b): ";
	int a;
	in >> a >> skipws;

	int b;
	in >> b;

	graph.addEdge(a, b);

	return in;
}

int main(void)
{
	Graph graph;

	int size;
	cout << "size ";
	cin >> size;

	for (int i = 0; i < size; i++)
		cin >> graph;
	cout << endl;

	//cout << graph << endl;
	cout << (graph.hasCircle() ? "has loop" : "hasn't loop") << endl;


	return 0;
}
