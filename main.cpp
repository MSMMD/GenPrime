#include <iostream>
#include <cstdint>
#include <random>
using namespace std;

#include "Tests.hpp"

int main(){
    cout<<"-------------------------------------\nBig primes generator with uncertainty\n-------------------------------------\n";
    
    uint64_t P, A; //UINT64_MAX: (2^64 -1) 18446744073709551615 | 19 casas que podem valer de 0-9

    unsigned int Number_of_digits;
    cout<<"Choose the Number of Digits: "; cin>>Number_of_digits;
    mt19937_64 gen(0);
    uniform_int_distribution<uint64_t> dist_prime(Pow_Mod<uint64_t>(10, Number_of_digits-1, UINT64_MAX), Pow_Mod<uint64_t>(10, Number_of_digits, UINT64_MAX)-1);
    
    P = dist_prime(gen);
    uniform_int_distribution<uint64_t> dist_base(1, P-1);
    A = dist_base(gen);
    unsigned int iterations=1, target;
    cout<<"Choose the Number of Iterations for the tests: "; cin>>target;
    
    cout<<"Find smalest Miller's Prime?";
    bool NOT_random; cin>>NOT_random;

    if(!NOT_random){
        while(iterations <= target){
            cout<<"P:"<<P<<", A:"<<A<<endl;

            if(Miller_Primality_Test(A,P)){
                iterations++;
                A = dist_base(gen);
            } else {
                iterations = 1;
                P = dist_prime(gen);
                uniform_int_distribution<uint64_t> dist_base(1, P-1);
                A = dist_base(gen);
            }
        }
    } else {
        P = pow(10, Number_of_digits - 1) + 1;
        while(iterations <= target){
            cout<<"P:"<<P<<", A:"<<A<<endl;

            if(Miller_Primality_Test(A,P)){
                iterations++;
                A = dist_base(gen);
            } else {
                iterations = 1;
                P += 2;
                uniform_int_distribution<uint64_t> dist_base(1, P-1);
                A = dist_base(gen);
            }
        }
    }

    long double certainty = pow(1.0/4.0, target); certainty = 1 - certainty;
    cout.precision(30);
    cout<<fixed;


    cout<<"Random Prime P: "<<P<<" with "<<certainty<<" certainty"<<endl;



    return 0;
}