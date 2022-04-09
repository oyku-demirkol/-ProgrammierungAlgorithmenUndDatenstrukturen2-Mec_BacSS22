#include "int_basic.h"
#include "int_algos.h"
#include <cstdlib>
#include <functional>

using namespace std;

// Testumgebung
int main (int argc, char* argv[]) 
{
  if (argc<4) {
    cerr << "Aufruf: " << argv[0] << " operation operand1 operand2" << endl;
    exit (-1);
  }

  // Eingabeargumente in C++-Strings einlesen
  string operation_s = argv[1];
  string input1 = argv[2];
  string input2 = argv[3];

  Digit::set_base (10);

  // Die Vektoren operand1, operand2 sollen die Ziffern der Eingabewerte
  // speichern, und zwar in der Indizierung wie in der Vorlesung
  // (Index 0 fuer niederwertigste Ziffer)
  vector <Digit> operand1 = digitsequence_from_string (input1);
  vector <Digit> operand2 = digitsequence_from_string (input2);

  // Aufruf des Algorithmus
  function <vector <Digit> (vector <Digit>, vector <Digit>)> operation;
  if (operation_s == "a") operation = addition;
  if (operation_s == "m") operation = multiplikation;
  if (operation_s == "k") operation = karatsuba;
  vector <Digit> result = operation (operand1, operand2);

  // Ergebnis ausgeben
  cout << result << endl;

  return 0;
}

