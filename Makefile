bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp
	
bin/testHashTable: praC.cpp HashTable.h Dict.h TableEntry.h
	mkdir -p bin
	g++ -o bin/testHashTable praC.cpp

clean:
	rm -rf *.o *.gch bin
