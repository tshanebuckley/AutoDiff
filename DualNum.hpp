/*
 * DualNum.hpp
 *
 *  Created on: Jul 6, 2019
 *      Author: tshan
 */

#ifndef DUALNUM_HPP_
#define DUALNUM_HPP_

#include <iostream>
#include <cmath>
using namespace std;

class DualNum {
public:
	double real; //real number variable
	double dual; //dual number variable (Espilon)
	//constructors
	DualNum() {
		real = 1.0;
		dual = 1.0;
	}
	DualNum(int r) {
		real = (double)r;
		dual = 1.0;
	}
	DualNum(double r) {
		real = r;
		dual = 1.0;
	}
	DualNum(int r, int d) {
		real = (double)r;
		dual = (double)d;
	}
	DualNum(double r, int d) {
		real = r;
		dual = (double)d;
	}
	DualNum(int r, double d) {
			real = r;
			dual = (double)d;
		}
	DualNum(double r, double d) {
			real = r;
			dual = d;
		}
	//assignment operator
	DualNum& operator=(DualNum& dn) {
		this->real = dn.real;
		this->dual = dn.dual;
		return *this;
	}
	/*
	 * dual num 1 = a + bE
	 * dual num 2 = c + dE
	 */
	//addition operators
	DualNum operator+(DualNum dn) {
		return DualNum(this->real+dn.real, this->dual+dn.dual);
		//real component: a+c
		//dual component: (b+d)E
	}
	DualNum operator+=(DualNum dn) {
		this->real += dn.real;
		this->dual += dn.dual;
		return *this;
	}
	//addition operators w/ variables
	DualNum operator+(int n) {
		return DualNum(this->real+(double)n, this->dual);
	}
	DualNum operator+(double n) {
		return DualNum(this->real+n, this->dual);
	}
	DualNum operator+=(int n) {
		this->real += (double)n;
		return *this;
	}
	DualNum operator+=(double n) {
		this->real += n;
		return *this;
	}
	//subtraction operators
	DualNum operator-(DualNum dn) {
		return DualNum(this->real-dn.real, this->dual-dn.dual);
		//real component: a-c
		//dual component: (b-d)E
	}
	DualNum operator-=(DualNum dn) {
		this->real -= dn.real;
		this->dual -= dn.dual;
		return *this;
	}
	//subtraction operators w/ variables
	DualNum operator-(int n) {
		return DualNum(this->real-(double)n, this->dual);
	}
	DualNum operator-(double n) {
		return DualNum(this->real-n, this->dual);
	}
	DualNum operator-=(int n) {
		this->real -= (double)n;
		return *this;
	}
	DualNum operator-=(double n) {
		this->real -= n;
		return *this;
	}
	//multiplication operators
	DualNum operator*(DualNum dn) {
		return DualNum(this->real*dn.real, this->real*dn.dual+this->dual*dn.real);
		//real component: a*c
		//dual component: (ad + bc)E
	}
	DualNum operator*=(DualNum dn) {
		this->dual = (this->real*dn.dual)+(this->dual*dn.real);
		this->real *= dn.real;
		return *this;
	}
	//multiplication operators w/ variables
	DualNum operator*(int n) {
		return DualNum(this->real*(double)n, this->dual*(double)n);
	}
	DualNum operator*(double n) {
		return DualNum(this->real*n, this->dual*n);
	}
	DualNum operator*=(int n) {
		this->real *= (double)n;
		this->dual *= (double)n;
		return *this;
	}
	DualNum operator*=(double n) {
		this->real *= n;
		this->dual *= n;
		return *this;
	}
	//division operators
	DualNum operator/(DualNum dn) {
		return DualNum(this->real/dn.real, (this->dual*dn.real-this->real*dn.dual)/(dn.real*dn.real));
		//real component: a/c
		//dual component: (bc - ad)E/(c^2)
	}
	DualNum operator/=(DualNum dn) {
		this->dual = this->real*dn.dual+this->dual*dn.real;
		this->real *= dn.real;
		return *this;
	}
	//division operators w/ variables
	DualNum operator/(int n) {
		return DualNum(this->real/(double)n, this->dual/(double)n);
	}
	DualNum operator/(double n) {
		return DualNum(this->real/n, this->dual/n);
	}
	DualNum operator/=(double n) {
		this->real /= n;
		this->dual /= n;
		return *this;
	}
	std::ostream& operator<<(DualNum&);
};

