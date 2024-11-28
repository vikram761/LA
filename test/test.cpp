#include <linear_algebra.hpp>
#include <iostream>

using namespace std;

int main(){
  Matrix a(3,3,1);
  Vector v(3, 1);
  v = a * v;

  for(size_t i =0;i < v.size(); i++)
    cout << v[i] << " ";
  cout << endl;

  return 0;
}
