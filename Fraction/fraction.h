#ifndef __FRACTION_H__
#define __FRACTION_H__

#include <iostream>

class Fraction
{
private:
	int num_;
	int den_;
	
	Fraction &normalize(void);
	
public:
	Fraction(int = 0, int = 1);
	
	Fraction &init(int = 0, int = 1);
	int getIntegerPart(void);
	Fraction getFractionPart(void);
	string toString(void);
	
	int getNumerator(void);
	int getDenominator(void);
	void setNumerator(int);
	void setDenominator(int);

	friend ostream &operator<<(ostream &, const Fraction &);

	// Operations with fraction int/1
	bool operator>(int);
	bool operator<(int);
	bool operator==(int);
	bool operator!=(int);
	bool operator>=(int);
	bool operator<=(int);

	Fraction operator+(int);
	Fraction operator-(int);
	Fraction operator*(int);
	Fraction operator/(int);
	
	Fraction &operator=(int);
	Fraction &operator+=(int);
	Fraction &operator-=(int);
	Fraction &operator*=(int);
	Fraction &operator/=(int);

	// Operatinos with Fraction
	bool operator>(Fraction &);
	bool operator<(Fraction &);
	bool operator==(Fraction &);
	bool operator!=(Fraction &);
	bool operator>=(Fraction &);
	bool operator<=(Fraction &);
	
	Fraction operator+(Fraction &);
	Fraction operator-(Fraction &);
	Fraction operator*(Fraction &);
	Fraction operator/(Fraction &);
	
	Fraction &operator=(Fraction &);
	Fraction &operator+=(Fraction &);
	Fraction &operator-=(Fraction &);
	Fraction &operator*=(Fraction &);
	Fraction &operator/=(Fraction &);
};

#endif
