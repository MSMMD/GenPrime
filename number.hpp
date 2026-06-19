#pragma once
#include <iostream>
#include <iomanip>
#include "Tests.hpp"

struct number{
    int space; //I'll simple refer as 's' in the complexity analisys
    int digits = 9;
    int base = 10;
    uint64_t *I; //litle endian;

    number(int s):space(s){
        I = new uint64_t[s];
    };

    friend std::ostream& operator<<(std::ostream& os, const number b){ //O(s)
        os<<std::setfill('0');
        for(int i=b.space -1; i>=0; i--) os<<std::setw(b.digits)<<b.I[i];
        return os;
    }

    bool operator==(const number b){ //O(s)
        if(space <= b.space){
            for(int i=0; i<space; i++)
                if(I[i] != b.I[i]) return false;
            
            for(int i=space; i<b.space; i++)
                if(b.I[i]) return false;

            return true;
        }

        for(int i=0; i<b.space; i++)
            if(I[i] != b.I[i]) return false;

        for(int i=b.space; i<space; i++)
            if(I[i]) return false;

        return true;
    }
    template<typename INT> bool operator==(const INT b){ //O(1)
        if(space > 1) return false;
        if(I[0] != b) return false;

        return true;
    }

    bool operator<(const number b){ //O(s)
        if(space < b.space) return true;
        if(space > b.space) return false;
        if(*this == b) return false;

        for(int i=0; i<space; i++)
            if(I[i] > b.I[i]) return false;

        return true;
    }
    template<typename INT> bool operator<(const INT b){ //O(s)
        if(space > 1) return false;
        if(*this == b) return false;

        return I[0]<b;
    }

    number operator+(const number b){ //O(s)
        uint64_t carry=0, mod=Pow_Mod<uint64_t>(base, digits, UINT64_MAX);
        int blocks = std::max(space, b.space);
        if(I[space-1] + b.I[b.space-1] >= mod-1) blocks++;

        number c(blocks); c.I[blocks-1] = 0;
        if(blocks == space) c.I[blocks-1] = I[space-1];
        if(blocks == b.space) c.I[blocks-1] = b.I[b.space-1];

        for(int i=0; i<std::min(space, b.space); i++){
            c.I[i] = (I[i] + b.I[i] + carry) % mod;
            carry = (I[i] + b.I[i] + carry >= mod)? 1:0;
        }
        
        c.I[blocks-1] += carry;
        if(c.I[blocks] == 0) c.space--;
        return c;
    }
    template<typename INT> number operator+(const INT b){ //O(s)
        uint64_t carry=0, mod=Pow_Mod<uint64_t>(base, digits, UINT64_MAX);
        int blocks = space;
        if(I[space-1] + b > mod-1) blocks++;

        number c(blocks); c.I[blocks-1] = 0;

        c.I[0] = (I[0] + b)%mod; carry = (I[0] + b >= mod)? 1:0;
        for(int i=1; i<space; i++){
            c.I[i] = (I[i] + carry) % mod;
            carry = (I[i] + carry >= mod)? 1:0;
        }
        
        c.I[blocks-1] += carry;
        if(c.I[blocks] == 0) c.space--;
        return c;
    }

    number operator- (number b);
    template<typename INT> number operator-(INT b);

    number operator*(number b);
    template<typename INT> number operator*(INT b);

    number operator%(number b);
    template<typename INT> number operator%(INT b);
};