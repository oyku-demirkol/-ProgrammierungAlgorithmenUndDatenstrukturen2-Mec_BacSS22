#include "int_algos.h"

using namespace std;

// Eigentliche Additionsroutine, mit Uebertrag auf die niedrigste Stelle,
// um so Addition und Subtraktion zu ermoeglichen
// Parameter werden durch Call by Value uebergeben, um die 
// Vektoren in der Funktion aendern zu koennen
vector <Digit> additionc (
      vector <Digit> a,
      vector <Digit> b,
      Digit carry )  // Uebertrag
{ 
  // Summanden auf gleiche Laenge ergaenzen
  while (a.size()<b.size()) a.push_back (0);
  while (b.size()<a.size()) b.push_back (0);
  
  // Additionsalgorithmus
  int n = a.size();
  vector <Digit> s (n+1); // Ergebisvektor
  vector <Digit> u (n+1); // Uebertragsvektor
  vector <Digit> aux;     // Hilfsvektor
  
  u[0] = carry; // statt u[0] = 0; mit dieser Abaenderung kann auch
                // die Subtraktion ueber diese Funktion erledigt werden (s.u.)
  
  for( int i=0; i<n; ++i)        // von 0 bis n wiederholen
  {
    aux    = elem_add3(a[i], b[i], u[i]);  // elem_add3 gibt einen vektor zurück 
    s[i]   = aux[0];                       // aux[0] = Summe  mod  Basis -> Rest
    u[i+1] = aux[1];                       // aux[1] = Summe durch Basis -> Übertrag
  }  
  s[n] = u[n];

  // Ergebnis zurueckgeben
  return s;
}

// Eigentliche Additionsroutine
// Parameter werden durch Call by Value uebergeben, um die 
// Vektoren in der Funktion aendern zu koennen
vector <Digit> addition (
      vector <Digit> a,
      vector <Digit> b )
{
  return additionc (a, b, 0);
}

// Subtraktionsroutine
// Parameter werden durch Call by Value uebergeben, um die 
// Vektoren in der Funktion aendern zu koennen
// Implementation setzt ungeprueft subtrahend<minuend voraus
vector <Digit> subtraktion (
      vector <Digit> a,
      vector <Digit> b )
{
  // Operanden auf gleiche Laenge ergaenzen
  while (a.size()<b.size()) a.push_back (0);
  while (b.size()<a.size()) b.push_back (0);

  // Komplement des Subtrahenden erzeugen
  int n = b.size();
  for (int i=0; i<n; ++i) b[i] = complement (b[i]);

  // Aufruf des Additionsalgorithmus mit Uebertrag 1
  auto result = additionc (a, b, 1);
  // Hoechstwertige Ziffer (aus Uebertrag) entfernen
  result.pop_back();
  return result;
}

// Multiplikation einer mehrstelligen und einer einstelligen Zahl
vector <Digit> multn1 (
      vector <Digit> a,
      Digit          b )
{ 
  int n = a.size();
  // Einerstellen- und Uebertragsvektor bereitstellen
  vector <Digit> u (n+1), v (n+1);
  // Abschlieszende 0 in Uebertragsvektor stellen
  u[0] = 0;
  // Ziffernweise multiplizieren
  for (int i=0; i<n; ++i) {
    vector <Digit> aux = elem_mult (a[i], b);
    v[i]   = aux[0];
    u[i+1] = aux[1];
  }
  // Uebertragsvektor mit fuehrender 0 ergaenzen
  v [n] = 0;
  // Einerstellen und Uebertraege addieren
  vector <Digit> p = addition (u, v);
  // Ueberschuessige fuehrende 0 aus Ergebnis entfernen
  p.pop_back ();
  
  // Ergebnis zurueckgeben
  return p;
}

// Allgemeine Multiplikation
vector <Digit> multiplikation (
      vector <Digit> a,
      vector <Digit> b )
{
  // Faktoren auf gleiche Laenge ergaenzen
  while (a.size()<b.size()) a.push_back (0);
  while (b.size()<a.size()) b.push_back (0);

  // Multiplikationsalgorithmus
  int n = a.size();

  // Akkumulator fuer Summe bereitstellen
  vector <Digit> p;

  // Iteriere ueber Ziffern des zweiten Faktors
  for (int i=0; i<n; ++i) {
    vector <Digit> wi = multn1 (a, b[i]);
    // Abschlieszende Nullen ergaenzen
    wi.insert (wi.begin(), i, 0);
    // Fuehrende Nullen ergaenzen
    wi.insert (wi.end(), n-1-i, 0);
    // Zu Akkumulator addieren
    p = addition (p, wi);
    // Ueberschuessige fuehrende Null entfernen
    p.pop_back();
  }

  // Ergebnis zurueckgeben
  return p;
}

// Stellenkorrektur (dezimaler Linksshift)
vector <Digit> shiftleft (
      vector <Digit> input,
      int shiftcount )
{
  input.insert (input.begin(), shiftcount, 0);
  return input;
}

// Allgemeine Multiplikation (Karatsuba)
vector <Digit> karatsuba (
      vector <Digit> a,
      vector <Digit> b )
{
  // Faktoren auf gleiche Laenge ergaenzen
  while (a.size()<b.size()) a.push_back(0);
  while (b.size()<a.size()) b.push_back(0);

  // Karatsuba-Algorithmus
  int n = a.size();

  // HIER ERGAENZEN: Karatsuba-Algorithmus aus Block 3T, Folie 10

  // Anfangsfaelle: Verwende Standardmultiplikation 
  // fuer bis zu dreistellige Zahlen
  if (n<=3) return multiplikation (a, b);

  // Andernfalls: Teile Ziffernfolgen auf
  int k = n / 2;
  vector <Digit> ai, aii, bi, bii;
  aii.insert (aii.begin(), a.begin(),   a.begin()+k);
  ai.insert  (ai.begin(),  a.begin()+k, a.end());
  bii.insert (bii.begin(), b.begin(),   b.begin()+k);
  bi.insert  (bi.begin(),  b.begin()+k, b.end());

  // Bilde Hilfsgroeszen a''', b'''
   vector <Digit> aiii, biii;
  aiii = addition(ai, aii);
  biii = addition(bi, bii);

  // Rekursive Aufrufe
vector <Digit> q1, q2, q3;
  q1 = karatsuba(ai,   bi  );
  q2 = karatsuba(aii,  bii );
  q3 = karatsuba(aiii, biii);

  // Zusammenfassen der Produkte fuer mittleren Summanden
  vector <Digit> r1, r2;
  r1 = subtraktion(q3, q1);
  r2 = subtraktion(r1, q2); 

  // Stellenrichtige Addition der drei Teilausdruecke
  vector <Digit> q1B2k = shiftleft (q1, 2*k);
  vector <Digit> r2Bk = shiftleft (r2, k);
  vector <Digit> s1 = addition (q1B2k, r2Bk);
  vector <Digit> p = addition (s1, q2);


  while (p.size() > 2 * n) p.pop_back();
  return p;
}

//Christian Vogel
//Gülden Öykü Demirkol