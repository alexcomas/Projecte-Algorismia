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

void usage(){
    cout << "La manera correcta d'executar aques programa és la següent:" << endl
         << "   ./main VAR [n f i COUNT]" << endl << "Si VAR = 'N' es grafica segons el nombre d'elements del fitxer 1." << endl
         << "Si VAR = 'F' es grafica segons el nombre de funcions de hashing." << endl
         << "[n] fixa el nombre d'elements de l'arxiu1, el default és 200." << endl
         << "[f] fixa el nombre de funcions de hashing, el default és l'òptim." << endl
         << "[i] fixa el nombre d'iteracions que es vol fer per a obtenir la mitjana, el default és 200." << endl
         << "Si COUNT = 0 s'implementa el Bloom Filter amb una array de bits." << endl
         << "Si COUNT = 1 s'implementa el Bloom Filter amb una array de comptadors." << endl
         << "ATENCIÓ: Si es volen triar els últims 4 paràmetres, s'han d'especificar tots." << endl;
}

float graficar(int n, int m, int n_functions, int n_iteracions, bool bcounter)
{
    int positives=0;
    int negatives=0;
    int truePositives=0;
    int totalf2=0;

    for(int i = 0; i < n_iteracions; i++){
        pair<int,int> compt = creaArxius::crea(n,i);

        truePositives += compt.first;
        totalf2 += compt.second;

        ifstream f1("dades/arxiu1_" + to_string(i) + ".txt");
        ifstream f2("dades/arxiu2_" + to_string(i) + ".txt");
        string s;
        int key;
        BloomFilter* B = NULL;
        if(bcounter)
            B = new BloomFilterCounter(m, n_functions);
        else
            B = new BloomFilterBit(m, n_functions);

        while(getline(f1,s)){
            key=stoi(s);
            B->add(key);
        }

        while(getline(f2,s)){
            key=stoi(s);
            if(B->check(key)){
                positives++;
            }else{
                negatives++;
            }
        }
    }
    return ((positives - truePositives)/(float)positives)*100;
}

int main(int argc, char *argv[]){
    int n = 200, n_functions, n_iteracions = 100;
    double p = 1.0/100;
    int  m = (int)(-n*log(p) / pow( log(2) , 2 ) );
    n_functions = ceil( (double)m/n * log(2));
    cout << "La mida òptima de l'array és: " << m << endl
         << "El nombre òptim de funcions de hashing és: " << n_functions << endl
         << "La probabilitat de fals positiu hauria de ser: " << exp(-((double)m/n)*pow(log(2),2))*100 << "%" << endl;
    bool bcounter = true;
    if(argc != 2 && argc != 6){
        usage();
        return -1;
    }
    else if(argc == 6){
        n = atoi(argv[2]);
        n_functions = atoi(argv[3]);
        n_iteracions = atoi(argv[4]);
        bcounter = atoi(argv[5]);
    }
    ofstream f("plot_"+ string(argv[1]) +".dat");
    cout << "Comencem: " << endl;
    if(string(argv[1]) == "F"){
        cout << "Nº de funcions de hash (per " + to_string(n) + " elements a l'arxiu1): " << endl;
        for(int i = 1; i <= 15; i++){
            cout << "    " << i << endl;
            f << i << "    " << graficar(n, (int)((double)(i)*n / log(2)), i, n_iteracions, bcounter) << endl;
        }
    }
    else if(string(argv[1]) == "N"){
        cout << "Mida del filtre de Bloom (per " + to_string(n_functions) + " funcions de hash i " + to_string(n) + " elements a l'arxiu1): " << endl;
        for(int i = 1; i <= 20; i++){
            cout << "    " << n*i << endl;
            f << n*i << "    " << graficar(n, n*i, n_functions, n_iteracions, bcounter) << endl;
        }
    }
    else
        cout << "Falla" << endl;
}