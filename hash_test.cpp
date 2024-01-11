#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <string>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../prac1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key){
		int suma=0;
		for(int i=0;i<key.size();i++){
			suma+=key[i];
		}
		return suma%capacity();
	};

  int h2(int hash_val)//Recibe en hash_val el valor de la funcion h. Devuelve h+1. Si ese valor > size, return 0.
  {
    int tam = capacity();//Tamaño de tabla hash
    int hashval2 = hash_val +1;
    if (hashval2 < tam) return hashval2;
    else return 0;
  }

    public:
	HashTable(int size){
		n=0;
		max=size;
		table= new ListLinked<TableEntry<V>>[size];
	}
	~HashTable(){
	  std:: cout<<"Borrando"<<std::endl;
		delete[] table;
	}
	int capacity() const{
		return max;
	}
	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		for(int i=0;i<th.capacity();i++){
		  out<<i<<" AAAAAAA" << "\n";
			for(int j=0;j<th.table[i].size();j++)
			out<<th.table[i][j]<<"\n";
		}
		return out;
	}
	V operator[](std::string key){
		V valor=search(key);
		if(valor==-1)
			throw std::runtime_error("No encontrado");
		return valor;
	}
        void insert(std::string key, V value) override{
		int clave=h(key);
		int clave2 = h2(clave);//Llamada a h2 con la posicion devuelta de h.
		TableEntry<V> th(key,value);

		bool  i = table[clave].empty();// si dev 1 vacio
		bool  j = table[clave2].empty();
		  if(i == 0){//Si ya está ocupada, busca en la sig pos.
		 
		  if(j== 0)//Si la pos clave2 esta ocupada
		    {
		      table[clave].prepend(th);//Sube a posicion clave.
		      n++;
		    }
		  else {
		    table[clave2].prepend(th);//Sube a la posicion clave2
		    n++;
		     }
		}
		else
		  {
		    table[clave].prepend(th);//Si la primera posicion no está ocupada.
		    n++;
		  }
		    
		  
	}
	V search(std::string key)override{
		int clave=h(key);
		int clave2 = h2(clave);//Llamada a h2 con la posicion devuelta de h.
		TableEntry<V> th(key);
		int i=table[clave].search(th);
		int j = table[clave2].search(th);
		if(i==-1){
		 
		  if(j==-1)
		    {
			throw std::runtime_error("No encontrado ni en h ni en h2");
		    }
		  else return table[clave2][j].value;
		}
		return table[clave][i].value;
		
	}
	V remove(std::string key)override{

	  int clave=h(key);
	  int clave2 = h2(clave);//Llamada a h2 con la posicion devuelta de h.
               	TableEntry<V> th(key);
		int i=table[clave].search(th);
		int j = table[clave2].search(th);
		if(i==-1){
		  
		  if(j==-1)//No está ni en i ni en j
		    {
			throw std::runtime_error("No encontrado ni en h ni en h2");
		    }
			
		}
		if(i != -1)
		  {
	    
		th=table[clave].remove(i);
		n--;
		  }
		if(j != -1)
		  {
		    th=table[clave2].remove(j);
		    n--;
		  }
		return th.value;
	}
	int entries()override{
		return n;
	}
        
};

#endif
