#include "amath583.hpp"
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include "Timer.hpp"
#include <cmath>
#include <thread>
#include "CSRMatrix.hpp"

using namespace std;
int main(int argc, char* argv[]) {
    istringstream iss1(argv[1]);
    string size_str;
    int size = 0;
    double serialResult = 0;
    double parallelResult = 0;
    double serialTime = 0;
    double parallelTime = 0;
    double speedup = 0;
    double normDifference = 0;
    short num_cores = thread::hardware_concurrency();
    short num_threads = omp_get_num_threads();
    if (iss1 >> size_str){
        size = stoi(size_str);
        Vector x = Vector(size*size);
        Vector y = Vector(size*size);
        randomize(x);
        zeroize(y);
        CSRMatrix A(size*size,size*size);
        piscetize(A,size, size);
            Timer t1;
            Timer t2;
            t1.start();
            matvec(A,x,y);
            t1.stop();
            serialResult = twoNorm(y);
            serialTime = t1.elapsed();
            zeroize(y);
            t2.start();
            ompMatvec(A,x,y);
            t2.stop();
            parallelResult = ompTwoNorm(y);
            parallelTime = t2.elapsed();
            speedup = (parallelTime/serialTime);
            normDifference = serialResult - parallelResult;
        }
    cout.precision(15);
    cout << num_cores << " " <<num_threads << " " << size <<" " << serialTime;
    cout << " " << parallelTime << " " << speedup << " " << abs(normDifference)<<endl; 
    return 0;
}