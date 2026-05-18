#pragma once
#include <cstdint>


uint64_t Pow_Mod(uint64_t a, uint64_t x, uint64_t p);
bool Fermat_Primality_Test(uint64_t a, uint64_t p);

struct Info{
    bool FAILS;
    uint64_t remainder;
};

Info Pow_Mod_Miller(uint64_t a, uint64_t x, uint64_t p);
bool Miller_Primality_Test(uint64_t a, uint64_t p);