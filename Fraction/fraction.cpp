#include "fraction.h"

using namespace std;

Fraction::Fraction(int num, int dem)
{
	this->num_ = num;
	this->den_ = dem;
}

Fraction &Fraction::init(int num, int den)
{
	this->num_ = num;
	this->den_ = den;
	
	return *this;
}

Fraction &Fraction::normalize(void)
{
	if (this->den_ == 0) {
		this->num_ = 0;
		this->den_ = 1;
		return *this;
	}
	
	int a = abs(this->num_);
	int b = abs(this->den_);

	// Euclidean algorithm
	while (a != 0 && b != 0) {
		if (a > b)
			a = a % b;
		else
			b = b % a;
	}

	// divide by GCD
	this->num_ /= (a+b);
	this->den_ /= (a+b);

	// only numerator has minus
	if (this->den_ < 0) {
		this->num_ *= -1;
		this->den_ *= -1;
	}
	
	return *this;
}


void Fraction::Print(void)
{
	this->normalize();
	
	if (this->den_ == 1)
		cout << this->num_ << '\n'; // If denominator equal 1 then print only numerator
	else
		cout << this->num_ << '/' << this->den_ << '\n';
}

int Fraction::getIntegerPart(void)
{
	return this->num_ / this->den_;
}

Fraction Fraction::getFractionPart(void)
{
	return Fraction(this->num_%this->den_, this->den_).normalize();
}

string Fraction::toString()
{
	this->normalize();
	
	if (this->den_ == 1)
		return to_string(this->num_);

	return to_string(this->num_) + "/" + to_string(this->den_);
}

int Fraction::getNumerator(void)
{
	this->normalize();
	return this->num_;
}

int Fraction::getDenominator(void)
{
	this->normalize();
	return this->den_;
	
}

void Fraction::setNumerator(int num)
{
	this->num_ = num;
}

void Fraction::setDenominator(int dem)
{
	this->den_ = dem;
}

bool Fraction::operator>(int num)
{
	return this->num_ > num*this->den_;
}

bool Fraction::operator<(int num)
{
	return this->num_ < num*this->den_;
}

bool Fraction::operator==(int num)
{
	return this->num_ == num*this->den_;
}

bool Fraction::operator!=(int num)
{
	return this->num_ != num*this->den_;
}

bool Fraction::operator>=(int num)
{
	return this->num_ >= num*this->den_;
}

bool Fraction::operator<=(int num)
{
	return this->num_ <= num*this->den_;
}

Fraction Fraction::operator+(int num)
{
	return Fraction(this->num_ + num*this->den_, this->den_);
}

Fraction Fraction::operator-(int num)
{
	return Fraction(this->num_ - num*this->den_, this->den_);
}

Fraction Fraction::operator*(int num)
{
	return Fraction(this->num_*num, this->den_);
}

Fraction Fraction::operator/(int num)
{
	return Fraction(this->num_, num*this->den_);
}

Fraction &Fraction::operator=(int num)
{
	this->num_ = num;
	this->den_ = 1;
	
	return *this;
}

Fraction &Fraction::operator+=(int num)
{
	this->num_ += num*this->den_;
	
	return *this;
}

Fraction &Fraction::operator-=(int num)
{
	this->num_ -= num*this->den_;
	
	return *this;
}

Fraction &Fraction::operator*=(int num)
{
	this->num_ *= num;
	
	return *this;
}

Fraction &Fraction::operator/=(int num)
{
	this->den_ *= num;
	
	return *this;
}

bool Fraction::operator>(Fraction &fraction)
{
	return this->num_*fraction.den_ > this->den_*fraction.num_;
}

bool Fraction::operator<(Fraction &fraction)
{
	return this->num_*fraction.den_ < this->den_*fraction.num_;
}

bool Fraction::operator==(Fraction &fraction)
{
	return this->num_*fraction.den_ == this->den_*fraction.num_;
}

bool Fraction::operator!=(Fraction &fraction)
{
	return this->num_*fraction.den_ != this->den_*fraction.num_;
}

bool Fraction::operator>=(Fraction &fraction)
{
	return this->num_*fraction.den_ >= this->den_*fraction.num_;
}

bool Fraction::operator<=(Fraction &fraction)
{
	return this->num_*fraction.den_ <= this->den_*fraction.num_;
}


Fraction Fraction::operator+(Fraction &fraction)
{
	int num = this->num_*fraction.den_ + this->den_*fraction.num_;
	int dem = this->den_ * fraction.den_;
	
	return Fraction(num, dem);
}

Fraction Fraction::operator-(Fraction &fraction)
{
	int num = this->num_*fraction.den_ - this->den_*fraction.num_;
	int dem = this->den_*fraction.den_;
	
	return Fraction(num, dem);
}

Fraction Fraction::operator*(Fraction &fraction)
{
	return Fraction(this->num_*fraction.num_, this->den_*fraction.den_);
}

Fraction Fraction::operator/(Fraction &fraction)
{
	return Fraction(this->num_*fraction.den_, this->den_*fraction.num_);
}

Fraction &Fraction::operator=(Fraction &fraction)
{
	this->num_ = fraction.num_;
	this->den_ = fraction.den_;
	
	return *this;
}

Fraction &Fraction::operator+=(Fraction &fraction)
{
	this->num_ = this->num_*fraction.den_ + this->den_*fraction.num_;
	this->den_ *= fraction.den_;
	
	return *this;
}

Fraction &Fraction::operator-=(Fraction &fraction)
{
	this->num_ = this->num_*fraction.den_ - this->den_*fraction.num_;
	this->den_ *= fraction.den_;
	
	return *this;
}

Fraction &Fraction::operator*=(Fraction &fraction)
{
	this->num_ *= fraction.num_;
	this->den_ *= fraction.den_;
	
	return *this;
}

Fraction &Fraction::operator/=(Fraction &fraction)
{
	this->num_ *= fraction.den_;
	this->den_ *= fraction.num_;
	
	return *this;
}

int main(int argc, char **argv)
{
	Fraction a(8, -3);
	Fraction b(11, 2);
	
	Fraction c = a+b;
	c.Print();
	
	return 0;
}
