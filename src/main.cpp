/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: ¡¡¡PONED AQUÍ VUESTROS NOMBRES!!!
 * Ultima revisión: ¡¡¡!!!
 * Resumen: ¡¡¡!!!
 * Nota: El código de este programa está repartido en varios módulos.
 *       Para compilarlo, hay que ejecutar el comando
 *           make all
 *       o, en Windows,
 *           mingw32-make all
 *       o ejecutar la tarea "Compilar «electricidad»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/electricidad
 *       o, en Windows,
 *           bin\electricidad.exe
 *       o ejecutar la tarea "Ejecutar «electricidad»" de VSC.
\******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
#include "vector-gastos.hpp"
#include "tarifas-comerciales.hpp"
using namespace std;


/*
 * Pre:  «f» es «cout» o un flujo de la clase «ofstream» asociado con un fichero
 *       externo abierto para escritura. Las «numRegs» primeras componentes
 *       del vector «regDiarios» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: Ha escrito en el flujo «f» el informe sobre consumo eléctrico indicado
 *       en el enunciado de este trabajo.
 */
void escribirInforme(ostream& f,
                     const GastoDiario regDiarios[], const unsigned numRegs,
                     const string nombreCliente, 
                     const unsigned mesInicial, const unsigned mesFinal) {

    f << "\nINFORME DEL CLIENTE \"" << nombreCliente << "\" ENTRE LOS MESES " << mesInicial << " Y " << mesFinal << " DE 2021" << endl;
    f << "-----------------------------------------------------------------------------" << endl;

    
     
}

void preguntarDatos(string& nombreCliente, unsigned& mesInicial, unsigned& mesFinal, string& nombreFichero) {

    cout << "Escriba el nombre de cliente: ";
    cin >> nombreCliente;
    cout << "Escriba el mes inicial y el final: ";
    cin >> mesInicial >> mesFinal;

    cout << "Escriba el nombre del fichero del informe";
    cout << "\n(presione solo ENTRAR para escribirlo en la pantalla): ";
    cin.get();

}



/*
 * ¡ESCRIBID LA ESPECIFICACIÓN DE ESTA FUNCIÓN!
 */
int main() {

    string nombreCliente, nombreFichero, nombreFicheroPrecios;
    Fecha dia;
    GastoDiario regDiarios[10000];
    double precioMedioMinimo;
    unsigned mesInicial, mesFinal;
    nombreFicheroPrecios = "datos/tarifas-2021-ene-nov.csv";

    preguntarDatos(nombreCliente, mesInicial, mesFinal, nombreFichero);

    leerConsumos(nombreCliente, mesInicial, mesFinal, regDiarios);
    leerPrecios(nombreFicheroPrecios, mesInicial, mesFinal, regDiarios);

    diaMasBarato(regDiarios, 20, dia, precioMedioMinimo);

    cout << dia.dia << ", " << precioMedioMinimo << endl;

    return 0;
}