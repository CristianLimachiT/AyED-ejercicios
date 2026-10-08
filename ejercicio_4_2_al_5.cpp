#include <windows.h>
#include<fstream>
#include<iostream>
using namespace std;
struct SDatos{
    short CodArticulo;
     char Descripcion[26];
    float PrecioUnitario;
};

struct SMayores{
    short CodArticulo;
    float PrecioUnitario;
};

// ejercicio 1
bool Ingresar_Datos(SDatos &RDatos){
    cout << "por favor ingrese datos" << endl;
    cout << "Codigo Articulo: ";
    cin >> RDatos.CodArticulo;
    if (RDatos.CodArticulo < 0 || RDatos.CodArticulo > 100){
        cout << "Valor de Articulo Incorrecto" << endl;
    return false;
    }

    cout << "Descripcion: ";
    cin.ignore(); // limpiamos buffer
    cin.getline(RDatos.Descripcion, 26); // es el cin para cadenas
    
    if(strlen(RDatos.Descripcion) == 0){
        cout << "Descripcion Incorrecta" << endl;
    return false;
    }
    cout << "Precio Unitario: ";
    cin >> RDatos.PrecioUnitario;
    if(RDatos.PrecioUnitario < 0){
        cout << "Precio Unitario Incorrecto" << endl;
    return false;
    }
    return true;
}

// ejercicio 1
void Grabar_Archivo(SDatos &RDatos){
    ofstream archivo("ARTICULO.DAT",ios::binary|ios::app);
    archivo.write((char * )&RDatos, sizeof RDatos);
    archivo.close();
    return;
}

// ejercicio 2
void Actualizar_Precios(){
    SDatos RDatos;
    float porcentaje;
    cout << "Ingrese el porcentaje para actualizar los precios";
    cin >> porcentaje;
    fstream archivo("ARTICULO.DAT",ios::binary|ios::in|ios::out);
    // esto esta en el manual
    while(archivo.read((char *) &RDatos, sizeof RDatos)){
        RDatos.PrecioUnitario = porcentaje / 100;
        archivo.seekg(-1 * sizeof RDatos,ios::cur); //mueve el puntero a previo
        archivo.write((const char *) &RDatos, sizeof RDatos); //rescribe el registro
    }
    archivo.close();
    return;
}

// ejercicio 3
void Precios_Mayores(){
    float ValorDiscrim;
    cout << "Ingrese el Valor Discriminador: ";
    cin >> ValorDiscrim;
    SDatos RDatos;
    SMayores RMayores;
    ifstream archivo("ARTICULO.DAT",ios::binary|ios::in);
    ofstream mayores("MAYORES.DAT",ios::binary|ios::out);
    while(archivo.read((char *) &RDatos, sizeof RDatos)){
        if(RDatos.PrecioUnitario > ValorDiscrim){
            RMayores.CodArticulo = RDatos.CodArticulo;
            RMayores.PrecioUnitario = RDatos.PrecioUnitario;
            mayores.write((char * )&RMayores, sizeof RMayores);
        }
    }
    archivo.close();
    mayores.close();
    return;
}

// ejercicio 4
void Cascaron(){
    SDatos RDatos;
    ofstream archivo("ARTREL.DAT",ios::binary|ios::app);

    for (int i = 0; i <= 100; i++){
        RDatos.CodArticulo = i;
        strcpy(RDatos.Descripcion," "); // copiamos en la cadena el ""
        RDatos.PrecioUnitario = 0;

        archivo.write((char * )&RDatos, sizeof RDatos);
    }
    archivo.close();
    return;
}

