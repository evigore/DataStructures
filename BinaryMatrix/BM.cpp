#include "BM.h"

using namespace std;

BM::BM(int rows, int columns, bool value)
{
	if (rows < 0)
		rows = 0;

	rows_ = rows;
	columns_ = columns;
	matrix_ = new BV[rows_];

	for (int i = 0; i < rows_; i++)
		matrix_[i] = BV(columns_, value);
}

BM::BM(uint8_t **matrix, int rows, int columns)
{
	if (rows < 0)
		rows = 0;

	rows_ = rows;
	columns_ = columns;
	matrix_ = new BV[rows];

	for (int i = 0; i < rows; i++)
		matrix_[i] = BV(matrix[i], columns);
}

BM::BM(const BM &bm)
{
	matrix_ = nullptr;
	*this = bm;
}

BM::~BM(void)
{
	delete[] matrix_;
}

BM &BM::operator=(const BM &bm)
{
	if (this == &bm)
		return *this;

	if (matrix_)
		delete[] matrix_;

	rows_ = bm.rows_;
	columns_ = bm.columns_;
	matrix_ = new BV[rows_];

	for (int i = 0; i < rows_; i++)
		matrix_[i] = BV(bm.matrix_[i]);

	return *this;
}

BM BM::operator~(void)
{
	BM bm(*this);

	for (int i = 0; i < rows_; i++)
		bm.matrix_[i] = ~bm.matrix_[i];

	return bm;
}

BV &BM::operator[](int row)
{
	if (row < 0)
		row = 0;
	else if (row > rows_-1)
		row = rows_-1;

	return matrix_[row];
}

BM BM::operator&(const BM &bm)
{
	BM mat(*this);
	mat &= bm;

	return mat;
}

BM BM::operator|(const BM &bm)
{
	BM mat(*this);
	mat |= bm;

	return mat;
}

BM BM::operator^(const BM &bm)
{
	BM mat(*this);
	mat ^= bm;

	return mat;
}

BM &BM::operator&=(const BM &bm)
{
	int rows = min(rows_, bm.rows_);

	for (int i = 0; i < rows; i++)
		matrix_[i] &= bm.matrix_[i];

	for (int i = rows_; i < rows; i++)
		matrix_[i] = BV(columns_, 0);

	return *this;
}

BM &BM::operator|=(const BM &bm)
{
	for (int i = 0; i < min(rows_, bm.rows_); i++)
		matrix_[i] |= bm.matrix_[i];

	return *this;
}

BM &BM::operator^=(const BM &bm)
{
	int rows = min(rows_, bm.rows_);

	for (int i = 0; i < rows; i++)
		matrix_[i] ^= bm.matrix_[i];

	return *this;
}

ostream &operator<<(ostream &out, const BM &bm)
{
	for (int i = 0; i < bm.rows_; i++)
		cout << bm.matrix_[i] << endl;

	return out;
}

istream &operator>>(istream &in, BM &bm)
{
	int rows;
	cout << "rows = ";
	in >> rows;

	int columns;
	cout << "columns = ";
	in >> columns;

	if (rows < 0)
		rows = 0;
	if (columns < 0)
		columns = 0;

	bm = BM(rows, columns, 0);

	cout << "Matrix:\n";
	for (int i = 0; i < rows; i++)
		in >> bm.matrix_[i];

	return in;
}

void BM::set(int i, int j, bool value, int count)
{
	if (count < 1)
		return;

	if (j < 0)
		j = 0;
	else if (j > rows_-1)
		j = rows_-1;

	matrix_[j].set(columns_-i-count, value, count);
}

void BM::inverse(int i, int j, int count)
{
	if (count < 1)
		return;

	if (j < 0)
		j = 0;
	else if (j > rows_-1)
		j = rows_-1;

	//matrix_[j].inverse(i, count);
	matrix_[j].inverse(columns_-i-count, count);
}

BV BM::rowsOR(void)
{
	BV bv(columns_, 0);

	for (int i = 0; i < rows_; i++)
		bv |= matrix_[i];

	return bv;
}

BV BM::rowsAND(void)
{
	if (rows_ <= 0)
		return BV(columns_, 0);

	BV bv(matrix_[0]);

	for (int i = 1; i < rows_; i++)
		bv &= matrix_[i];

	return bv;
}

int BM::weight(void)
{
	int weight = 0;

	for (int i = 0; i < rows_; i++)
		weight += matrix_[i].weight();

	return weight;
}

int BM::weight(int row)
{
	if (row < 0)
		row = 0;
	else if (row > rows_-1)
		row = rows_-1;

	return matrix_[row].weight();
}
