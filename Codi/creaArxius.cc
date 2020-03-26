#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

const int N=100000;

class creaArxius {
	private:
	
	static int genRandom(set<int>& numeros){
		int r=rand()%(N);
		while(numeros.find(r)!=numeros.end()){
			r=rand()%(N);
		}
		numeros.insert(r);
		return r;
	}

	public:
	static pair<int,int> crea(int n, int nfile){
		ofstream f1("dades/arxiu1_" + to_string(nfile) + ".txt");
		ofstream f2("dades/arxiu2_" + to_string(nfile) + ".txt");
		
		int comptf1af2=0;
		int compt2 = 0;
		set<int> numeros;   
		
		srand (time(NULL));
		for(int i=0;i<n;i++){
			int r=genRandom(numeros);
			f1<<r<<endl;
			if(rand()%2==0){
				comptf1af2++;
				f2<<r<<endl;
			}
			f2<<genRandom(numeros)<<endl;
			f2<<genRandom(numeros)<<endl;
			compt2 += 2;
		}
		compt2 += comptf1af2;
		return pair<int,int>(comptf1af2, compt2);
	}

};
