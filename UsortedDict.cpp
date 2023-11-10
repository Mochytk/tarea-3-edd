#include <typeinfo>

template <class tipoClave, class tipoInfo> class UnsortedDict
{
private:
    const size_t C1 = 2, C2 = 1, C3 = 1;    //  Constante de funcionSonda
    const int8_t USED = 0, EMPTY = -1, FREE = -2;   //  Constante de estado
    size_t HTSize = 32; //  Tamanio de HT

    struct Hash
    {
        tipoClave key;  //  Clave del Registro
        tipoInfo data;  //  Dato del registro
        int8_t state = -1;  //  Estado
    };

    Hash * HashTable = nullptr; //  TablaHash (HT)
    size_t tamanio;     //  cantidad de claves en la HT
    float factorCarga;  //  Factor de carga

    /**
     * size_t funcionHashStringType(tipoClave key)
     * ***
     * Funcion de Hashing para strings types
     * Basado en un Multiplicative hash fuction
     * O(len(key))
     * ***
     * Inputs:
     *      tipoClave key   :   clave a hashear
     * ***
     * Return:
     *      size_t  :   Posicion resultante del registro relacionado a la clave
    **/
    size_t funcionHashStringType(tipoClave key){
        size_t len = key.length();  //  Tamanio de key
        const size_t a = 33;
        const size_t INITIAL_VALUE = 5381;
        size_t hash = INITIAL_VALUE;            //  Hash Resultante

        for (size_t i = 0; i < len; i++)
        {
            hash = ((hash*a) + key[i]);
        }
        
        return hash % HTSize;
    }

    /**
     * size_t funcionSonda(size_t pos)
     * ***
     * Funcion de sondeo para buscar posiciones siguentes como metodo de Hashing Cerrado
     * tipo Cuadrático
     * O(1)
     * ***
     * Inputs:
     *      size_t i   :    posicion a calcular el salto
     * ***
     * Returns:
     *      size_t  :    resultado del salto
    **/
    size_t funcionSonda(size_t i){
        return C1*i*i + C2*i + C3;
    }

    /**
     * tipoInfo * HashInsert(Hash HT[], tipoClave key, tipoInfo data)
     * ***
     * Algoritmo de insertado en la HashTable
     * O(1)
     * ***
     * Inputs:
     *      Hash HT[]   :   Direccion de la tabla de registro
     *      tipoClave Key   :   Clave a intertar
     *      tipoInfo data   :   Dato a insertar
     * ***
     * Return:
     *      tipoInfo *  :   Direccion del dato insertado. Si no exitoso, retorna .end()
    **/
    tipoInfo * HashInsert(Hash HT[], tipoClave key, tipoInfo data){
        size_t inicio;

        if (typeid(tipoClave) == typeid(std::string))   // Pruebas de Templates
        {
            inicio = funcionHashStringType(key);
        }

        size_t pos = inicio;

        for (size_t i = 1; (HT[pos].state != EMPTY && HT[pos].state != FREE) && HT[pos].key != key; i++)
        {            
            pos = (inicio + funcionSonda(i)) % HTSize;
        }

        if (HT[pos].key == key && HT[pos].state == USED)
        {
            return end();   //  Insercion no exitosa, clave repetida

        } else {
            HT[pos].key = key;
            HT[pos].data = data;
            HT[pos].state = USED;
            tamanio++;

            calcularfactor();

            if(factorCarga >= 0.7)
            {
                resize();
                return HashSearch(HashTable, key);
            }

            return &(HT[pos].data);   //  Insercion exitosa
        }
    }

    /**
     * tipoInfo * HashErrase(Hash HT[], tipoClave key)
     * ***
     * Algoritmo de Borrado en la HashTable
     * O(1)
     * ***
     * Inputs:
     *      Hash HT[]   :   Direccion de la tabla de registros
     *      tipoClave key   :   Clave a borrar
     * ***
     * Return:
     *      tipoInfo *  :   Direccion del dato borrado. Si no exitoso, retorna .end()
    **/
    tipoInfo * HashErrase(Hash HT[], tipoClave key){
        size_t inicio;

        if (typeid(tipoClave) == typeid(std::string))
        {
            inicio = funcionHashStringType(key);
        }

        size_t pos = inicio;

        for (size_t i = 1; HT[pos].state != EMPTY && HT[pos].key != key; i++)
        {
            pos = (inicio + funcionSonda(i)) % HTSize;
        }

        if (HT[pos].key == key && HT[pos].state == USED)
        {
            HT[pos].key.clear();    //  Borado de la llave
            HT[pos].state = FREE;   //  Si FREE inaccesible
            tamanio--;

            calcularfactor();

            return &(HT[pos].data);   //  Borrado Exitoso

        } else {
            return end();   //  Borrado no exitoso, no existe clave
        }
    }

    /**
     * tipoInfo * HashSearch(Hash HT[], tipoClave key)
     * ***
     * Algoritmo de Busqueda en la HashTable
     * O(1)
     * ***
     * Inputs:
     *      Hash HT[]   :   Direcciom de la tabla de registro
     *      tipoClave key   :   Clave a buscar
     * ***
     * Return:
     *      tipoInfo *  :   Direccion del dato asociado a la clave, Si no existe, retorna .end()
    **/
    tipoInfo * HashSearch(Hash HT[], tipoClave key){
        size_t inicio;

        if (typeid(tipoClave) == typeid(std::string))
        {
            inicio = funcionHashStringType(key);
        }

        size_t pos = inicio;

        for (size_t i = 1; HT[pos].state != EMPTY && HT[pos].key != key; i++)
        {
            pos = (inicio + funcionSonda(i)) % HTSize;
        }

        if (HT[pos].key == key && HT[pos].state == USED)
        {
            return &(HT[pos].data);     //  Caso exitoso

        } else {
            return end();       //      Clave no encontrada, no exito
        }
    }

    /**
     * tipoInfo * HashReplace(Hash HT[], tipoClave key, tipoInfo data)
     * ***
     * Algoritmo de busqueda y remplazo en la HashTable
     * O(1)
     * ***
     * Inputs
     *      Hash HT[]   :    Direccion de la tabla de registros
     *      tipoClave key    :   Clave a buscar
     *      tipoInfo data    :   Valor a remplazar en la clave asociada
     * ***
     * Return
     *      tipoInfo * :    Direccion del valor remplazado asociado a la clave. Si no existe, retorna .end()
    **/
    tipoInfo * HashReplace(Hash HT[], tipoClave key, tipoInfo data){
        size_t inicio;

        if (typeid(tipoClave) == typeid(std::string))
        {
            inicio = funcionHashStringType(key);
        }

        size_t pos = inicio;

        for (size_t i = 1; HT[pos].state != EMPTY && HT[pos].key != key; i++)
        {
            pos = (inicio + funcionSonda(i)) % HTSize;
        }

        if (HT[pos].key == key && HT[pos].state == USED)
        {
            HT[pos].data = data;    //  Remplazo de data
            return &(HT[pos].data); //  Caso exitoso

        } else {
            return end();   //  No exitoso, no exite la llave
        }
    }

    /**
     * void calcularfactor()
     * ***
     * Calcula el factor de carga de la HT.
    **/
    void calcularfactor(){
        factorCarga = (double) tamanio / (double) HTSize;
    }

    /**
     * void resize()
     * ***
     * Realiza el aumento de tamanio de la HT cuando factoCarga >= 0.7
     * Duplica el tamanio.
     * O(n)
    **/
    void resize(){
        size_t prevHTSize = HTSize;     //  Guarda la tabla a cambiar
        Hash * prevHashTable = HashTable;

        HTSize = HTSize * 2;
        HashTable = new Hash[HTSize +1];    //  Reserva +1 para .end()
        tamanio = 0;

        //  Rehashin O(n)
        for (size_t i = 0; i < prevHTSize; i++)
        {
            if(prevHashTable[i].state != USED) continue;
            HashInsert(HashTable, prevHashTable[i].key, prevHashTable[i].data);
        }
        
        delete[] prevHashTable;
    }

public:
    UnsortedDict();

    tipoInfo * insert(tipoClave key, tipoInfo data);

    tipoInfo * remove(tipoClave key);

    tipoInfo * get(tipoClave key);

    tipoInfo * replace(tipoClave key, tipoInfo data);

    tipoInfo * end();

    ~UnsortedDict();
};

