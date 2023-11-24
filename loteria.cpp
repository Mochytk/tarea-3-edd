#include <iostream>
#include <fstream>
#include <sstream>
#include "UnsortedDict.cpp"

int main() {
    // Leer información de premios desde el archivo
    std::ifstream premiosFile("premios.txt");
    if (!premiosFile.is_open()) {
        std::cerr << "Error al abrir el archivo de premios" << std::endl;
        return 1;
    }

    int numPremios;
    premiosFile >> numPremios;

    UnsortedDict premiosDict;

    // Insertar premios en la tabla hash
    for (int i = 0; i < numPremios; ++i) {
        int numero;
        std::string premio;
        premiosFile >> numero >> premio;
        premiosDict.hashInsert(premiosDict.table, numero, premio);
    }

    premiosFile.close();

    // Leer números comprados por las personas
    int numPersonas;
    std::cin >> numPersonas;

    for (int i = 0; i < numPersonas; ++i) {
        int numeroComprado;
        std::cin >> numeroComprado;

        // Buscar el premio asociado al número comprado
        std::string premio = premiosDict.hashSearch(premiosDict.table, numeroComprado);

        // Mostrar el premio o "No tiene premio"
        std::cout << (premio != "invalido" ? premio : "No tiene premio") << std::endl;
    }

    return 0;
}
