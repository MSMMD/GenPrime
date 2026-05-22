#include <iostream>
#include <cstdint>
#include <random>
using namespace std;

#include "Tests.hpp"

int main(){
    cout<<"-------------------------------------\nBig primes generator with uncertainty\n-------------------------------------\n";
    
    uint64_t P, A; //UINT64_MAX: (2^64 -1) 18446744073709551615 | 19 casas que podem valer de 0-9
    cout<<"Type a number to check if it's prime: "; cin>>P;
    cout<<"Type a number to use as base in the Primality Tests: "; cin>>A;
    
    Fermat_Primality_Test(A, P);
    Miller_Primality_Test(A, P);

    unsigned int Number_of_digits=10;
    cout<<"Choose the Number of Digits: "; cin>>Number_of_digits;
    mt19937_64 gen(0);
    uniform_int_distribution<uint64_t> dist(Pow_Mod(10, Number_of_digits-1, UINT64_MAX), Pow_Mod(10, Number_of_digits, UINT64_MAX)-1);
    cout<<"Random number P: "<<dist(gen)<<endl;


    return 0;
}