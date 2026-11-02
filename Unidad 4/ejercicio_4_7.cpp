//proceso modelo para el apareo por HIGH VALUE de dos archivos, procesador de ABM

#include<fstream>
#include<iostream>
using namespace std;
#include<cstring>

#define HIGH_VALUE 10000

struct SMaestro{
     int Clave;
    char Descripcion[21];
};

struct SNovedades{
     int Clave;
    char Descripcion[21];
    char CodMov[2];
};

struct SErrores{
    int Clave;
   char DescError[41];
};

// La idea es usar el algoritmo de HIGH VALUE, que consisten en leer crear el nuevo archivo maestro
// sin necesidad de evaluar con eof(), ya que puede ocurrir que el mestro y el novedades llegue a su fin
// pero necesitamos que siga corriendo la lectura apesar de esto, por lo tanto el HIGH_VALUE nos sirve para seguir
// leyendo asignandole a la clave del archivo finalizado el HIGH_VALUE, entonces pasaria a leer solo el archivo que
// no termino, cuando los dos sean HIGH_VALUE se termina el proceso

void EvaluarIguales(SMaestro &RMaestro, SNovedades &RNovedades, ofstream &MaestroSalida
                    ,ifstream &Maestro, ifstream &Novedades){
    if (strcmp(RNovedades.CodMov,"A") == 0){
        //grabamos en Errores este caso ya que se quiere dar de alta clave existente
        SErrores RErrores;

        RErrores.Clave = RNovedades.Clave;
        strcpy(RErrores.DescError, "ALTA EN CLAVE EXISTENTE");

        ofstream Errores("Errores.dat",ios::binary|ios::app);
        Errores.write((char *) &RErrores, sizeof RErrores);
        Errores.close();
    }
    else{
        //es una Modificacion grabamos nuevo mastro con campos actualizados
        strcpy(RMaestro.Descripcion, RNovedades.Descripcion);
        MaestroSalida.write((char * )&RMaestro, sizeof RMaestro);
    }

    //se leen los dos archivos ya que avanzan las dos lecturas
    Maestro.read((char *) &RMaestro, sizeof RMaestro);
    if (Maestro.eof() == true){
        RMaestro.Clave = HIGH_VALUE;
    }
    
    Novedades.read((char *) &RNovedades, sizeof RNovedades);
    if (Novedades.eof() == true){
        RNovedades.Clave = HIGH_VALUE;
    }

}

void EvaluarMayor(SMaestro &RMaestro, SNovedades &RNovedades,ofstream &MaestroSalida
                  ,ifstream &Maestro, ifstream &Novedades){
    //Clave Maestro > clave Novedades, Clave de la novedad no existe en el maestro
    //tiene que ser A, porque si es B o M, no se puede modif o bajar algo que no esta
    if((strcmp(RNovedades.CodMov,"A") == 0)){
        //es una Modificacion grabamos nuevo mastro con campos actualizados
        RMaestro.Clave = RNovedades.Clave;
        strcpy(RMaestro.Descripcion, RNovedades.Descripcion);
        
        MaestroSalida.write((char * )&RMaestro, sizeof RMaestro);
    }
    else{
        SErrores RErrores;

        RErrores.Clave = RNovedades.Clave;
        strcpy(RErrores.DescError, "MOD/BAJA EN CLAVE EXISTENTE");

        ofstream Errores("Errores.dat",ios::binary|ios::app);
        Errores.write((char *) &RErrores, sizeof RErrores);
        Errores.close();
    }
    // se avanza solo el novedades ya que es el unico que se procesa
    Novedades.read((char *) &RNovedades, sizeof RNovedades);
    if (Novedades.eof() == true){
        RNovedades.Clave = HIGH_VALUE;
    }

}

void EvaluarMenor(SMaestro &RMaestro, SNovedades &RNovedades, ofstream &MaestroSalida
                  ,ifstream &Maestro, ifstream &Novedades){
// Clave Maestro < Clave Novedad, significa que el maestro tiene info que el Novedad no
// por lo tanto el maestro esta al dia
    MaestroSalida.write((char * )&RMaestro, sizeof RMaestro);
    
    // se avanza el Maestro ya que es el unico que se lee
    Maestro.read((char *) &RMaestro, sizeof RMaestro);
    if (Maestro.eof() == true){
        RMaestro.Clave = HIGH_VALUE;
    }

}

void Procesos(){
    SMaestro RMaestro;
    SNovedades RNovedades;
     
    ifstream Maestro("Maestro.dat",ios::binary);
    ifstream Novedades("Novedades.dat",ios::binary);
    ofstream MaestroSalida("MaestroSalida.dat",ios::binary|ios::app);


    Maestro.read((char *) &RMaestro, sizeof RMaestro);
     if (Maestro.eof() == true){
        RMaestro.Clave = HIGH_VALUE;
    }
    
    Novedades.read((char *) &RNovedades, sizeof RNovedades);
    if (Novedades.eof() == true){
        RNovedades.Clave = HIGH_VALUE;
    }

    while(RMaestro.Clave != HIGH_VALUE && RNovedades.Clave != HIGH_VALUE){
        int opcion; 

        if (RMaestro.Clave == RNovedades.Clave){
            opcion = 0;
        }
        else if(RMaestro.Clave < RNovedades.Clave){
            opcion = -1;
        }
        else if(RMaestro.Clave > RNovedades.Clave){
            opcion = 1;
        }

        switch (opcion){
            case 0:
                EvaluarIguales(RMaestro,RNovedades,MaestroSalida,Maestro,Novedades);
                break;
            case 1:
                EvaluarMayor(RMaestro,RNovedades,MaestroSalida,Maestro,Novedades);
                break;
            case -1:
                EvaluarMenor(RMaestro,RNovedades,MaestroSalida,Maestro,Novedades);
                break;
        }
    }
}
int main(){
    Procesos();
    return 0;
}
