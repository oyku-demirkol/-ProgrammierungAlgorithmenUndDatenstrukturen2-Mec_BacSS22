#include "int_basic.h"

using namespace std;

unsigned int Digit::base;

void Digit::set_base (unsigned int base)
{
  Digit::base = base;
  return;
}

unsigned int Digit::get_base()
{
  return base;
}

unsigned int Digit::get() const
{
  return value;
}

Digit::Digit (const unsigned int value) 
{
  if (value < base) this->value = value;
  else this->value = 0;
}

Digit& Digit::operator= (const unsigned int value)
{
  if (value < base) this-> value = value;
  return *this;
}

// Lesen einer Eingabeziffer aus einem String
Digit digit_from_string (const string &s, const int pos)
{
  if (pos<0 || pos>s.length()-1)
    throw string ("Ungueltiger Index");
  if (s[pos]<'0' || (s[pos]>'9' && s[pos] < 'A') || s[pos]>'Z')
    throw string ("Ungueltige Ziffer");
  unsigned int val = s[pos] - '0';
  if (val > 9) val -= ('A' - '9' + 1);
  if (val > Digit::get_base()) throw string ("Ungueltige Ziffer");
  return Digit (val);
}

// Lesen einer kompletten Ziffernfolge aus einem String
vector <Digit> digitsequence_from_string (const string& s) 
{
  vector <Digit> result;
  for (int i=s.length()-1; i>=0; --i)
    result.push_back (digit_from_string (s, i));
  return result;
}

// Schreiben einer Ziffernfolge in einen String
string string_from_digitsequence (const vector <Digit> &digits) 
{
  string result;
  for (int i=digits.size()-1; i>=0; --i) {
    unsigned int val = digits[i].get();
    if (val <= 9) result += (char) ('0' + val);
    else result += (char) ('A' + val - 10);
  }
  return result;
}

// Ausgabe einer einzelnen Ziffer
ostream& operator<< (ostream &os, const Digit& digit)
{
  return os << digit.get();
}

// Ausgabe einer Ziffernfolge
ostream& operator<< (std::ostream &os, const vector <Digit> &digits)
{
  return os << string_from_digitsequence (digits);
}

// Komplementoperation 
// (Einser-Komplement fuer B=2, Neunerkomplement fuer B=10 usw.)
Digit complement (Digit digit)
{
  return Digit::get_base() - digit.get() - 1;
}

// Volladdierer, gibt stets Vektor mit zwei Int-Werten zurueck
// Niederwertige Ziffer des Ergebnisses in Position 0,
// Uebertrag in Position 1 des Rueckgabevektors
vector <Digit> elem_add3 (
      const Digit digit1,
      const Digit digit2,
      const Digit digit3 )
{
  unsigned int sum = digit1.get() + digit2.get() + digit3.get();
  vector<Digit> result (2);
  result [0] = sum % Digit::get_base();
  result [1] = sum / Digit::get_base();
  return result;
}

// Elementarer Multiplizierer, gibt stets Vektor mit zwei Int-Werten zurueck
// Niederwertige Ziffer des Ergebnisses in Position 0,
// Uebertrag in Position 1 des Rueckgabevektors
vector <Digit> elem_mult (
      const Digit digit1,
      const Digit digit2 )
{
  unsigned int prod = digit1.get() * digit2.get();
  vector <Digit> result (2);
  result [0] = prod % Digit::get_base();
  result [1] = prod / Digit::get_base();
  return result;
}


