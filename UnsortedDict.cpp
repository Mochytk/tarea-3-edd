#include "UnsortedDict.h"

UnsortedDict::UnsortedDict() {
    // Inicializar la tabla hash
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i].clave = -1; // Usamos -1 para representar una ranura vacía
    }
}

int UnsortedDict::hashInsert(Ranura HT[], int k, const std::string& I) {
    int index = h(k);

    // Verificar si la clave ya existe
    if (HT[index].clave == k) {
        return 0; // No se puede insertar, la clave ya está presente
    }

    // Buscar la siguiente ranura vacía
    while (HT[index].clave != -1) {
        index = (index + 1) % TABLE_SIZE;
    }

    // Insertar en la ranura encontrada
    HT[index].clave = k;
    HT[index].informacion = I;
    return 1; // Inserción exitosa
}

std::string UnsortedDict::hashDelete(Ranura HT[], int k) {
    int index = h(k);

    // Buscar la clave
    while (HT[index].clave != k) {
        if (HT[index].clave == -1) {
            return "invalido"; // Clave no encontrada
        }
        index = (index + 1) % TABLE_SIZE;
    }

    // Eliminar la clave y devolver la información asociada
    HT[index].clave = -1;
    return HT[index].informacion;
}

std::string UnsortedDict::hashSearch(Ranura HT[], int k) {
    int index = h(k);

    // Buscar la clave
    while (HT[index].clave != k) {
        if (HT[index].clave == -1) {
            return "invalido"; // Clave no encontrada
        }
        index = (index + 1) % TABLE_SIZE;
    }

    // Devolver la información asociada
    return HT[index].informacion;
}

int UnsortedDict::h(int k) {
    return k % TABLE_SIZE; // Función de hash simple
}
