#include <cstdlib>
#include <iostream>
#include <cstring>

#define MAX_DIGITS_COUNT 256
#define OVERFLOW_STRING "overflow"
#define MINUS_OVERFLOW_STRING "-overflow"
#define ABS(x) ((x >= 0) ? (x) : (-x))
#define MAX(x,y) ((x >= y) ? (x) : (y))

using namespace std;

class Number {
private:
   unsigned short* digits;
   bool sign;
   bool over;
   
   void init();
   void set(long long l);
public:
   Number();
   Number(short s);
   Number(unsigned short s);
   Number(int i);
   Number(unsigned i);
   Number(long l);
   Number(unsigned long l);
   Number(long long l);
   Number(unsigned long long l);
   Number(const char* c);
   Number(const string& s);
   Number(const Number& n);
   
   operator short() const;
   operator unsigned short() const;
   operator int() const;
   operator unsigned() const;
   operator long() const;
   operator unsigned long() const;
   operator long long() const;
   operator unsigned long long() const;
   
   bool operator==(const Number& n) const;
   bool operator!=(const Number& n) const;
   bool operator<(const Number& n) const;
   bool operator>(const Number& n) const;
   bool operator<=(const Number& n) const;
   bool operator>=(const Number& n) const;
   
   Number& operator+(const Number& n) const;
   Number& operator-(const Number& n) const;
   Number& operator*(short s) const;
   Number& operator*(unsigned short s) const;
   Number& operator*(int i) const;
   Number& operator*(unsigned i) const;
   Number& operator*(long l) const;
   Number& operator*(unsigned long l) const;
   Number& operator*(long long l) const;
   Number& operator*(unsigned long long l) const;
   Number& operator*(const Number& n) const;
   Number& operator+=(const Number& n);
   Number& operator-=(const Number& n);
   Number& operator*=(short l);
   Number& operator*=(unsigned short l);
   Number& operator*=(int l);
   Number& operator*=(unsigned l);
   Number& operator*=(long l);
   Number& operator*=(unsigned long l);
   Number& operator*=(long long l);
   Number& operator*=(unsigned long long l);
   Number& operator*=(const Number& n);
   Number& operator++();
   Number& operator++(int);
   Number& operator--();
   Number& operator--(int);
   
   Number& abs() const;
   Number& negation() const;
   Number& pow(long long l) const;
   Number& pow(const Number& n) const;
   
   friend ostream& operator<<(ostream& s, const Number& n);
   friend istream& operator>>(istream& s, Number& n);
   unsigned short getDigit(unsigned index) const;
   void setDigit(unsigned index, unsigned short digit);
   bool getSign() const;
   void setSign(bool sign);
   bool getOver() const;
   void setOver(bool over);
   bool isZero() const;
   unsigned digitsCount() const;
};

/**********************************************************************/

void Number::init() {
   digits = (unsigned short*)malloc(MAX_DIGITS_COUNT * sizeof(unsigned short));
   
   for(int i = 0; i < MAX_DIGITS_COUNT; ++i) {
      digits[i] = 0;
   }
   
   sign = true;
   over = false;
}

void Number::set(long long l) {
   unsigned short digit;
   long long rest;
   
   if(l >= 0) {
      rest = l;
   }
   else {
      sign = false;
      rest = -l;
   }
   
   for(int i = 0; rest > 0; ++i) {
      if(i >= MAX_DIGITS_COUNT) {
         over = true;
         break;
      }
      
      digit = rest % 10;
      rest /= 10;
      digits[i] = digit;
   }
}

/**********************************************************************/

Number::Number() {
   init();
}

Number::Number(short s) {
   init();
   set(s);
}

Number::Number(unsigned short s) {
   init();
   set(s);
}

Number::Number(int i) {
   init();
   set(i);
}

Number::Number(unsigned i) {
   init();
   set(i);
}

Number::Number(long l) {
   init();
   set(l);
}

