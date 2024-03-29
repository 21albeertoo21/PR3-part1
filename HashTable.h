#ifndef TABLAHASH_H
#define TABLAHASH_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/aandgom44/Escritorio/UNI/PRA/PR1/ListLinked.h"

using namespace std;

template <typename V>

class HashTable : public Dict<V>{

	public:
		HashTable(int size){
			n = 0;
			max = size;
			table = new ListLinked<TableEntry<V>>[size]; 
		}
		
		~HashTable(){
			delete[] table;
		}
		
		int capacity(){return max;}
		
		friend ostream& operator<<(ostream &out, const HashTable<V> &th){
			out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << endl;
			out << "================\n\n";
			for(int i = 0; i < th.max; i++){
				out << "== Cubeta " << i << " ==\n\n";
				if(th.table[i].size() == 0)
					out << "List -> []\n\n";
				else{
					out << "List -> [\n";
					for(int j = 0; j < th.table[i].size(); j++){
						out << "\t('" << th.table[i][j].key << "' -> " << th.table[i][j].value << ")" << endl;
					}
					out << "]\n\n";
				}
			}
			out << "================\n\n";
			return out;
		}
		
		V operator[](string key){
			V get_value = search(key);
			
			return get_value;
		}
		
		void insert(string key, V value)override{
			int pos = cubeta(key);
			int aux = capacity();	
			for(int i = 0; i < table[pos].size(); i++){
				if(table[pos][i].key == key)
					throw runtime_error("Key already exists\n");
			}
			TableEntry nueva_entrada(key, value);
			table[pos].append(nueva_entrada);
			n++;
			if(n / aux > 0.5)
				rehash();
		}
		
		V search(string key)override{
			int pos = cubeta(key);
			for(int i = 0; i < table[pos].size(); i++){
				if(table[pos][i].key == key)
					return table[pos][i].value;
			}
				
			throw runtime_error("Key not found\n");
		}
		
		V remove(string key){
			int pos = cubeta(key);
			for(int i = 0; i < table[pos].size(); i++){
				if(table[pos][i].key == key){
					V aux = (table[pos].remove(i)).value; 
					n--;
            		return aux;
            	}
			}
				
			throw runtime_error("Key not found\n");
		}
		
		int entries()override{
			return n;
		}

	private:
		int n; //elementos almacenados en tabla hash (SE ACTUALIZA)
		int max; //tamaño tabla hash (NUM TOTAL DE CUBETAS)
		ListLinked<TableEntry<V>> *table; //array de punteros (TABLA DE CUBETAS)
		
		int cubeta(string key){
			int suma;
			char c;
			int resto;
			for(int i = 0; i < key.length(); i++){
				c = key.at(i);
				suma += int(c);
			}
			resto = suma % max;
			return resto;		
		}
		
		void rehash(){
			max = max * 2;
			ListLinked<TableEntry<V>> *temp;
			temp = new ListLinked<TableEntry<V>>[max];
			TableEntry<V> nodo("", 0);
			for(int i = 0; i < n; i++){
				for(int j = 0; j < table[i].size(); j++){
					nodo.key = table[i][j].key;
                    nodo.value = table[i][j].value;
                    temp[cubeta(table[i][j].key)].append(nodo);
				}
			}
			delete[] table;
			table = temp;
		}
};

#endif
