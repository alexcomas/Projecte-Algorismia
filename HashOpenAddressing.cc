#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

typedef struct{
	int pos;
	bool trobat;
	int intent;
}hashOutput;

const int HashSize=599;
//Provar diferents valors c1 i c2. Els més típics son (0,1) (1,1) i (0.5,0.5)
const float c1=0.5;
const float c2=0.5; 

hashOutput hashL (int key, const vector<int>& taula){
	hashOutput info;
    int posicio = key%HashSize;
    int intent = 1;
	while(taula[posicio]!=-1 && taula[posicio]!=key){
		posicio = (posicio+1)%HashSize;
		intent++;
	}
    info.trobat=(taula[posicio]==key);
    info.pos=posicio;
    info.intent=intent;
    return info;
}

hashOutput hashQ (int key, const vector<int>& taula){
	hashOutput info;
    int posicio = key%HashSize;
    int intent = 1;
    int i=0;
	float suma;
	while(taula[posicio]!=-1 && taula[posicio]!=key){
		suma=c1*float(i)+c2*float(i*i);
		posicio = (posicio+(int)suma)%HashSize;
		intent++;
		i++;
	}
	 
    info.trobat=(taula[posicio]==key);
    info.pos=posicio;
    info.intent=intent;
    return info;
}

hashOutput hashD (int key, const vector<int>& taula){
	hashOutput info;
    int posicio = key%HashSize;
    int intent = 1;
	int i=0;
	int hash2 = 7-(key%7);
	while(taula[posicio]!=-1 && taula[posicio]!=key){
		posicio = (posicio+i*hash2)%HashSize;
		intent++;
		i++;
	}
    info.trobat=(taula[posicio]==key);
    info.pos=posicio;
    info.intent=intent;
    return info;
}

hashOutput hash1(int key, const vector<int>& taula, char* method){ 
	if (!strcmp(method,"Q")) { 
		return hashQ(key,taula);
	}else if(!strcmp(method,"D")) { 
		return hashD(key,taula);
	}else { 
		return hashL(key,taula);
	}
}

string getMethodName(char* method){ 
	if (!strcmp(method,"Q")) { 
		return "Quadratic Probing";
	}else if(!strcmp(method,"D")) { 
		return "Double Hashing";
	}else { 
		return "Linear Probing";
	}
}

int main(int argc, char* argv[]){
	char* method;
	string methodName;
	if (argc>1){
		method=argv[1];
		methodName=getMethodName(method);
	}
    ifstream f1("arxiu1.txt");
    ifstream f2("arxiu2.txt");
    string s;
    int key;
    int pos;
    vector<int> th(HashSize,-1);
    hashOutput info;
    
    int intentsCreador=0;
    int numvalors=0;
    int numvalorsdif=0;

    while(getline(f1,s)){
        key=stoi(s);
        info=hash1(key,th,method);
        th[info.pos]=key;
        intentsCreador+=info.intent;
        numvalors++;
        if(!info.trobat)numvalorsdif++;
    }
    
    int valorsTrobats=0;
    int valorsNoTrobats=0;
    int intentsTrobats=0;
    int intentsNoTrobats=0;
    
    while(getline(f2,s)){
		key=stoi(s);
		info=hash1(key,th,method);
		if(info.trobat){
			valorsTrobats++;
			intentsTrobats+=info.intent;
		}else{
			valorsNoTrobats++;
			intentsNoTrobats+=info.intent;
		}
	}
	cout<<methodName<<endl;
	cout<<"Cost de crear la taula de hash de mida "<<HashSize<<" amb "<<numvalors<<" valors :"<<intentsCreador<<" intents"<<endl;
	cout<<"Promig d'intents: "<<float(intentsCreador)/float(numvalors)<<endl;
	cout<<"-------------------------------------"<<endl;
	cout<<"Promig d'intents en la cerca de valors trobats: "<<float(intentsTrobats)/float(valorsTrobats)<<endl;
	cout<<"Promig d'intents en la cerca de valors no trobats: "<<float(intentsNoTrobats)/float(valorsNoTrobats)<<endl;
	cout<<"-------------------------------------"<<endl;
	cout<<"Promig total: "<<(float(intentsCreador)+float(intentsTrobats)+float(intentsNoTrobats))/(float(numvalors)+float(valorsTrobats)+float(valorsNoTrobats))<<endl;
	
}

