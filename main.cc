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
#include "creaArxius.cc"
#include "BloomFilter.cc"

int main(int argc, char *argv[])
{
    int n;
    int n_functions;
    int n_iteracions;
    int positives=0;
    int negatives=0;
    int truePositives=0;
    int totalf2=0;
    if(argc > 1)
        n = atoi(argv[1]);
    else
        n = 200;
    if(argc > 2)
        n_functions = atoi(argv[2]);
    else
        n_functions = 7;
    if(argc > 3)
        n_iteracions = atoi(argv[3]);
    else
        n_iteracions = 50;
    for(int i = 0; i < n_iteracions; i++){
        pair<int,int> compt = creaArxius::crea(n,i);

        truePositives += compt.first;
        totalf2 += compt.second;

        ifstream f1("dades/arxiu1_" + to_string(i) + ".txt");
        ifstream f2("dades/arxiu2_" + to_string(i) + ".txt");
        string s;
        int key;
        BloomFilterBit B(n, n_functions);

        while(getline(f1,s)){
            key=stoi(s);
            B.add(key);
        }

        while(getline(f2,s)){
            key=stoi(s);
            if(B.check(key)){
                positives++;
            }else{
                negatives++;
            }
        }
    }
    cout << "Positius totals: " << positives << endl;
    cout << "Falços positius: " << positives - truePositives << endl;
    cout << "Percentatge de falços positius per positiu real: " << ((positives - truePositives)/(float)positives)*100 << "%" << endl;
    cout << "Negatius " << negatives << endl;
}