#include <iostream>
#include <string>

const int TAM_TABLA = 100; // Tamaño de la tabla de hashing

// Struct para representar una ranura en la tabla hash
struct Ranura {
    int clave;
    std::string informacion;
};

class hashTable {
public:
    hashTable(); // Constructor
    int hashInsert(Ranura HT[], int k, const std::string& I);
    std::string hashDelete(Ranura HT[], int k);
    std::string hashSearch(Ranura HT[], int k);
    int h(int k);
    Ranura table[TAM_TABLA];
};

///////////////////////////////////////////////////////////////////////////////////////

hashTable::hashTable() {
    // Inicializar la tabla hash
    for (int i = 0; i < TAM_TABLA; ++i) {
        table[i].clave = -1; // Usamos -1 para representar una ranura vacía
    }
}

int hashTable::hashInsert(Ranura HT[], int k, const std::string& I) {
    int index = h(k);

    // Verificar si la clave ya existe
    if (HT[index].clave == k) {
        return 0; // No se puede insertar, la clave ya está presente
    }

    // Buscar la siguiente ranura vacía
    while (HT[index].clave != -1) {
        index = (index + 1) % TAM_TABLA;
    }

    // Insertar en la ranura encontrada
    HT[index].clave = k;
    HT[index].informacion = I;
    return 1; // Inserción exitosa
}

std::string hashTable::hashDelete(Ranura HT[], int k) {
    int index = h(k);

    // Buscar la clave
    while (HT[index].clave != k) {
        if (HT[index].clave == -1) {
            return "invalido"; // Clave no encontrada
        }
        index = (index + 1) % TAM_TABLA;
    }

    // Eliminar la clave y retornar la información asociada
    HT[index].clave = -1;
    return HT[index].informacion;
}


std::string hashTable::hashSearch(Ranura HT[], int k) {
    int index = h(k);
    int startIndex = index;

    // Buscar la clave
    while (HT[index].clave != k) {
        if (HT[index].clave == -1 || index == startIndex) {
            return "No tiene premio"; // Clave no encontrada o se ha revisado toda la tabla
        }
        index = (index + 1) % TAM_TABLA;
    }

    // Retornar la información asociada
    return HT[index].informacion;
}

int hashTable::h(int k) {
    return k % TAM_TABLA; // Función de hash simple
}