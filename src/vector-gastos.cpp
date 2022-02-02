#include "vector-gastos.hpp"
#include "gasto-diario.hpp"
#include <iostream>

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios horarios de energía eléctrica.
 * Post: Asigna al parámetro «dia» el día en el que se registró el menor precio
 *       diario promedio de entre las primeras «numRegs» componentes del vector
 *       «regsDiarios» y al parámetro «precioMaximo», el valor de ese precio
 *       promedio diario mínimo.
 */
void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs,
                  Fecha &dia, double &precioMedioMinimo) {
                      
    //Hallemos qué día tuvo el coste diario más bajo

    double min = costeMedio(regsDiarios[0]);

    for (unsigned i = 1; i < numRegs; i++)
    {
        if (costeMedio(regsDiarios[i]) < min) {
            min = costeMedio(regsDiarios[i]);
            dia.dia = i;
        }
    }
    
    precioMedioMinimo = min;
}

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios horarios de energía eléctrica.
 * Post: Asigna al parámetro «dia» el día en el que se registró el mayor precio
 *       horario de entre las primeras «numRegs» componentes del vector
 *       «regsDiarios»; al parámetro «hora», la hora de ese día en la que se
 *       registró ese mayor precio horario y al parámetro «precioMaximo», el
 *       valor de ese precio máximo.
 */
void horaMasCara(const GastoDiario regsDiarios[], const unsigned numRegs,
                 Fecha &dia, unsigned &hora, double &precioMaximo) {

    //Hallemos qué día tuvo la hora más cara

    int horaa = horaMasCara(regsDiarios[0]);
    double max = regsDiarios[0].precios[horaa];

    for (unsigned i = 1; i < numRegs; i++)
    {
        horaa = horaMasCara(regsDiarios[i]);

        if (regsDiarios[i].precios[horaa] > max) {
            max = regsDiarios[i].precios[horaa];
            hora = horaa;
            dia.dia = i;
        }
    }
    
    precioMaximo = max;
}

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios y consumo horarios de energía eléctrica.
 * Post: Devuelve el coste en euros de la energía eléctrica consumida según los
 *       datos de las primeras «numRegs» componentes del vector «regsDiarios».
 */
double costeTerminoVariable(const GastoDiario regsDiarios[],
                            const unsigned numRegs) {
                                
    // Hallamos el coste eléctrico de cada día y los sumamos

    double sum = 0;

    for (unsigned i = 0; i < numRegs; i++)
    {
        sum += costeDiario(regsDiarios[i]);
    }
    
    return sum;
}

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios y consumo horarios de energía eléctrica.
 * Post: Devuelve el coste en euros del coste de la energía eléctrica consumida
 *       según los datos de las primeras «numRegs» componentes del vector
 *       «regsDiarios», suponiendo que TODO el consumo de cada uno de los días
 *       almacenados en las componentes de «regsDiarios» se ha producido
 *       precisamente en la hora más barata de ese día.
 */
double costeMinimoPosible(const GastoDiario regsDiarios[],
                          const unsigned numRegs) {

    // Hallamos el coste eléctrico mínimo de cada día y los sumamos

    double sum = 0;

    for (unsigned i = 0; i < numRegs; i++)
    {
        sum += costeDiarioMinimo(regsDiarios[i]);
    }

    return sum;
    
}