/**
 * UnsortedDict<tipoClave, tipoInfo>::UnsortedDict()
 * ***
 * Contructor
 * Inicializa el diccionario vacio
 * O(1)
*/
template <class tipoClave, class tipoInfo> UnsortedDict<tipoClave, tipoInfo>::UnsortedDict()
{
    HashTable = new Hash[HTSize+1];     //  Reserva +1 para .end()
    tamanio = 0;
    factorCarga = 0;
}

/**
 * tipoInfo * UnsortedDict<tipoClave, tipoInfo>::insert(tipoClave key, tipoInfo data)
 * ***
 * Insertar un par <Clave, Dato> al diccionario
 * Si ya exite la clave, retorna .end()
 * O(1)
 * ***
 * Inputs:
 *      tipoClave key   :   Clave asociada al registro a insertar
 *      tipoInfo data   :   Valor asociado a la Clave a insertar
 * ***
 * Return:
 *      tipoClave *     :   Direccion del valor Insertado, Si no insertado, retorna .end()
**/
template <class tipoClave, class tipoInfo> tipoInfo * UnsortedDict<tipoClave, tipoInfo>::insert(tipoClave key, tipoInfo data)
{
    return HashInsert(HashTable, key, data);
}

/**
 * tipoInfo * UnsortedDict<tipoClave, tipoInfo>::remove(tipoClave key)
 * ***
 * Remover una clave del diccionario
 * Si no existe la clave, retorna .end()
 * O(1)
 * ***
 * Inputs:
 *      tipoClave key   :   Clave asociada al registro a remover
 * ***
 * Return:
 *      tipoClave *     :   Direccion del valor asociado a la clave eliminada. Si no removido, retorna .end()
**/
template <class tipoClave, class tipoInfo> tipoInfo * UnsortedDict<tipoClave, tipoInfo>::remove(tipoClave key)
{
    return HashErrase(HashTable, key);
}