// ejercicio 5
void Alta(){
    short CodArticuloAux;    
    SDatos RDatos;

    cout << "Ingrese el codigo de articulo: ";
    cin  >> CodArticuloAux;

    ifstream archivo("ARTICULO.DAT",ios::binary|ios::in);

    while(archivo.read((char *) &RDatos, sizeof RDatos)){
        if (RDatos.CodArticulo == CodArticuloAux){
            cout << "ERROR - EL CODIGO DE ARTICULO YA EXISTE" << endl;
            Sleep(5000);
            return;
        }
    }
    
    archivo.close();
    RDatos.CodArticulo = CodArticuloAux;

    cout << "Ingrese la descripcion del articulo: ";
    cin.ignore(); // limpiamos buffer
    cin.getline(RDatos.Descripcion, 26); // es el cin para cadenas
    
    cout << "Ingrese el precio del artiuclo: ";
    cin  >> RDatos.PrecioUnitario;

    Grabar_Archivo(RDatos);
    return;
}

void Baja(){
    short CodArticuloAux;
    bool  CodArticuloExiste;
    SDatos RDatos;

    cout << "Ingrese el codigo de articulo"<< endl;
    cin  >> CodArticuloAux;

    ifstream archivo("ARTICULO.DAT",ios::binary|ios::in);

    while(archivo.read((char *) &RDatos, sizeof RDatos)){
        if (RDatos.CodArticulo == CodArticuloAux){
            CodArticuloExiste = true;
        }
    }
    archivo.close();

    if (CodArticuloExiste == false){
            cout << "ERROR - EL CODIGO DE ARTICULO NO EXISTE" << endl;
            Sleep(5000);
            return;
    }
    return;
}
void Modificacion(){
    short CodArticuloAux;
    bool  CodArticuloExiste;
    SDatos RDatos;

    cout << "Ingrese el codigo de articulo"<< endl;
    cin  >> CodArticuloAux;

    ifstream archivo("ARTICULO.DAT",ios::binary|ios::in);

    while(archivo.read((char *) &RDatos, sizeof RDatos)){
        if (RDatos.CodArticulo == CodArticuloAux){
            CodArticuloExiste = true;
        }
    }
    archivo.close();

    if (CodArticuloExiste == false){
            cout << "ERROR - EL CODIGO DE ARTICULO NO EXISTE" << endl;
            Sleep(5000);
            return;
    }
    return;
}

void Listar(){
    short CodArticuloAux; 
    SDatos RDatos;

    ifstream archivo("ARTICULO.DAT",ios::binary|ios::in);

    while(archivo.read((char *) &RDatos, sizeof RDatos)){
        cout << RDatos.CodArticulo << " | ";
        cout << RDatos.Descripcion << " | ";
        cout << RDatos.PrecioUnitario << endl;
    }
    archivo.close();

    return;
}

// ejercicio 5
void ProcesarABML(){
    short opcionabml;

    do{
        cout << "Seleccione una opcion del ABML" << endl;
        cout << "1 - Alta" << endl;
        cout << "2 - Baja" << endl;
        cout << "3 - Modificacion" << endl;
        cout << "4 - Listar" << endl;
        cout << "0 - Salir" << endl;
        cout << "opcion: ";
        cin  >> opcionabml;
        switch(opcionabml){
            case 0:
                break;
            case 1:
                Alta();
                break;
            case 2:
                Baja();
                break;
            case 3:
                Modificacion();
                break;
            case 4:
                Listar();
                break;
        }
    }while(opcionabml != 0);

    return;
}

int main(){
    short opcion;
    do{
        cout << "1 - Ingresar Datos" << endl;
        cout << "2 - Actualizar Precios con un Porcentaje" << endl;
        cout << "3 - Precios Mayores" << endl;
        cout << "4 - Cascaron" << endl;
        cout << "5 - Procesar ABML" << endl;
        cout << "0 - SALIR" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        switch(opcion){
            case 0:
                break;
            case 1:{
                SDatos RDatos;
                bool IngresarDatosOK = Ingresar_Datos(RDatos);
                if (IngresarDatosOK == true){
                    Grabar_Archivo(RDatos);
                }
                break;}
            case 2:
                Actualizar_Precios();
                break;
            case 3:
                Precios_Mayores();
                break;
            case 4:
                Cascaron();
                break;
            case 5:
                ProcesarABML();
                break;
        }
    }while(opcion != 0);
    return 0;
}
