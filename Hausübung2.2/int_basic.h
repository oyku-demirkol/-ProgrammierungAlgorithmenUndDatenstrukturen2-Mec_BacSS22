#ifndef INT_BASIC_H
#define INT_BASIC_H
#include <iostream>
#include <string>
#include <vector>

class Digit {
  private:
    unsigned int value;
    static unsigned int base;
  public:
    static void set_base (unsigned int base);
    unsigned int get() const;
    static unsigned int get_base();
    Digit (const unsigned int value = 0);
    Digit& operator= (const unsigned int value);
};

// Lesen einer Eingabeziffer aus einem String
Digit digit_from_string (const std::string &s, const int pos);

// Lesen einer kompletten Ziffernfolge aus einem String
std::vector <Digit> digitsequence_from_string (const std::string& s);

// Schreiben einer Ziffernfolge in einen String
std::string string_from_digitsequence (const std::vector <Digit> &digits);

// Ausgabe einer einzelnen Ziffer
std::ostream& operator<< (std::ostream &os, const Digit &digit);

// Ausgabe einer Ziffernfolge
std::ostream& operator<< (std::ostream &os, const std::vector <Digit> &digits);

// Komplementoperation 
// (Einser-Komplement fuer B=2, Neunerkomplement fuer B=10 usw.)
Digit complement (Digit digit);

// Volladdierer, gibt stets Vektor mit zwei Digit-Werten zurueck
// Niederwertige Ziffer des Ergebnisses in Position 0,
// Uebertrag in Position 1 des Rueckgabevektors
std::vector <Digit> elem_add3 (
      const Digit digit1,
      const Digit digit2,
      const Digit digit3 );

// Elementarer Multiplizierer, gibt stets Vektor mit zwei Digit-Werten zurueck
// Niederwertige Ziffer des Ergebnisses in Position 0,
// Uebertrag in Position 1 des Rueckgabevektors
std::vector <Digit> elem_mult (
      const Digit digit1,
      const Digit digit2 );

#endif // #ifndef INT_BASIC_H