Number::Number(unsigned long l) {
   init();
   set(l);
}

Number::Number(long long l) {
   init();
   set(l);
}

Number::Number(unsigned long long l) {
   init();
   set(l);
}

Number::Number(const char* c) {
   init();
   
   if(strcmp(c, OVERFLOW_STRING) == 0) {
      over = true;
   }
   else if(strcmp(c, MINUS_OVERFLOW_STRING) == 0) {
      sign = false;
      over = true;
   }
   else {
      int length = strlen(c);
      
      for(int i = 0; i < length; ++i) {
         if(i >= MAX_DIGITS_COUNT) {
            over = true;
            break;
         }
         
         if(c[length - i - 1] == '-') {
            sign = false;
            break;
         }
         
         digits[i] = c[length - i - 1] - '0';
      }
   }
}

Number::Number(const string& s) {
   init();
   
   if(s.compare(OVERFLOW_STRING) == 0) {
      over = true;
   }
   else if(s.compare(MINUS_OVERFLOW_STRING) == 0) {
      sign = false;
      over = true;
   }
   else {
      int length = s.length();
      
      for(int i = 0; i < length; ++i) {
         if(i >= MAX_DIGITS_COUNT) {
            over = true;
            break;
         }
         
         if(s[length - i - 1] == '-') {
            sign = false;
            break;
         }
         
         digits[i] = s[length - i - 1] - '0';
      }
   }
}

Number::Number(const Number& n) {
   init();
   
   sign = n.getSign();
   over = n.getOver();
   
   for(int i = 0; i < MAX_DIGITS_COUNT; ++i) {
      digits[i] = n.getDigit(i);
   }
}

/**********************************************************************/

Number::operator short() const {
   return (short)((long long)(*this));
}

Number::operator unsigned short() const {
   return (unsigned short)((unsigned long long)(*this));
}

Number::operator int() const {
   return (int)((long long)(*this));
}

Number::operator unsigned() const {
   return (unsigned)((unsigned long long)(*this));
}

Number::operator long() const {
   return (long)((long long)(*this));
}

Number::operator unsigned long() const {
   return (unsigned long)((unsigned long long)(*this));
}

Number::operator long long() const {
   long long result = (unsigned long long)(*this);
   
   if(!sign) {
      return -result;
   }
   
   return result;
}

Number::operator unsigned long long() const {
   unsigned long long result = digits[0];
   unsigned long long pow = 10;
   unsigned count = digitsCount();
   
   for(int i = 1; i < count; ++i) {
      result += pow * digits[i];
      pow *= 10;
   }
   
   return result;
}

/**********************************************************************/

bool Number::operator==(const Number& n) const {
   unsigned count = digitsCount();
   
   if(sign != n.getSign() || over != n.getOver() || count != n.digitsCount()) {
      return false;
   }
   
   for(int i = 0; i < count; ++i) {
      if(digits[i] != n.getDigit(i)) {
         return false;
      }
   }
   
   return true;
}

bool Number::operator!=(const Number& n) const {
   return !operator==(n);
}

bool Number::operator<(const Number& n) const {
   unsigned countLeft = digitsCount();
   unsigned countRight = n.digitsCount();
   
   if((countLeft < countRight || !over && n.getOver()) && n.getSign()
   || (countLeft > countRight || over && !n.getOver()) && !sign) {
      return true;
   }
   if((countLeft < countRight || !over && n.getOver()) && !n.getSign()
   || (countLeft > countRight || over && !n.getOver()) && sign) {
      return false;
   }
   
   if(sign < n.getSign()) {
      return true;
   }
   if(sign > n.getSign()) {
      return false;
   }
   
   for(int i = countLeft - 1; i >= 0; --i) {
      if(digits[i] < n.getDigit(i)) {
         return true;
      }
      else if(digits[i] > n.getDigit(i)) {
         return false;
      }
   }
   
   return false;
}

bool Number::operator>=(const Number& n) const {
   return !operator<(n);
}

