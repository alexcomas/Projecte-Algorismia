#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

const int N=100000;

int main(){
	ofstream f1("arxiu1.txt");
    ofstream f2("arxiu2.txt");
    
    int n;
    cin>>n;
    
    set<int> numeros;
    set<int>::iterator it;
    it=numeros.end();
    
    int r;
    int s;
    
    srand (time(NULL));
    for(int i=0;i<n;i++){
		r=rand()%(N);
		while(numeros.find(r)!=it){
			r=rand()%(N);
		}
		numeros.insert(r);
		f1<<r<<endl;
		if(rand()%2==0) f2<<r<<endl;
		r=0;
		s=0;
		bool loop = true;
		while(loop){
			r=rand()%(N);
			s=rand()%(N);
			if(!(numeros.find(r)!=it && numeros.find(r)!=it && r==s)){
				loop = false;
			}
		}
		numeros.insert(r);
		numeros.insert(s);
		f2<<r<<endl;
		f2<<s<<endl;
	}
}
