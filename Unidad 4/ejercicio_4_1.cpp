#include <fstream>
#include <iostream>
using namespace std;

struct SArticulos{
    short CodArticulo;
     char Descripcion[20];
    float PrecioU;
};
// recibe por parametro el archivo y la estructura
bool GrabarArchivo(ofstream &articulo, SArticulos &RArticulo){
    articulo.write((char *)&RArticulo, sizeof(RArticulo));
    return articulo.good();
}

void LeerArchivo(ifstream &archivo, SArticulos &RArticulo){
    // el archivo.read() devuelve true si lee segun el registro RArticulo
    // devuelve false si no encuentra nada mas, esta es la forma de leer en un binario
    while(archivo.read((char *)&RArticulo, sizeof(RArticulo))){
        cout << RArticulo.CodArticulo << " | ";
        cout << RArticulo.Descripcion << " | ";
        cout << RArticulo.PrecioU << endl;

    }
    return;
}
void Ingresar_Datos(){
    short Continuar;
    bool ArchivoOK = true;
    
    SArticulos RArticulo;
    
    ofstream articulo("ARTICULO.dat",ios::binary);

    do{
        cout << "ingrese CodArticulo: ";
        cin  >> RArticulo.CodArticulo;

        cout << "Ingrese Descripcion: ";
        cin.ignore();
        cin.getline(RArticulo.Descripcion,20);

        cout << "Ingrese Precio Unitario: ";
        cin  >> RArticulo.PrecioU;

        ArchivoOK = GrabarArchivo(articulo, RArticulo);
        
        cout << "Continuar? (1 = SI, 0 = NO): ";
        cin >> Continuar;

    }while(ArchivoOK && Continuar == 1);

    return;
}

void Ingresar_Porcentaje(int &porcenaje){
    int porcentaje; 
    cout << "ingrese porcentaje para actualizar precios: ";
    cin  >> porcentaje;
    return;
}

int main(){
    short menu;
    bool salir = false;

    do{
        cout << "¿Que deseas hacer?" << endl;
        cout << "1 - Ingresar Datos"<< endl;
        cout << "2 - Leer Datos"<< endl;
        cout << "3 - Ingresar Porcentaje" << endl;
        cout << "0 - Salir"<< endl;
        cin  >> menu;

        switch (menu){
            case 1: 
                Ingresar_Datos();
                break;
            case 2:{
                SArticulos RArticulo;
                ifstream archivo("ARTICULO.dat",ios::binary);
                LeerArchivo(archivo, RArticulo);
                break;}
            case 3:{
                int porcentaje;
                Ingresar_Porcentaje(porcentaje);
                cout << porcentaje;
                break;}
            case 0:
                salir = true;
                break;
        }
    }while(salir == false);

    return 0;
}
