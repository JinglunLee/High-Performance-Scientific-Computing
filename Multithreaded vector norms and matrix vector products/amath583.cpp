//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2018
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Tommaso Buvoli
//

#include "amath583.hpp"
using namespace std;
// == HW Functions (AMATH 483 & 583) ================================
mutex mtx;

double twoNorm(const Vector& x)
{
    double sum=0;
    for (int i = 0; i < x.num_rows(); ++i){
        sum+= x(i)*x(i);
    }
    return sqrt(sum);
}

double twoNormAscend(Vector&  x)
{
    sort (x.begin(), x.end());
    double sum=0;
    for (int i = 0; i < x.num_rows(); ++i){
        sum+= x(i)*x(i);
    }
    return sqrt(sum);
}

double twoNormDescend(Vector&  x)
{   
    sort (x.begin(), x.end(), greater<double>());
    double sum=0;
    for (int i = 0; i < x.num_rows(); ++i){
        sum+= x(i)*x(i);
    }
    //std::cout<< "Sum before sqrt: " << sum << endl;
    return sqrt(sum);
    return 0;
}

double partitionedTwoNorm(const Vector& x, size_t partitions)
{
    vector<thread> threads;
    double product = 0.0;
    size_t size = floor(x.num_rows()/partitions);
   // std::cout << "Size of a job: " << size << endl;
    for (size_t k=0; k <partitions; ++k){
        int begin = k*size;
        //std::cout<<"begin: " << begin;
        int end;
        if (k < partitions-1){
            end = (k+1)*size;
        }
        else if (k == partitions -1){
            end = x.num_rows();
        }
        //std::cout<<" end: " << end <<endl;
        threads.push_back(thread(ptn_worker,cref(x), begin, end, std::ref(product)));
    }
    //std::cout<<" product: " << product << endl;
    for (size_t k = 0; k < partitions; ++k){
        threads[k].join();
    }
    return sqrt(product);
}

void ptn_worker(const Vector& x, std::size_t begin, size_t end, double& partial)
{
    double sum=0.0;
    //scout << "begin = " << begin << endl;
     for (size_t i = begin; i < end; ++i){
        sum+= x(i)*x(i);
    }
    mtx.lock();
    lock_guard<mutex> lck (mtx,adopt_lock);
    partial += sum;
    //std::cout<<"PARTIAL: " << partial << endl;

}
	
double recursiveTwoNorm(const Vector& x, size_t levels)
{
    return sqrt(rtn_worker(x,0,x.num_rows(), levels));
}

double rtn_worker(const Vector& x, std::size_t begin, std::size_t end, std::size_t level)
{   
    if (level == 0){
        double sum=0.0;
        for (size_t i = begin; i < end; ++i){
            sum+= x(i)*x(i);
        }
        return sum;
    } 
    else {
        vector<future<double>> partial_sum1;
        vector<future<double>> partial_sum2;

        partial_sum1.push_back(async(launch::deferred, rtn_worker, x, begin, begin+(end-begin)/2, level-1));
        partial_sum2.push_back(async(launch::deferred, rtn_worker, x, begin+(end-begin)/2, end, level-1));

        return partial_sum1[0].get() + partial_sum2[0].get();
        
    }
}

// == HW Functions (AMATH 583) ======================================

void task_matvec(const Matrix& A, const Vector& x, Vector& y, std::size_t partitions)
{
    vector<thread> threads;
    double product = 0.0;
    size_t size = floor(x.num_rows()/partitions);
   // std::cout << "Size of a job: " << size << endl;
    for (size_t k=0; k <partitions; ++k){
        int begin = k*size;
        //std::cout<<"begin: " << begin;
        int end;
        if (k < partitions-1){
            end = (k+1)*size;
        }
        else if (k == partitions -1){
            end = x.num_rows();
        }
        //std::cout<<" end: " << end <<endl;
        threads.push_back(thread(ptn_worker,cref(x), begin, end, std::ref(product)));
    }
    //std::cout<<" product: " << product << endl;
    for (size_t k = 0; k < partitions; ++k){
        threads[k].join();
    }

}

void matvec_helper(const Matrix& A, const Vector& x, Vector& y, std::size_t begin, std::size_t end)
{
    double sum=0.0;
    //scout << "begin = " << begin << endl;
     for (size_t i = begin; i < end; ++i){
        for(std::size_t j = 0; j < A.num_cols(); j ++)
        {
            sum += A(i,j) * x(j);
        }
        mtx.lock();
        lock_guard<mutex> lck (mtx,adopt_lock);
        y(i) = sum;
    }

}

// == Random Functions ==============================================

Vector randomVector(std::size_t n)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    
    Vector x(n);
    for (std::size_t i = 0; i < x.num_rows(); i++)
    {
        x(i) = distribution(generator);
    }
    return x;
}

Matrix randomMatrix(std::size_t m, std::size_t n)
{
    static std::default_random_engine             generator;
    static std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    
    Matrix A(m,n);
    for (std::size_t i = 0; i < A.num_rows(); i++)
    {
        for(std::size_t j = 0; j < A.num_cols(); j++)
        {
            A(i,j) = distribution(generator);
        }
    }
    return A;
}

// == Operations ====================================================
void matvec(const Matrix& A, const Vector& x, Vector& y)
{
    double sum = 0;
    for(std::size_t i = 0; i < A.num_rows(); i ++)
    {
        sum = 0.0;
        for(std::size_t j = 0; j < A.num_cols(); j ++)
        {
            sum += A(i,j) * x(j);
        }
        y(i) = sum;
        
    }
}