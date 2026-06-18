#pragma once
#include <cstdint>

template <typename INT> INT Pow_Mod(INT a, INT x, INT p){
    if(!x) return 1;

    if(!(x%2)){
        INT r = Pow_Mod(a, x/2, p);
        return (r*r) % p;
    }

    INT r = Pow_Mod(a, (x-1)/2, p);
    r = (r*r)%p;
    return (a*r)%p;
}

template <typename INT> bool Fermat_Primality_Test(INT a, INT p){
    INT R = Pow_Mod(a, p-1, p);

    if(R==1)return 1;
    return 0;
}

template <typename INT> struct Info{
    bool FAILS;
    INT remainder;
};

template <typename INT> Info<INT> Pow_Mod_Miller(INT a, INT x, INT p){
    if(!x) return {0,1};
    Info<INT> ret, i;
    INT r;

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

template <typename INT> bool Miller_Primality_Test(INT a, INT p){
    Info I = Pow_Mod_Miller(a, p-1, p);

    if(I.remainder==1 && !I.FAILS) return 1;
    return 0;
}