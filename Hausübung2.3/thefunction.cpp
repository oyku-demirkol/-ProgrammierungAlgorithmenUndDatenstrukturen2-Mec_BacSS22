#include <cmath>
#include <iostream>
#include "thefunction.h"

using namespace std;

//The function f and its derivation f' implemented in a separate module thefunction as f() and df()

double f (double x)
{
  return 0.01 * x * x + cos (x);
}

double df (double x)
{
  return 0.02 * x - sin (x);
}

double NumberUserinput(string prompt){
  string inputline;
  double input;
  while(true){
    cout << prompt;
    getline(cin,inputline); //for taking input from user
    if(sscanf(inputline.c_str(), "%lf", &input) == 1) break;
  }
  return input;
}

double Newton(double x_old, double e ){
  double x_new; // x(k+1) = x_new , x(k) = x_old
  // The f() and df() called by the module using Newton's method.
  for(int i = 0; i < 100; ++i)
   { 
     x_new = x_old - (f(x_old)/ df(x_old)); // x(k+1) = x(k) - f(x(k))/f'(x(k))
     if(abs(x_new - x_old) < e) break; //|x(k+1) − x(k)| < ε 
     x_old = x_new;
   }
   
   return x_new;
}

int main (int argc, char* argv[]) 
{
   double x0 = NumberUserinput("start approximation:");
   double e = NumberUserinput("exit barrie: ");
   if(df(x0) == 0){
       cout << "f'(xk) is equal to zero, please start the programm again and enter a valid value" ;
   }else{
   x0 = Newton(x0,e);
   cout << "x=" << x0 << endl ;
     }
}
 
//Christian Vogel
//Gulden Oyku Demirkol