bool Number::operator>(const Number& n) const {
   unsigned countLeft = digitsCount();
   unsigned countRight = n.digitsCount();
   
   if((countLeft < countRight || !over && n.getOver()) && n.getSign()
   || (countLeft > countRight || over && !n.getOver()) && !sign) {
      return false;
   }
   if((countLeft < countRight || !over && n.getOver()) && !n.getSign()
   || (countLeft > countRight || over && !n.getOver()) && sign) {
      return true;
   }
   
   if(sign < n.getSign()) {
      return false;
   }
   if(sign > n.getSign()) {
      return true;
   }
   
   for(int i = countLeft - 1; i >= 0; --i) {
      if(digits[i] > n.getDigit(i)) {
         return true;
      }
      else if(digits[i] < n.getDigit(i)) {
         return false;
      }
   }
   
   return true;
}

bool Number::operator<=(const Number& n) const {
   return !operator>(n);
}

/**********************************************************************/

Number& Number::operator+(const Number& n) const {
   Number* number = new Number;
   short sum, flow = 0;
   
   int i = 0, max = MAX(digitsCount(), n.digitsCount());
   
   bool addition = (sign == n.getSign());
   bool greater = (abs() >= n.abs());
   
   for(; i < max; ++i) {
      if(addition) {
         sum = digits[i] + n.getDigit(i) + flow;
      }
      else {
         if(greater) {
            sum = digits[i] - n.getDigit(i) + flow;
         }
         else {
            sum = n.getDigit(i) - digits[i] + flow;
         }
      }
      
      if(sum > 9) {
         sum -= 10;
         flow = 1;
      }
      else if(sum < 0) {
         sum += 10;
         flow = -1;
      }
      else {
         flow = 0;
      }
      
      number->setDigit(i, sum);
   }
   
   if(flow > 0) {
      if(i >= MAX_DIGITS_COUNT) {
         number->setOver(true);
      }
      else {
         number->setDigit(i, flow);
      }
   }
   
   if(over || n.getOver()) {
      number->setOver(true);
   }
   
   if(number->isZero()) {
      number->setSign(true);
   }
   else if(greater) {
      number->setSign(sign);
   }
   else {
      number->setSign(n.getSign());
   }
   
   return *number;
}

Number& Number::operator-(const Number& n) const {
   return operator+(n.negation());
}

Number& Number::operator*(short s) const {
   return *this * (long long)s;
}

Number& Number::operator*(unsigned short s) const {
   return *this * (unsigned long long)s;
}

Number& Number::operator*(int i) const {
   return *this * (long long)i;
}

Number& Number::operator*(unsigned i) const {
   return *this * (unsigned long long)i;
}

Number& Number::operator*(long l) const {
   return *this * (long long)l;
}

Number& Number::operator*(unsigned long l) const {
   return *this * (unsigned long long)l;
}

Number& Number::operator*(long long l) const {
   Number* number = new Number;
   long long abs = ABS(l);
   
   for(long long i = 0; i < abs; ++i) {
      *number += *this;
   }
   
   if(number->isZero()) {
      number->setSign(true);
   }
   else {
      number->setSign(sign == (l >= 0));
   }
   
   return *number;
}

Number& Number::operator*(unsigned long long l) const {
   Number* number = new Number;
   
   for(unsigned long long i = 0; i < l; ++i) {
      *number += *this;
   }
   
   if(number->isZero()) {
      number->setSign(true);
   }
   else {
      number->setSign(sign);
   }
   
   return *number;
}

Number& Number::operator*(const Number& n) const {
   Number* number = new Number;
   Number abs = n.abs();
   
   for(Number i; i < abs; ++i) {
      *number = *number + *this;
   }
   
   if(number->isZero()) {
      number->setSign(true);
   }
   else {
      number->setSign(sign == n.getSign());
   }
   
   return *number;
}

Number& Number::operator+=(const Number& n) {
   *this = *this + n;
   
   return *this;
}

