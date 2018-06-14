#include "amath583.hpp"
#include <iostream>
#include <iomanip>
#include "amath583IO.hpp"

using namespace std;

int main() {

    int n = 1000;
    Vector x = randomVector(n); 

    cout << setprecision(15) << twoNorm(x) << endl;
    cout << setprecision(15) << twoNormAscend(x) << endl;
    cout << setprecision(15) << twoNormDescend(x) << endl;
    return 0;
}