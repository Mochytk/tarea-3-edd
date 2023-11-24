#ifndef UNSORTEDDICT_HPP
#define UNSORTEDDICT_HPP

#include <iostream>
#include <string>

const int TABLE_SIZE = 100; // Tamaño de la tabla de hashing, puedes ajustarlo según tus necesidades

// Estructura para representar una ranura en la tabla hash
struct Ranura {
    int clave;
    std::string informacion;
};

class UnsortedDict {
public:
    UnsortedDict(); // Constructor
    int hashInsert(Ranura HT[], int k, const std::string& I);
    std::string hashDelete(Ranura HT[], int k);
    std::string hashSearch(Ranura HT[], int k);
    int h(int k);
    Ranura table[TABLE_SIZE]; // Tabla hash
};

#endif
