#define TAMANO_TABLA 100 // Tamaño de la tabla hash

typedef int tipoClave; // Tipo de clave (pueden ser diferentes para Lotería y Tic-Tac-Toe)

class hashTable {

public:

        typedef struct {
        // Definir la estructura para la información asociada a la clave
        // Puede variar según el problema (por ejemplo, para Lotería o Tic-Tac-Toe)
        // Aquí se utiliza una estructura simple como ejemplo
            int valor;
        } tipoInfo;

    typedef struct {
        tipoClave clave;
        tipoInfo info;
        int ocupado; // Bandera para indicar si la ranura está ocupada o no
    } ranura;

    // Función hash genérica, puede variar para adaptarse al problema
    int h(tipoClave k) {
        // Implementación de la función hash
        // Puede ser una función específica para cada problema (Lotería, Tic-Tac-Toe)
        return k % TAMANO_TABLA; // Ejemplo simple de función hash
    }

    // Función para insertar en la tabla hash
    int hashInsert(ranura HT[], tipoClave k, tipoInfo I) {
        int indice = h(k);

        if (HT[indice].ocupado == 0) {
            HT[indice].clave = k;
            HT[indice].info = I;
            HT[indice].ocupado = 1;
            return 1; // Éxito al insertar
        }

        // La ranura está ocupada
        return 0;
    }

    // Función para buscar una clave en la tabla hash
    tipoInfo hashSearch(ranura HT[], tipoClave k) {
        int indice = h(k);

        if (HT[indice].ocupado == 1 && HT[indice].clave == k) {
            return HT[indice].info; // Clave encontrada, devuelve la información
        }

        // Clave no encontrada
        tipoInfo invalido;
        invalido.valor = -1; // Valor inválido, puede variar según la estructura de tipoInfo
        return invalido;
    }

    // Función para eliminar una clave de la tabla hash
    tipoInfo hashDelete(ranura HT[], tipoClave k) {
        int indice = h(k);

        if (HT[indice].ocupado == 1 && HT[indice].clave == k) {
            tipoInfo infoEliminada = HT[indice].info;
            // Marcamos la ranura como no ocupada (borrada)
            HT[indice].ocupado = 0;
            return infoEliminada; // Devolvemos la información asociada a la clave eliminada
        }

        // Clave no encontrada
        tipoInfo invalido;
        invalido.valor = -1; // Valor inválido, puede variar según la estructura de tipoInfo
        return invalido;
    }
};