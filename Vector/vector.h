#include <iostream>

class Vector
{
private:
	int *nums_;
	int size_; // used size
	int maxsize_; // allocated size

	bool isSorted_;
	bool isAscending_;

	// checks if the data is sorted
	void checkNumber(unsigned int index);

	void resize(unsigned int size);

	int linearSearch(int key);
	int binarySearch(int key);
	int reverseBinarySearch(int key);

	int partition(unsigned int begin, unsigned int end);
	void quickSort(unsigned int begin, unsigned int end);

public:
	Vector(int size = 0);
	Vector(int *, int size);
	Vector(const Vector &);
	~Vector(void);

	friend Vector operator+(int value, Vector &); // Add a value at the beginning
	Vector operator+(int value); // Add value at the end
	Vector operator-(int value);
	Vector &operator+=(int value);
	Vector &operator-=(int value);

	Vector operator+(Vector &);
	Vector operator-(Vector &);
	Vector &operator+=(Vector &);
	Vector &operator-=(Vector &);

	Vector &operator=(const Vector &);
	int &operator[](int);
	bool operator==(Vector &);
	bool operator!=(Vector &);

	friend ostream &operator<<(ostream &, const Vector &);
	friend istream &operator>>(istream &, Vector &); // input only one number

	void sort(void);
	void reverse(void);

	void insert(int value, int index); // Adds an element at the position
	void insertAfterKey(int value, int key);

	void removeAt(int index);
	void removeLast(void);

	int min(void);
	int max(void);

	int search(int value);

	void clear(); // fill zero
	void random(void) {this->random(size_);};
	void randomAscending(void) {this->randomAscending(size_);};
	void randomDescending(void) {this->randomDescending(size_);};

	void random(int count);
	void randomAscending(int count);
	void randomDescending(int count);

	void shiftLeft(int offset = 1, int unshift = 0); // the first unshift elements will remain unchanged, the rest will shift
	void shiftRight(int offset = 1, int unshift = 0); // the first unshift elements will remain unchanged, the rest will shift
};

