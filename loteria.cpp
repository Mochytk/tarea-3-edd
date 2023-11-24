#include <iostream>
#include <fstream>
#include <sstream>
#include "hashTable.h"

int main() {

    // Leer información de premios desde el archivo
    std::ifstream premiosFile("premios.txt");
    int numPremios;
    premiosFile >> numPremios;
    hashTable premios;

    // Insertar premios en la tabla hash
    for (int i = 0; i < numPremios; ++i) {
        int numero;
        std::string premio;
        premiosFile >> numero >> premio;
        premios.hashInsert(premios.table, numero, premio);
    }
	
    premiosFile.close();
	
    // Leer números comprados por las personas
    int numPersonas;
    std::cin >> numPersonas;

    for (int i = 0; i < numPersonas; ++i) {
        int numeroComprado;
        std::cin >> numeroComprado;
        // Buscar el premio asociado al número comprado
        std::string premio = premios.hashSearch(premios.table, numeroComprado);
		
		// Si ya se encontro el premio, eliminarlo
		if (premio != "invalido") {
			premios.hashDelete(premios.table, numeroComprado);
		}
		
        // Mostrar el premio o "No tiene premio"
		if (premio != "invalido") {
            std::cout << premio << std::endl;
        } else {
            std::cout << "No tiene premio" << std::endl;
        }
    }

    return 0;

}