#ifndef INT_ALGOS_H
#define INT_ALGOS_H
#include "int_basic.h"

// Eigentliche Additionsroutine
// Parameter werden durch Call by Value uebergeben, um die 
// Vektoren in der Funktion aendern zu koennen
std::vector <Digit> addition (
      std::vector <Digit> summand1,
      std::vector <Digit> summand2 );

// Allgemeine Multiplikation
std::vector <Digit> multiplikation (
      std::vector <Digit> faktor1,
      std::vector <Digit> faktor2 );

// Allgemeine Multiplikation (Karatsuba)
std::vector <Digit> karatsuba (
      std::vector <Digit> faktor1,
      std::vector <Digit> faktor2 );

#endif // #define INT_ALGOS_H

