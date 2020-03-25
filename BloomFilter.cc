#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <stdio.h>


using namespace std;

#include "hash_functions/MurmurHash3.h"
#include "hash_functions/sha256.h"

class BloomFilter {
    protected:
    int m;      // Number of bits or counters of the Bloom Filter
    int n;      // Number of elements of the set the Bloom Filter represents
    int k;      // Number of hash functions used
    uint32_t seed = 26;

    static unsigned int to_int(string s){ 
        return (unsigned int)s[0]+(unsigned int)s[1]*pow(2,8)+(unsigned int)s[2]*pow(2,16)+(unsigned int)s[3]*pow(2,24);
    }

    /**
     * Function that hashes numbers as k independent hash functions based on only two independent hash functions, which are MurmurHash3 and SHA256 and returns the result (mod m).
     * Parameters:
     *      i -> 1 <= i <= k lineal factor which determines which independent hash function-
     *      num -> number we wish to hash
     */ 
    int hash(int i, unsigned int num){
        if(i < 0 || i >= k) return -1;
        unsigned int murmured;
        unsigned int SHAed;
        MurmurHash3_x86_32(&num, 1, seed, &murmured);
        SHAed = BloomFilter::to_int(sha256(to_string(num).substr(0,4)));
        return (murmured + i*SHAed) % m;
    }

    public:
    
    int size (){
        return m;
    }

    virtual void add (unsigned int s){};

    virtual bool check(unsigned int s){};
};


class BloomFilterBit : public BloomFilter{
    private:
    vector<bool> values;

    public:
    
    BloomFilterBit(int size, int n_functions){
        k = n_functions;
        m = size;
        vector<bool> temp(m,0);
        values = temp;
    }

    void add (unsigned int s){
        for(int i = 0; i < k; i++){
            values[hash(i, s)] = 1;
        }
    }
    
    bool check(unsigned int s){
        for(int i = 0; i < k; i++)
            if(values[hash(i, s)] != 1)
                return false;
        return true;
    }

};

class BloomFilterCounter : public BloomFilter{
    private:
    vector<int> values;

    public:
    
    BloomFilterCounter(int size, int n_functions){
        k = n_functions;
        m = size;
        vector<int> temp(m,0);
        values = temp;
    }

    void add (unsigned int s){
        for(int i = 0; i < k; i++){
            values[hash(i, s)] += 1;
        }
    }
    
    int del (unsigned int s){
        if(check(s)){
            for(int i = 0; i < k; i++){
                values[hash(i, s)] -= 1;
            }
            return 0;
        }
        else
            return -1;
    }

    bool check(unsigned int s){
        for(int i = 0; i < k; i++)
            if(values[hash(i, s)] == 0)
                return false;
        return true;
    }

};