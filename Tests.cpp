#include "Tests.hpp"
#include <iostream>

uint64_t Pow_Mod(uint64_t a, uint64_t x, uint64_t p){
    if(!x) return 1;

    if(!(x%2)){
        uint64_t r = Pow_Mod(a, x/2, p);
        return (r*r) % p;
    }

    uint64_t r = Pow_Mod(a, (x-1)/2, p);
    r = (r*r)%p;
    return (a*r)%p;
}

bool Fermat_Primality_Test(uint64_t a, uint64_t p){
    uint64_t R = Pow_Mod(a, p-1, p);

    if(R==1){
        std::cout<<"It's a Fermat's Prime\n";
        return 1;
    }
    
    std::cout<<"It's NOT a Fermat's Prime. Remainder = "<<R<<std::endl;
    return 0;
}

Info Pow_Mod_Miller(uint64_t a, uint64_t x, uint64_t p){
    if(!x) return {0,1};
    Info ret, i;
    uint64_t r;

    if(!(x%2)){
        i = Pow_Mod_Miller(a, x/2, p);
        r = i.remainder;

        ret.remainder = (r*r)%p;
        ret.FAILS = ((ret.remainder == 1) && (r != 1) && (r != p-1)) || i.FAILS;
    } else {
        i = Pow_Mod_Miller(a, (x-1)/2, p);
        r = i.remainder;

        ret.remainder = (r*r)%p;
        ret.remainder = (a*ret.remainder)%p;
        ret.FAILS = 0;
    }

    return ret;
}

bool Miller_Primality_Test(uint64_t a, uint64_t p){
    Info I = Pow_Mod_Miller(a, p-1, p);

    if(I.remainder==1 && !I.FAILS){
        std::cout<<"It's a Miller's Prime\n";
        return 1;
    }
    
    std::cout<<"It's NOT a Miller's Prime. Remainder = "<<I.remainder<<std::endl;
    return 0;
}