/**
 * tipoInfo * UnsortedDict<tipoClave, tipoInfo>::get(tipoClave key)
 * ***
 * Obtine el valor asociado a la llave del registro
 * Si no exite la clave, retorna .end()
 * O(1)
 * ***
 * Inputs:
 *      tipoClave key   :   Clave asociada al registro a obtener
 * ***
 * Return:
 *      tipoClave *     :   Direccion del valor asociado a la clave. Si no exite, retorna .end()
**/
template <class tipoClave, class tipoInfo> tipoInfo * UnsortedDict<tipoClave, tipoInfo>::get(tipoClave key)
{
    return HashSearch(HashTable, key);
}

/**
 * tipoInfo * UnsortedDict<tipoClave, tipoInfo>::replace(tipoClave key, tipoInfo data)
 * ***
 * Remplaza el valor asociado a la clave en el registro por uno nuevo
 * Si no exite la clave, retorna .end()
 * O(1)
 * ***
 * Inputs:
 *      tipoClave key   :   Clave asociada al registro del valor a remplazar
 *      tipoInfo data   :   Nuevo valor a remplazar asociado a la clave
 * ***
 * Return:
 *      tipoClave *     :   Direccion del valor asociado a la clave. Si no exite, retorna .end()
**/
template <class tipoClave, class tipoInfo> tipoInfo * UnsortedDict<tipoClave, tipoInfo>::replace(tipoClave key, tipoInfo data)
{
    return HashReplace(HashTable, key, data);
}

/**
 * tipoInfo * UnsortedDict<tipoClave, tipoInfo>::end()
 * ***
 * Obtiene una direccion de tipoInfo reservado para comparar retornos de otras funciones del dicionario
 * Cambia cuando la tabla hash aumneta de tamanio
 * O(1)
 * ***
 * Return:
 *      tipoClave *     :   Direccion de un tipoClave para realizar comparaciones
**/
template <class tipoClave, class tipoInfo> tipoInfo * UnsortedDict<tipoClave, tipoInfo>::end()
{
    return &(HashTable[HTSize].data);
}

/**
 * UnsortedDict<tipoClave, tipoInfo>::~UnsortedDict()
 * ***
 * Destructor del diccionario
 * O(1)
**/
template <class tipoClave, class tipoInfo> UnsortedDict<tipoClave, tipoInfo>::~UnsortedDict()
{
    delete[] HashTable;
    HTSize = 0;
    tamanio =  0;
}
