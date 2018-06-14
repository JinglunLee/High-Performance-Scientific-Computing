#include "amath583.hpp"
#include <iostream>
#include <iomanip>
#include "HRTimer.hpp"
#include <fstream>
#include <iterator>

using namespace std;

int main() {

    HRTimer t;
    HRTimer t2;
    HRTimer t3;
    vector<double> twoNormTimes;
    vector<double> partitionTwoNormTimes;
    vector<double> recursiveTwoNormTimes;
        for (size_t j = 1; j < 24; ++j){
            t.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(pow(2,j));
                twoNorm(x);
            }
            double time =  t.toc();
            time = time/100;
            twoNormTimes.push_back(time);
        }
        ofstream twoNorm_file("./twoNorm.txt");
        ostream_iterator<double> twoNorm_iterator(twoNorm_file, "\n");
        copy(twoNormTimes.begin(), twoNormTimes.end(), twoNorm_iterator);
        for (size_t j = 1; j < 24; ++j){
            t2.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(pow(2,j));
                partitionedTwoNorm(x, 4);
            }
            double time =  t2.toc();
            time = time/100;
            partitionTwoNormTimes.push_back(time);
        }
        ofstream partitionTwoNorm_file("./partititonTwoNorm.txt");
        ostream_iterator<double> partitionTwoNorm_iterator(partitionTwoNorm_file, "\n");
        copy(partitionTwoNormTimes.begin(), partitionTwoNormTimes.end(), partitionTwoNorm_iterator);

        for (size_t j = 1; j < 24; ++j){
            t3.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(pow(2,j));     
                recursiveTwoNorm(x, 4);
            }
            double time =  t3.toc();
            time = time/100;
            recursiveTwoNormTimes.push_back(time);
        }
        ofstream recursiveTwoNorm_file("./recursiveTwoNorm.txt");
        ostream_iterator<double> recursiveTwoNorm_iterator(recursiveTwoNorm_file, "\n");
        copy(recursiveTwoNormTimes.begin(), recursiveTwoNormTimes.end(), recursiveTwoNorm_iterator);
        return 0;
    /*
    Vector x = randomVector(pow(2,4)); 
    cout << "twoNorm() " << setprecision(15) << twoNorm(x) << endl;
    cout << "twoNormAscend " << setprecision(15) << twoNormAscend(x) << endl;
    cout << "twoNormDescend "<< setprecision(15) << twoNormDescend(x) << endl;
    cout << "PartitionedTwoNorm() " <<setprecision(15) << partitionedTwoNorm(x, 5) << endl;
    cout << "Recursive norm " << setprecision(15) << recursiveTwoNorm(x, 4) << endl;
    r
    */

}