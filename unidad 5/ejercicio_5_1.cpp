#include <iostream>
#include <fstream>
using namespace std;

struct SGastos{
    float Importe;
    short Mes;
};

//definimos un nodo donde esta el dato actual, y el nodo anterior
struct SNodo{
    SGastos info;
    SNodo *anterior;
};

//Como en nuestro stack se guardan los SGasto, lo ponemos como dato
void push(SNodo *&Stack, SGastos &RGastos){
    SNodo *PNodo;
	
	//generamos un nuevo nodo 
    PNodo = new SNodo;
    //asignamos el valor al nodo actual 
    PNodo -> info = RGastos;
    //asignamos el nodo anterior el stack actual
	PNodo -> anterior = Stack;
	//actualizamos el stack con el nodo actual
	Stack = PNodo;
    return;
}

// toma el stack y devuelve el ultimo elemento en el RGastos
// y elimina este ultimo nodo del stack
void pop(SNodo *&Stack, SGastos &RGastos){
    SNodo *PNodo;
    
    //asignamos el nodo actual a un puntero temporal
    PNodo = Stack;
    //asignamos el valor del nodo actual al RGastos de salida
    RGastos = Stack -> info;
    //actualizamos el stack con el nodo anterior
    Stack = Stack -> anterior;
    //liberamos la memoria del nodo actual
    delete PNodo;
    return;
}
void AbrirGastos(ifstream &Gastos){
    Gastos.open("Gastos.txt",ios::in);
    return;
}
 
void LeerGastos(ifstream &Gastos, SNodo *&Stack){
	SGastos RGastos;
	char buffer[13];
    
    Gastos.getline(buffer,13);
    while (Gastos.eof() == false){
        char CharImporte[11];
        
        for(int i=0; i < 11; i++){
            CharImporte[i] = buffer[i];    
        }
		CharImporte[11] = '\0';
        
        char CharMes[3];

        for(int j=0; j < 3; j++){
            CharMes[j] = buffer[j+10];
        }
        
        CharMes[3] = '\0';

        RGastos.Importe = stof(CharImporte);
        RGastos.Mes = stoi(CharMes);

        //Hacemos Push en la Pila por cada Gasto, apilandose al final
		push(Stack, RGastos);

	    Gastos.getline(buffer,26);
    }
    return;
}

void EmitirListado(SNodo *&Stack){
    SGastos RGastos;
    //podemos hacer simplemente while(Stack), ya que mientras haya algo no va a ser nullptr, 
    while(Stack != nullptr){
        pop(Stack,RGastos);
        cout << RGastos.Importe << RGastos.Mes << endl;
    }
    return;
}

void CerrarGastos(ifstream &Gastos){
    Gastos.close();
}

int main(){
    ifstream Gastos;
    AbrirGastos(Gastos);
    
    //creamos el puntero al stack con estructura de SNodo con valor
    //NULL para iniciarlizarlo
    SNodo *Stack = NULL;
    LeerGastos(Gastos,Stack);
    
    EmitirListado(Stack);
    CerrarGastos(Gastos);
    return 0;
}

