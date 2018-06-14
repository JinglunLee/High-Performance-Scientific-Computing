#include "amath583.hpp"
#include <iostream>
#include <iomanip>
#include "HRTimer.hpp"
#include <fstream>
#include <iterator>

using namespace std;

int main() {

    HRTimer t2;
    vector<double> partitionTwoNormTimes;
 
        for (size_t j = 1; j < 20; j+=2){
            t2.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(pow(2,15));
                partitionedTwoNorm(x, j);
            }
            double time =  t2.toc();
            time = time/100;
            partitionTwoNormTimes.push_back(time);
        }
        ofstream partitionTwoNorm_file("./differentPartitionsN.txt");
        ostream_iterator<double> partitionTwoNorm_iterator(partitionTwoNorm_file, "\n");
        copy(partitionTwoNormTimes.begin(), partitionTwoNormTimes.end(), partitionTwoNorm_iterator);
    
    return 0;

}