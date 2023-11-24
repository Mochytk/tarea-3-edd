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
/*****
* Int hashInsert
******
* Inserta un elemento en una tabla de hash
******
* Input:
* Ranura HT : Arreglo donde se guardan las claves e información
* Int k: llave
* String& i: información
* .......
******
* Returns:
* Int, 1 si la insercción es exitosa o de lo contrario 0
*****/
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
/*****
* Int hashDelete
******
* Borra un elemento en una tabla de hash
******
* Input:
* Ranura HT : Arreglo donde se guardan las claves e información
* Int k: llave
* .......
******
* Returns:
* string, retorna la información borrada o retorna inválido si no la encuentra
*****/
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

/*****
* Int hashSearch
******
* Busca un elemento en la tabla hash
******
* Input:
* Ranura HT : Arreglo donde se guardan las claves e información
* Int k: llave
* .......
******
* Returns:
* string. Retorna la información pedida. Si no encuentra la clave, retorna no tiene premio o se buscó en toda la tabla.
*****/
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
/*****
* Int h
******
* Método para tratar las colisiones
******
* Input:
* Int k: llave
* .......
******
* Returns:
* Int, retorna la posición
*****/
int hashTable::h(int k) {
    return k % TAM_TABLA; // Función de hash simple
}
