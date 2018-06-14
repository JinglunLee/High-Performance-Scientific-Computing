#include "amath583.hpp"
#include <iostream>
#include <iomanip>
#include "HRTimer.hpp"
#include <fstream>
#include <iterator>
#include "amath583IO.hpp"

using namespace std;

int main() {
    /*
    Vector y(n);
    matvec(A,x,y);
    string matvec_file = "matvec.txt";
    writeVector(y, matvec_file);

    task_matvec(A,x,y, 8);
    string task_matvec_file = "task_matvec.txt";
    writeVector(y, task_matvec_file);
    */
    HRTimer t;
    HRTimer t2;
    HRTimer t3;
    vector<double> matvecTimes;
        for (size_t j = 1; j < 14; ++j){
            t.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(j); 
                Matrix A = randomMatrix(j,j);
                Vector y(j);
                matvec(A,x,y);
            }
            double time =  t.toc();
            time = time/100;
            matvecTimes.push_back(time);
        }
        ofstream matvecTimes_file("./matvecTimes.txt");
        ostream_iterator<double> matvecTimes_iterator(matvecTimes_file, "\n");
        copy(matvecTimes.begin(), matvecTimes.end(), matvecTimes_iterator);
    
    vector<double> task_matvecTimes1;
        for (size_t j = 1; j < 14; ++j){
            t.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(j); 
                Matrix A = randomMatrix(j,j);
                Vector y(j);
                task_matvec(A,x,y,2);
            }
            double time =  t.toc();
            time = time/100;
            task_matvecTimes1.push_back(time);
        }
        ofstream task_matvecTimes_file("./task_matvecTimes1.txt");
        ostream_iterator<double> task_matvecTimes_iterator(task_matvecTimes_file, "\n");
        copy(task_matvecTimes1.begin(), task_matvecTimes1.end(), task_matvecTimes_iterator);
    
    vector<double> task_matvecTimes2;
        for (size_t j = 1; j < 14; ++j){
            t.tic();
            for (size_t i = 0; i < 100; ++i){
                Vector x = randomVector(j); 
                Matrix A = randomMatrix(j,j);
                Vector y(j);
                task_matvec(A,x,y,4);
            }
            double time =  t.toc();
            time = time/100;
            task_matvecTimes2.push_back(time);
        }
        ofstream task_matvecTimes_file2("./task_matvecTimes2.txt");
        ostream_iterator<double> task_matvecTimes_iterator2(task_matvecTimes_file2, "\n");
        copy(task_matvecTimes2.begin(), task_matvecTimes2.end(), task_matvecTimes_iterator2);


    return 0;
}