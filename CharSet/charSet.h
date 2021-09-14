#ifndef __CHAR_SET_H__
#define __CHAR_SET_H__

#include <iostream>
#include "BV.h"

#define SET_SIZE 128

using namespace std;

class Set: protected BV
{
public:
	Set(const char *str = nullptr);
	Set(const Set &);

	bool operator==(const Set &);
	bool operator!=(const Set &);

	Set operator~(void) const;

	Set operator+(char);
	Set operator-(char);
	Set operator+(const char *);
	Set operator-(const char *);
	Set operator&(const Set &);
	Set operator|(const Set &);
	Set operator/(const Set &);

	Set &operator=(const Set &);
	Set &operator+=(char);
	Set &operator-=(char);
	Set &operator+=(const char *);
	Set &operator-=(const char *);
	Set &operator&=(const Set &);
	Set &operator|=(const Set &);
	Set &operator/=(const Set &);

	friend ostream &operator<<(ostream &, const Set &);
	friend istream &operator>>(istream &, Set &);

	bool isExist(char);
	char min(void);
	char max(void);
	int power(void);
};

#endif
