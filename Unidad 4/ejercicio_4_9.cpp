// el ejercicio consisten en grabar en una matriz ordenada un campo, en este caso, gasto
// el cual se acumula. la gracia de esto es usar el HASHING, que nos permite grabar sin necesidad
// de ordenar o de recorrer una estructura
// luego se imprime el reporte con un for anidado, ya que recorre por mes y por cada mes el dia

#include<fstream>
#include<iostream>
using namespace std;

//hacemos un typedef para los nombres de los meses
typedef char str15[16];

struct SGastos{
  short Dia;
  short Mes;
  float Gasto;
};

void AbrirGastos(ifstream &Gastos){
    Gastos.open("Gastos.dat",ios::binary| ios::in);
    return;
}

void LeerGastos(ifstream &Gastos, SGastos &RGastos, long MatrizGastos[13][32]){
    Gastos.read((char *) &RGastos, sizeof RGastos);

    while(Gastos.eof() == false){
        MatrizGastos[RGastos.Dia][RGastos.Mes] += RGastos.Gasto;
        Gastos.read((char *) &RGastos, sizeof RGastos);
    }
}

void EmitirGastos(long MatrizGastos[13][32], str15 Meses[13]){
    cout << "Listado de Gastos ordenado por Mes y Dia Acumulado" << endl;
    for(short i = 0; i <= 12; i++){
        cout << "Mes: " << Meses[i] << endl;
        for(short j = 0; j <= 32; j++){
           if (MatrizGastos[i][j] > 0){   
               cout << "        dia: " << j 
                    << "importe acumulado: " << MatrizGastos[i][j]<< endl;
           }
        }
    }
}

void CerrarGastos(ifstream &Gastos){
    Gastos.close();
    return;
}

// funcion para grabar registros
void GrabarRegistro(){
    ofstream Gastos("Gastos.dat",ios::binary| ios::app);

    SGastos RGastos;

    RGastos.Dia = 7;
    RGastos.Mes = 7;
    RGastos.Gasto = 7777;

    Gastos.write((char * ) &RGastos, sizeof RGastos);

    Gastos.close();
}
int main(){
    ifstream Gastos;
    AbrirGastos(Gastos);
    
    //* Generamos Matriz para hacer le hashing
    //* el {0} pone toda la matriz en cero
    long MatrizGastos[13][32] = {0};
    SGastos RGastos;
    LeerGastos(Gastos, RGastos, MatrizGastos);

    str15 Meses[13] = {
    "Enero", "Febrero", "Marzo","Abril","Mayo","Junio","Julio",
    "Agosto","Septiembre","Octubre", "Novimiembre" ,"Dicimiebre"
    };

    //GrabarRegistro();
    EmitirGastos(MatrizGastos,Meses);
    CerrarGastos(Gastos);
    return 0;
}
