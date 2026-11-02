#include<cstring>
#include<fstream>
#include<iostream>
using namespace std;

struct SExamenes{
    char CodUni[6];
    char CodFacu[6];
    char ApellidoNom[31];
     int NumLegajo;
     int Nota;
};

// funcion para grabar casos (NO ES PARTE DEL EJERCICIO)
void GrabarExamen(){
    SExamenes RExamen;
    
    strcpy(RExamen.CodUni, "U02");
    strcpy(RExamen.CodFacu,"F04"),
    strcpy(RExamen.ApellidoNom,"Valentina Espinoza");

    RExamen.NumLegajo = 4444444;
    RExamen.Nota = 10;

    ofstream examen("Examenes.dat",ios::binary|ios::app);
    examen.write((char * ) &RExamen, sizeof RExamen);

    examen.close();
}

// funcion para ver los casos, (NO ES PARTE DEL EJERCICIO)
void EmitirNotas(){
    SExamenes RExamenes;
    int CodUniAnt;
    int CodFacuAnt;
    int NumLegajoAnt;
    int ContadorLegajo;
    int ContadorAprobado;

    ifstream examenes("Examenes.dat",ios::binary);
    
    //el examenes.read mueve un puntero por cada registro que lee,
    //cuando termina el puntero esta al final, el .eof() lo que hace es ver
    //en que posicion esta ese puntero, si aun no esta en el final .eof()=false,
    //si llego al final .eof()=true
    examenes.read((char *) &RExamenes , sizeof RExamenes);
    
    while(!examenes.eof()){
        
        cout << "Universidad : " << RExamenes.CodUni << endl;
        cout << "       Facultad : " << RExamenes.CodFacu << endl;
        cout << "           Nro.Legajo: " << RExamenes.NumLegajo;
        cout << "   Nota: " << RExamenes.Nota << endl;

        examenes.read((char *) &RExamenes , sizeof RExamenes);    
    }
}

void EmitirReporte(){
    SExamenes RExamenes;
    char CodUniActual[6];
    char CodFacuActual[6];
    int ContadorLegajoFacu;
    int ContadorAprobadoFacu;
    int ContadorLegajoUni;
    int ContadorAprobadoUni;

    ifstream examenes("Examenes.dat",ios::binary);
    
    //el examenes.read mueve un puntero por cada registro que lee,
    //cuando termina el puntero esta al final, el .eof() lo que hace es ver
    //en que posicion esta ese puntero, si aun no esta en el final .eof()=false,
    //si llego al final .eof()=true
    examenes.read((char *) &RExamenes , sizeof RExamenes);
    
    // cuando trabajamos con Cortes de Control, lo mejor es hacer bloques while por cada
    // corte que deseamos hacer, en este caso, lo hacemos por Universidad, Facultad 
    // y los detalles, la forma que se usa para comparar es si es el fin de archivo
    // junto a si es la misma universidad y la misma facultad segun el nivel,
    // al final de cada bloque ponemos un trailer con los acumulados del bloque
    
    while(!examenes.eof()){
        // BLOQUE UNIVERSIDAD
        cout << "Universidad : " << RExamenes.CodUni << endl;
        strcpy(CodUniActual, RExamenes.CodUni);
        
        ContadorLegajoUni = 0;
        ContadorAprobadoUni = 0;
        
        while(!examenes.eof() && strcmp(CodUniActual, RExamenes.CodUni) == 0){
            //BLOQUE FACULTAD 
            cout << "       Facultad : " << RExamenes.CodFacu << endl;
            strcpy(CodFacuActual, RExamenes.CodFacu);

            ContadorLegajoFacu = 0;
            ContadorAprobadoFacu = 0;
            
            while(!examenes.eof() && strcmp(CodUniActual, RExamenes.CodUni) == 0
                                  && strcmp(CodFacuActual,RExamenes.CodFacu) == 0){
                //BLOQUE DETALLES
                cout << "           Nro.Legajo: " << RExamenes.NumLegajo;
                cout << "   Nota: " << RExamenes.Nota << endl;
                
                //ACUMULADORES
                ContadorLegajoFacu += 1;
                ContadorLegajoUni  += 1;
                if (RExamenes.Nota >= 4){
                    ContadorAprobadoFacu += 1;
                    ContadorAprobadoUni  += 1;
                }
                
                examenes.read((char *) &RExamenes , sizeof RExamenes);
            }
            //TRAILER DE FACULTAD
            cout << "       Cantidad Inscriptos: " << ContadorLegajoFacu << endl;
            cout << "       Cantidad Aprobados : " << ContadorAprobadoFacu << endl;
        }
        //TRAILER UNIVERSIDAD
        cout << "Cantidad Inscriptos: " << ContadorLegajoUni << endl;
        cout << "Cantidad Aprobados : " << ContadorAprobadoUni << endl;
    }
}
int main(){
    //GrabarExamen();  
    //EmitirNotas();
    EmitirReporte();
}