ostream& operator<<(ostream& os, DualNum dn) {
    os << dn.real << " + " << dn.dual << "E";
    return os;
}

//variable on LHS operators
DualNum operator+(int n, DualNum dn) {
    return dn + n;
}

DualNum operator+(double n, DualNum dn) {
    return dn + n;
}

DualNum operator*(int n, DualNum dn) {
    return dn * n;
}

DualNum operator*(double n, DualNum dn) {
    return dn * n;
}

DualNum operator-(int n, DualNum dn) {
    return DualNum(n-dn.real, dn.dual);
}

DualNum operator-(double n, DualNum dn) {
    return DualNum(n-dn.real, dn.dual);
}

DualNum operator/(int n, DualNum dn) {
    return DualNum(n/dn.real, n/dn.dual);
}

DualNum operator/(double n, DualNum dn) {
    return DualNum(n/dn.real, n/dn.dual);
}

namespace math{

	DualNum sin(DualNum dn) {
 		return DualNum(std::sin(dn.real),dn.dual*(std::cos(dn.real)));
 	}
 	double sin(double d) {
 		return std::sin(d);
 	}
 	double sin(int d) {
 	 	return std::sin(d);
 	}
 	DualNum cos(DualNum dn) {
 		return DualNum(std::cos(dn.real),-dn.dual*(std::sin(dn.real)));
  	}
 	double cos(double d) {
 	 	return std::cos(d);
 	}
 	double cos(int d) {
 	 	return std::sin(d);
 	}
 	DualNum pow(DualNum dn, int n) {
 		return DualNum(std::pow(dn.real,(double)n),(double)n*dn.dual*(std::pow(dn.real,(double)n-1)));
 	}
 	DualNum pow(DualNum dn, double n) {
 	 	return DualNum(std::pow(dn.real,n),n*dn.dual*(std::pow(dn.real,n-1)));
 	}
 	double pow(double d1, double d2) {
 	 	return std::pow(d1,d2);
 	}
 	double pow(int d1, double d2) {
 	 	return std::pow((double)d1,d2);
 	 }
 	double pow(double d1, int d2) {
 	 	return std::pow(d1,(double)d2);
 	}
 	double pow(int d1, int d2) {
 	 	return std::pow((double)d1,(double)d2);
 	}
 	DualNum log(DualNum dn) {
 		return DualNum(std::log(dn.real), dn.dual/dn.real);
 	}
 	double log(double d) {
 		return std::log(d);
 	}
 	double log(int n) {
 	 	return std::log(n);
 	}
 	DualNum exp(DualNum dn) {
 		return DualNum(std::exp(dn.real), dn.dual*(std::exp(dn.real)));
 	}
 	double exp(double d) {
 		return std::exp(d);
 	}
 	double exp(int n) {
 		return std::exp(n);
 	}
 	DualNum abs(DualNum dn) {
 		int sign = dn.real == 0 ? 0 : dn.real/(std::abs(dn.real));
 		return DualNum(std::abs(dn.real), dn.dual*sign);
 	}
 	double abs(double d) {
 		return std::abs(d);
 	}
 	double abs(int n) {
 	 	return std::abs(n);
 	}
 	double tan(double d) {
 		return sin(d)/cos(d);
 	}
 	double tan(int i) {
 	 	return sin(i)/cos(i);
 	}
 	double cot(double d) {
 		return cos(d)/sin(d);
 	}
 	double cot(int i) {
 	 	return cos(i)/sin(i);
 	}
 	double sec(double d) {
 	 	return 1/cos(d);
 	}
 	double sec(int i) {
 		return 1/cos(i);
 	}
 	double csc(double d) {
 	 	return 1/sin(d);
 	}
 	double csc(int i) {
 		return 1/sin(i);
 	}
 	DualNum tan(DualNum dn) {
 		return DualNum(tan(dn.real), dn.dual*(pow(sec(dn.real),2)));
 	}
 	DualNum cot(DualNum dn) {
 	 	return DualNum(cot(dn.real), -dn.dual*(pow(csc(dn.real),2)));
 	}
 	DualNum sec(DualNum dn) {
 	 	return DualNum(sec(dn.real), dn.dual*(tan(dn.real)*sec(dn.real)));
 	}
 	DualNum csc(DualNum dn) {
 	 	return DualNum(sec(dn.real), -dn.dual*(cot(dn.real)*csc(dn.real)));
 	}
}

#endif /* DUALNUM_HPP_ */
