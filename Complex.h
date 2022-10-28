#ifndef COMPLEX_H
#define COMPLEX_H
#include <math.h>
class Complex {
private :
   float thuc;
   float ao;
public:
   Complex (float t = 0.0, float a = 0.0): thuc(t), ao(a) {}
   float getModulus () const {
      return sqrt (thuc * thuc + ao * ao);
   }
   bool operator< (const Complex& other) {
      return (this->getModulus() < other.getModulus());
   }
   bool operator== (const Complex& other) {
      return (this->getModulus() == other.getModulus());
   }
   bool operator<= (const Complex& other) {
      return (this->getModulus() <= other.getModulus());
   }
   bool operator>= (const Complex& other) {
      return !(this->operator<(other));
   }
   bool operator> (const Complex& other) {
      return !(this->operator<=(other));
   }
   bool operator!= (const Complex& other) {
      return !(this->operator==(other));
   }
};
#endif /* COMPLEX_H */