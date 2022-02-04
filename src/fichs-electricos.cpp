#include "fichs-electricos.hpp"
#include <string>

/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-precios> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <precio-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «precio»,
 *       respectivamente, los datos sobre la fecha, hora y precio horario
 *       correspondientes a la línea que se ha extraído del flujo «f».
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
bool leerPrecioHorario(istream &f, Fecha &fecha, unsigned &hora, double &precio) {
    double precio_temp;
    string basura;
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');
    
    f >> precio_temp;
    precio_temp /= 1000;
    precio = precio_temp;

    f.get();
    f >> fecha.agno;
    f.get();
    f >> fecha.mes;
    f.get();
    f >> fecha.dia;
    f.get();
    f >> hora;
    getline(f, basura, '\n');

    return !f.eof();
}

/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-consumos> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <consumo-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «consumo»,
 *       respectivamente, los datos sobre la fecha, hora y consumo horario
 *       correspondientes a la línea que se ha extraído del flujo «f».
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
bool leerConsumoHorario(istream &f,
                        Fecha &fecha, unsigned &hora, double &consumo) {

    string basura;

    getline(f, basura, ';');

    f >> fecha.dia;
    f.get();

    f >> fecha.mes;
    f.get();

    f >> fecha.agno;
    f.get();

    f >> hora;
    hora -= 1;
    f.get();

    f >> consumo;

    getline(f, basura, '\n');

    return !f.eof();
}

/*
 * Pre:  «nombreFichero» es el nombre de un fichero externo que cumple con la
 *       sintaxis de la regla <fichero-precios> establecida en el enunciado;
 *       «mesInicial» y «mesFinal» están ambos entre «PRIMER_MES» y «ULTIMO_MES»
 *       y mesInicial < mesFinal.
 * Post: Ha copiado los datos de precios horarios correspondientes a fechas
 *       entre «mesInicial» y «mesFinal» presentes en «nombreFichero» en las
 *       componentes correspondientes a la hora del precio del campo «precios»
 *       en las primeras componentes del vector «registros», cuyos campos
 *       «fecha» se han actualizado y han quedado en orden cronológico (tal y
 *       como aparecían en el fichero). LOS DATOS DEL VECTOR CORRESPONDIENTE AL
 *       CAMPO «CONSUMO» NO SE HAN MODIFICADO.
 *       La función ha devuelto «true» si ha podido leer del fichero de nombre
 *       «nombreFichero» correctamente, y «false» en caso contrario.
 */
bool leerPrecios(const string nombreFichero,
                 const unsigned mesInicial, const unsigned mesFinal,
                 GastoDiario registros[]) {

    ifstream f;
    Fecha fecha, inicial;
    inicial.agno = 2021;
    inicial.dia = 1;
    inicial.mes = mesInicial;
    string basura;

    unsigned hora;
    double precio;

    f.open(nombreFichero);

    if (f.is_open()) {

        //Nos quitamos de en medio la cabecera
        getline(f, basura, '\n');
        
        while (!f.eof())
        {
            leerPrecioHorario(f, fecha, hora, precio); // leemos una línea

            if (fecha.mes >= mesInicial || fecha.mes <= mesFinal) // comprobamos si el mes se encuentra entre inicial y final ( y por tanto nos es de interés)
            {
                //Calculamos el índice del vector registros donde irán todos los datos del día.
                unsigned indice = diasTranscurridos(inicial, fecha);

                //Metemos los datos de las 24h de ese día
                for (unsigned i = 0; i < NUM_HORAS-1; i++)
                {
                    registros[indice].precios[hora] = precio;
                    leerPrecioHorario(f, fecha, hora, precio); // leemos la siguiente hora
                }

                registros[indice].precios[hora] = precio;
                
                
            }
            else { // si el mes no es de nuestro interés simplemente nos lo saltamos

                getline(f, basura, '\n');
            }   
        }

        return true;

    }
    else {
        return false;
    }
                     
}


/*
 * Pre:  «mesInicial» y «mesFinal» están ambos entre «PRIMER_MES» y «ULTIMO_MES»
 *       y mesInicial < mesFinal; si para cada mes entre «mesInicial» y
 *       «mesFinal» existe un fichero con nombre de la forma
 *       "datos/" + nombreCliente + "-2021-" + mes-con-dos-cifras + ".csv", este
 *       cumple con la sintaxis de la regla <fichero-consumos> establecida en el
 *       enunciado.
 * Post: Ha copiado los datos de precios horarios correspondientes a fechas 
 *       entre «mesInicial» y «mesFinal» presentes en los ficheros mencionados
 *       en la precondición en las componentes correspondientes a la hora del
 *       consumo del campo «consumo» en las primeras componentes del vector
 *       «registros». LOS DATOS DEL VECTOR CORRESPONDIENTE AL CAMPO «PRECIOS» NO
 *       SE HAN MODIFICADO.
 *       La función ha devuelto «true» si ha podido leer de todos los ficheros 
 *       referidos en la precondición correctamente, y «false» en caso contrario.
 */
bool leerConsumos(const string nombreCliente,
                  const unsigned mesInicial, const unsigned mesFinal,
                  GastoDiario registros[]) {

    for (unsigned i = mesInicial; i <= mesFinal; i++)
    {
        // Creamos el nombre del fichero
        unsigned mes = i;
        string nombreFichero;
        if (i < 10)
        {
            nombreFichero = RUTA_DATOS + nombreCliente + "-2021-0" + to_string(i) + ".csv"; 
        }
        else {
            nombreFichero = RUTA_DATOS + nombreCliente + "-2021-" + to_string(i) + ".csv";
        }

        ifstream f;

        f.open(nombreFichero);

        if (f.is_open())
        {   
            string basura;
            Fecha fecha, inicial;
            unsigned hora;
            double consumo;
            
            inicial.agno = 2021;
            inicial.dia = 1;
            inicial.mes=mesInicial;

            //Quitamos la cabecera
            getline(f, basura, '\n');

            while(!f.eof()) {
                
                //Leemos una línea del fichero de consumos
                leerConsumoHorario(f, fecha, hora, consumo);

                //Calculamos el índice del vector registros donde irán los datos de ese día
                unsigned indice = diasTranscurridos(inicial, fecha);

                //vamos metiendo las 24 horas
                for (unsigned i = 0; i < NUM_HORAS-1; i++)
                {
                    registros[indice].consumos[hora] = consumo;
                    leerConsumoHorario(f, fecha, hora, consumo); // leemos la siguiente hora
                }
                registros[indice].consumos[hora] = consumo;
                

            }


        }
        else {
            return false;
        }
        
        f.close();
        
    }
    
    return true;
}