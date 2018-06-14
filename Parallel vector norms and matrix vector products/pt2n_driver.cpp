#include "amath583.hpp"
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include "Timer.hpp"
#include <cmath>

using namespace std;
int main(int argc, char* argv[]) {
    istringstream iss1(argv[1]);
    istringstream iss2(argv[2]);
    string size_str;
    int size = 0;
    int repeat = 0;
    string repeat_str;
    double serialResult = 0;
    double parallelResult = 0;
    double serialTime = 0;
    double parallelTime = 0;
    double speedup = 0;
    double normDifference = 0;

    if (iss1 >> size_str){
        size = stoi(size_str);
        Vector x = Vector(size);
        randomize(x);
      /*  for (size_t i = 0; i < size; ++i){
            cout << x(i) << endl;
        }
        */
        if (iss2 >> repeat_str){
            repeat = stoi(repeat_str);
            Timer t1;
            Timer t2;

            t1.start();
            for (size_t i = 0; i < repeat; ++i){
                serialResult+= twoNorm(x);
            }
            t1.stop();
            serialTime = t1.elapsed();
            
            t2.start();
            for (size_t i = 0; i < repeat; ++i){
                parallelResult+= ompTwoNorm(x);
            }
            t2.stop();
            parallelTime = t2.elapsed();
            speedup = (parallelTime/serialTime);
            normDifference = (serialResult/repeat) - (parallelResult/repeat);
        }
    cout.precision(15);
    cout << size << " " << (serialTime/repeat) << " " << (parallelTime/repeat) << " " << abs(speedup) << " " << abs(normDifference)<<endl;
    
    }
    return 0;
}