Number& Number::operator-=(const Number& n) {
   *this = *this - n;
   
   return *this;
}

Number& Number::operator*=(short s) {
   *this = *this * s;
   
   return *this;
}

Number& Number::operator*=(unsigned short s) {
   *this = *this * s;
   
   return *this;
}

Number& Number::operator*=(int i) {
   *this = *this * i;
   
   return *this;
}

Number& Number::operator*=(unsigned i) {
   *this = *this * i;
   
   return *this;
}

Number& Number::operator*=(long l) {
   *this = *this * l;
   
   return *this;
}

Number& Number::operator*=(unsigned long l) {
   *this = *this * l;
   
   return *this;
}

Number& Number::operator*=(long long l) {
   *this = *this * l;
   
   return *this;
}

Number& Number::operator*=(unsigned long long l) {
   *this = *this * l;
   
   return *this;
}

Number& Number::operator*=(const Number& n) {
   *this = *this * n;
   
   return *this;
}

Number& Number::operator++() {
   *this = *this + Number(1);
   
   return *this;
}

Number& Number::operator++(int) {
   Number* number = new Number(*this);
   *this = *this + Number(1);
   
   return *number;
}

Number& Number::operator--() {
   *this = *this - Number(1);
   
   return *this;
}

Number& Number::operator--(int) {
   Number* number = new Number(*this);
   *this = *this - Number(1);
   
   return *number;
}

/**********************************************************************/

Number& Number::abs() const {
   Number* number = new Number(*this);
   number->setSign(true);
   
   return *number;
}

Number& Number::negation() const {
   Number* number = new Number(*this);
   if(!isZero()) {
      number->setSign(!sign);
   }
   
   return *number;
}

Number& Number::pow(long long l) const {
   if(l < 0) {
      return *(new Number);
   }
   
   Number* number = new Number(1);
   long long abs = ABS(l);
   
   for(long long i = 0; i < abs; ++i) {
      *number *= *this;
   }
   
   return *number;
}

Number& Number::pow(const Number& n) const {
   if(!n.getSign()) {
      return *(new Number);
   }
   
   Number* number = new Number(1);
   Number abs = n.abs();
   
   for(Number i; i < abs; ++i) {
      *number *= *this;
   }
   
   return *number;
}

/**********************************************************************/

ostream& operator<<(ostream& s, const Number& n) {
   if(!n.sign) {
      s << "-";
   }
   
   if(n.over) {
      s << OVERFLOW_STRING;
   }
   else {
      for(int i = n.digitsCount() - 1; i >= 0; --i) {
         s << n.digits[i];
      }
   }
   
   return s;
}

istream& operator>>(istream& s, Number& n) {
   string str;
   s >> str;
   
   n = *(new Number(str));
   
   return s;
}

unsigned short Number::getDigit(unsigned index) const {
   return digits[index];
}

void Number::setDigit(unsigned index, unsigned short digit) {
   digits[index] = digit;
}

bool Number::getSign() const {
   return sign;
}

void Number::setSign(bool sign) {
   this->sign = sign;
}

bool Number::getOver() const {
   return over;
}

void Number::setOver(bool over) {
   this->over = over;
}

bool Number::isZero() const {
   for(int i = 0; i < MAX_DIGITS_COUNT; ++i) {
      if(digits[i] != 0) {
         return false;
      }
   }
   
   return true;
}

unsigned Number::digitsCount() const {
   int i = MAX_DIGITS_COUNT - 1;
   
   for(; i > 0; --i) {
      if(digits[i] != 0) {
         break;
      }
   }
   
   return i+1;
}

/**********************************************************************/

int main() {
   Number a, b;
   
   cout << "Enter first number:" << endl;
   cin >> a;
   
   cout << "Enter second number:" << endl;
   cin >> b;
   
   cout << "The sum is:" << endl << (a+b) << endl;
   
   return 0;
}
