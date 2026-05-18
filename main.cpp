#include <iostream>
#include <cstdint>
using namespace std;

#include "Tests.hpp"

int main(){
    cout<<"-------------------------------------\nBig primes generator with uncertainty\n-------------------------------------\n";
    
    uint64_t P, A; //Unsigned INT 64bits MAX: (2^64 -1) 18446744073709551615 | 19 casas que podem valer de 0-9
    cout<<"Type a number to check if it's prime: "; cin>>P;
    cout<<"Type a number to use as base in the Primality Tests: "; cin>>A;
    
    Fermat_Primality_Test(A, P);
    Miller_Primality_Test(A, P);

    return 0;
}