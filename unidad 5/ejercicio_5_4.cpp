//ENUNCIADO:
//Se tiene un archivo de Gastos producidos en un año calendario, conteniendo: Importe
//(real), Mes (1..12) y Día (1..31), sin orden, el cual podrá repetirse un gasto para un
//mismo mes de un mismo día. Se requiere de un proceso que : Emita un listado de los
//gastos producidos en c/u. de los meses del año y ordenado por Día (acumulado).
//Además informar total por c/u. de los meses y el total anual.
//
//SOLUCION:
//el ejercicio debe contener las estructuras dinamicas, por lo tanto usamos listas dinamicas
//con nodos del archivo gastos. como sabemos, para listas desordenadas con multinivel podemos usar 
//listas colgadas o sublistas, que son listas dentro de otras listas
//podemos generar la lista Meses y dentro de la lista meses podemos generar la lista Dias
//
//

#include<iostream>
#include<fstream>
using namespace std;

//Sublista de Dias
struct SSubListaDias{
    short Dia;
    float Importe;
};

//Nodo de Dias
struct SNodoDia{
    SSubListaDias InfoDias;
    SNodoDia *NodoDiaSiguiente;
};

//Lista de Mes
struct SListaMes{
    short Mes;
    SNodoDia *PCabeceraSubDias; //puntero a la cabecera de la sublista de dias
};

//Nodo de Mes
struct SNodoMes{
    SListaMes InfoMes;
    SNodoMes *NodoMesSiguiente;
};

//registro para leer el archivo
struct SGastos{
    float Importe;
    short Mes;
    short Dia;
};

//usamos la funcion ExisteNodo para ver si el mes o dia que tenemos en el RGastos existe ya en la lista
//devolvemos un puntero del Nodo donde esta el nodo que buscamos, los parametros son 
// el campo RListaMes es solo el Nodo con el puntero del inicio de lista de meses, 
// el RNodoAnterior es el puntero al nodo del nodo anterior al que buscamos, este sirve para que el orden se contenga
// a pesar de que pongamos algo entre el RNodoAnterio y el RNodoActual, el campo Mes es simplemente el mes que buscamos
SNodoMes* ExisteNodo(SNodoMes *RListaMes, SNodoMes *&RNodoAnterior, short Mes ){
    SNodoMes *RNodoActual; //definimos un nodo que usaremos como el primer nodo de la lista de meses
    RNodoAnterior = NULL;  //dejamos el nodo anterior como null
    RNodoActual = RListaMes; //dejamos el nodo actual como el primero nodo de la lista de meses

    while(RNodoActual != NULL && Mes > RNodoActual -> InfoMes.Mes){
        RNodoAnterior = RNodoActual;   //si el Mes es mayor al mes del nodo actual movemos el nodo anterior como nodo actual
        RNodoActual = RNodoActual -> NodoMesSiguiente; // ponemos como nodo actual el nodo del mes siguiente, osea su encadenado
    }
    // si el nodo actual no es null y el infomes.mes del nodo actual es igual al mes que estamos buscanod
    if(RNodoActual != NULL && RNodoActual -> InfoMes.Mes == Mes){
        return RNodoActual;
    }
    else{
        return NULL;
    }
}

void ProcesarGasto(SGastos &RGastos, SNodoMes *&RListaMes){
//evaluamos primero si existe el nodo que contenga el mes del RGastos
//generamos el RNodoAnterior vacio ya que es un dato de salida
    SNodoMes *RNodoAnterior = NULL;
    SNodoMes *RNodoMes = ExisteNodo(RListaMes, RNodoAnterior, RGastos.Mes);
    
    //evaluamos si el nodo fue encontrado en la lista de meses
    if(RNodoMes == NULL){
        RNodoMes = new SNodoMes; //si no existe generamos el nuevo nodo
        RNodoMes->InfoMes.Mes = RGastos.Mes;   // dentro del nuevo nodo en el InfoMes.Mes guardamos el Mes
        RNodoMes->InfoMes.PCabeceraSubDias = NULL;  // para el nuevo mes, la lista de dias arranca vacia, por eso va NULL
        
        // 4. Lo enganchamos en la lista usando pAntMes
        if (RNodoAnterior == NULL) {
            // Caso A: Va al principio de todo (la lista estaba vacía o es menor al primer mes)
            RNodoMes->NodoMesSiguiente = RListaMes;
            RListaMes = RNodoMes; // La cabeza ahora es este nuevo nodo
        } else {
            // Caso B: Va en el medio o al final (detrás de pAntMes)
            RNodoMes->NodoMesSiguiente = RNodoAnterior->NodoMesSiguiente;
            RNodoAnterior->NodoMesSiguiente = RNodoMes;
        }
    } 

}


void AbrirGastos(ifstream &ArchivoGastos){
    ArchivoGastos.open("Gastos.dat",ios::binary|ios::in);
    return;
}

void LeerGastos(ifstream &ArchivoGastos, SGastos &RGastos, SNodoMes *RListaMes){
    ArchivoGastos.read((char *)&RGastos, sizeof RGastos);

    while(ArchivoGastos.eof() != true){
        ProcesarGasto(RGastos,RListaMes);
        ArchivoGastos.read((char *)&RGastos, sizeof RGastos);
    }

    return;
} 

int main(){
    ifstream ArchivoGastos;
    AbrirGastos(ArchivoGastos);
    
    //creamos el puntero para la cabecera de la lista mes
    SNodoMes *RListaMes = NULL;
    SGastos RGastos;
    LeerGastos(ArchivoGastos,RGastos,RListaMes);
    
    //EmitirListado();
    //CerrarGastos();

    

    return 0;
    

}
