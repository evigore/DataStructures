#ifndef __BM_H__
#define __BM_H__

#include <iostream>
#include <cstdint>
#include "BV.h"

class BM
{
private:
	BV *matrix_;
	int rows_;
	int columns_;

public:
	BM(int rows = 0, int columns = 0, bool value = 0);
	BM(uint8_t **, int rows, int columns);
	BM(const BM &);
	~BM(void);

	int getRows(void) {return rows_;}
	int getColumns(void) {return columns_;}

	BM &operator=(const BM &);
	BV &operator[](int row);

	BM operator~(void);
	BM operator&(const BM &);
	BM operator|(const BM &);
	BM operator^(const BM &);

	BM &operator&=(const BM &);
	BM &operator|=(const BM &);
	BM &operator^=(const BM &);

	friend std::ostream &operator<<(std::ostream &, const BM &);
	friend std::istream &operator>>(std::istream &, BM &);

	void set(int i, int j, bool value = 1, int count = 1);
	void inverse(int i, int j, int count = 1);

	BV rowsOR(void);
	BV rowsAND(void);

	int weight(void);
	int weight(int row);
};

#endif
