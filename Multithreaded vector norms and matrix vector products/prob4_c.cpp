#include "amath583.hpp"
#include <iostream>
#include <iomanip>
#include "HRTimer.hpp"
#include <fstream>
#include <iterator>

using namespace std;

int main() {

    HRTimer t2;
    vector<double> recursiveTwoNormTimes;
 
        for (size_t j = 0; j < 10; ++j){
            t2.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(pow(2,15));
                recursiveTwoNorm(x, j);
            }
            double time =  t2.toc();
            time = time/100;
            recursiveTwoNormTimes.push_back(time);
        }
        ofstream recursiveTwoNorm_file("./differentLevelsN.txt");
        ostream_iterator<double> recursiveTwoNorm_iterator(recursiveTwoNorm_file, "\n");
        copy(recursiveTwoNormTimes.begin(), recursiveTwoNormTimes.end(), recursiveTwoNorm_iterator);
    
    return 0;

}