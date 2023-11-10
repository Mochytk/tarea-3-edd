#include <iostream>
#include <fstream>
#include "UsortedDict.cpp"

typedef int tipoClave;
typedef int tipoInfo;

int main() {
    // Crear la instancia del nuevo TDA
    UnsortedDict<tipoClave, tipoInfo> hashTable;

    // Lectura de información de premios desde el archivo
    std::ifstream archivo("premios.txt");

    int n;
    archivo >> n;

    for (int i = 0; i < n; ++i) {
        tipoClave num;
        tipoInfo premio;
        archivo >> num >> premio;
        hashTable.insert(num, premio);
    }

    archivo.close();

    // Entrada de números comprados por las personas
    int k;
    std::cin >> k;

    for (int i = 0; i < k; i++) {
        tipoClave numComprado;
        std::cin >> numComprado;

        // Buscar el premio asociado al número comprado
        tipoInfo *premio = hashTable.get(numComprado);

        // Mostrar el premio o indicar que no tiene premio
        if (premio != hashTable.end()) {
            std::cout << *premio << std::endl;
        } else {
            std::cout << "No tiene premio" << std::endl;
        }
    }

    return 0;
}