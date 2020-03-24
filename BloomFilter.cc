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

int HashSize=599;
//Provar diferents valors c1 i c2. Els més típics son (0,1) (1,1) i (0.5,0.5)
const float c1=0.5;
const float c2=0.5; 

typedef struct{
	int pos;
	bool trobat;
	int intent;
}hashOutput;

string getMethodName(char* method){ 
	if (!strcmp(method,"Q")) { 
		return "Quadratic Probing";
	}else if(!strcmp(method,"D")) { 
		return "Double Hashing";
	}else { 
		return "Linear Probing";
	}
}


unsigned int to_int(string s){ 
    //cout << (int)s[0] << " + " << (int)s[1]*pow(2,8) << " + " << (int)s[2]*pow(2,16) << " + " << (int)s[3]*pow(2,24) << endl;
    return (unsigned int)s[0]+(unsigned int)s[1]*pow(2,8)+(unsigned int)s[2]*pow(2,16)+(unsigned int)s[3]*pow(2,24);
}

class BloomFilterBit{
    private:
    int m;      // Number of bits of the Bloom Filter
    int n;      // Number of elements of the set the Bloom Filter represents
    int k;      // Number of hash functions used
    uint32_t seed = 26;

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
        SHAed = to_int(sha256(to_string(num).substr(0,4)));
        return (murmured + i*SHAed) % m;
    }


    public:
    vector<bool> values;
    
    BloomFilterBit(int size, int n_functions){
        k = n_functions;
        m = size*(k+1);
        vector<bool> temp(m,0);
        values = temp;
    }

    int size (){
        return m;
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



int main(int argc, char* argv[]){
	char* method;
	string methodName;
    cout << "A" << endl;
	if (argc>1){
		/*method=argv[1];
		methodName=getMethodName(method);*/
        HashSize = atoi(argv[1]);
	}
    ifstream f1("arxiu1.txt");
    ifstream f2("arxiu2.txt");
    string s;
    int key;
    int pos;
    BloomFilterBit B(HashSize, 7);
    hashOutput info;
    cout << "B" << endl;
    int intentsCreador=0;
    int numvalors=0;
    int numvalorsdif=0;

    while(getline(f1,s)){
        key=stoi(s);
        B.add(key);
    }
    
    int valorsTrobats=0;
    int valorsNoTrobats=0;
    int intentsTrobats=0;
    int intentsNoTrobats=0;
    cout << "C" << endl;
    while(getline(f2,s)){
		key=stoi(s);
		if(B.check(key)){
			valorsTrobats++;
			//intentsTrobats+=info.intent;
		}else{
			valorsNoTrobats++;
			//intentsNoTrobats+=info.intent;
		}
	}
	/*cout<<methodName<<endl;
	cout<<"Cost de crear la taula de hash de mida "<<HashSize<<" amb "<<numvalors<<" valors :"<<intentsCreador<<" intents"<<endl;
	cout<<"Promig d'intents: "<<float(intentsCreador)/float(numvalors)<<endl;
	cout<<"-------------------------------------"<<endl;
	cout<<"Promig d'intents en la cerca de valors trobats: "<<float(intentsTrobats)/float(valorsTrobats)<<endl;
	cout<<"Promig d'intents en la cerca de valors no trobats: "<<float(intentsNoTrobats)/float(valorsNoTrobats)<<endl;
	cout<<"-------------------------------------"<<endl;
	cout<<"Promig total: "<<(float(intentsCreador)+float(intentsTrobats)+float(intentsNoTrobats))/(float(numvalors)+float(valorsTrobats)+float(valorsNoTrobats))<<endl;*/
    cout << "Valors trobats: " << valorsTrobats << endl;
    cout << "Valors no trobats: " << valorsNoTrobats << endl;
	
}

/*int main(){
    unsigned int num = 37;
    BloomFilterBit B(7,2);
    B.add(num);
    
    for(int i = 0; i < B.values.size(); i++)
        cout << B.values[i] << " ";
    cout << endl;
    
    cout << B.check(num) << endl;
    cout << B.check(25) << endl;
}*/