#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// y = ax+b
// suma (ax+b - y)^2

int main() {

   string s;
   stringstream ss;
   double x,y;
   double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0, n =0;
   
   
   ifstream f("file");
   
   while ( getline (f, s) )
   {
     //cout << s << endl;
     ss.clear();
     ss << s;
     ss >> x >> y;
     sum_x += x;
     sum_y += y;
     sum_x2 += x*x;
     sum_xy += x*y;
     n++;

     //cout << "x " << x << endl;
     //cout << "y " << y << endl; 
   }

   double a = (sum_y * sum_x2 - sum_x*sum_xy) / (n*sum_x2 - sum_x*sum_x);
   double b = (n*sum_xy - sum_x * sum_y) / (n*sum_x2 - sum_x*sum_x);

   cout << "b " << a << endl;
   cout << "a " << b << endl;

}
