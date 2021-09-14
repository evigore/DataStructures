#include "charSet.h"

using namespace std;

Set::Set(const char *str): BV(SET_SIZE, 0)
{
	int size = 0;
	if (str)
		size = strlen(str);

	for (int i = 0; i < size; i++)
		(*this)[(int)str[i]] = 1;
}

Set::Set(const Set &set): BV(set)
{}

bool Set::operator==(const Set &set)
{
	Set s(set);

	if (this->power() != s.power())
		return false;

	for (int i = 0; i < this->size(); i++)
		if ((*this)[i] != s[i])
			return false;

	return true;
}

bool Set::operator!=(const Set &set)
{
	return !(*this == set);
}

Set Set::operator~(void) const
{
	Set set(*this);
	BV &bv = set;
	bv = ~bv;

	return set;
}

Set Set::operator+(char sym)
{
	Set set(*this);
	set += sym;

	return set;
}

Set Set::operator-(char sym)
{
	Set set(*this);
	set -= sym;

	return set;
}

Set Set::operator+(const char *str)
{
	Set set(*this);
	set += str;

	return set;
}
Set Set::operator-(const char *str)
{
	Set set(*this);
	set -= str;

	return set;
}

Set Set::operator&(const Set &set)
{
	Set s(*this);
	s &= set;

	return s;
}

Set Set::operator|(const Set &set)
{
	Set s(*this);
	s |= set;

	return s;
}

Set Set::operator/(const Set &set)
{
	Set s(*this);
	s /= set;

	return s;
}

Set &Set::operator=(const Set &set)
{
	BV::operator=(set);
	return *this;
}

Set &Set::operator+=(char sym)
{
	this->set((int) sym);

	return *this;
}

Set &Set::operator-=(char sym)
{
	this->set((int) sym, 0);

	return *this;
}

Set &Set::operator+=(const char *str)
{
	for (int i = 0; str[i]; i++)
		*this += str[i];

	return *this;
}

Set &Set::operator-=(const char *str)
{
	for (int i = 0; str[i]; i++)
		*this -= str[i];

	return *this;
}

Set &Set::operator&=(const Set &set)
{
	BV::operator&=(set);

	return *this;
}

Set &Set::operator|=(const Set &set)
{
	BV::operator|=(set);

	return *this;
}

Set &Set::operator/=(const Set &set)
{
	*this &= ~set;

	return *this;
}

bool Set::isExist(char sym)
{
	return (*this)[(int) sym];
}

char Set::min(void)
{
	int i = 0;
	while (i < this->size() && (*this)[i] == 0)
		i++;

	return (char) i;
}

char Set::max(void)
{
	int i = this->size() - 1;
	while (i >= 0 && (*this)[i] == 0)
		i--;

	return (char) i;
}

int Set::power(void)
{
	int size = 0;

	for (int i = 0; i < this->size(); i++)
		size += (int) (*this)[i];

	return size;
}

ostream &operator<<(ostream &out, const Set &set)
{
	for (int i = 0; i < SET_SIZE; i++)
		if (((Set &)set)[i])
			cout << (char) i;

	return out;
}

istream &operator>>(istream &in, Set &set)
{
	string str;
	cin >> str;

	set = Set(str.c_str());

	return in;
}
