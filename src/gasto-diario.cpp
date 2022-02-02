#include "gasto-diario.hpp"
#include <iostream>

/*
 * Pre:  ---
 * Post: Devuelve la hora en la que el precio de la electricidad según los datos
 *       de precios horarios del registro «gasto» fue más cara.
 */
unsigned horaMasCara(const GastoDiario &gasto) {

    double max = gasto.precios[0];
    unsigned hora;

    for (unsigned i = 1; i < NUM_HORAS; i++)
    {
        if (gasto.precios[i] > max)
        {
            max = gasto.precios[i];
            hora = i;
        }
        
    }
    
    return hora;
}

/*
 * Pre:  ---
 * Post: Devuelve el precio medio de la electricidad según los datos de precios
 *       horarios del registro «gasto».
 */
double costeMedio(const GastoDiario &gasto) {

    double sum = 0;

    for (unsigned i = 0; i < NUM_HORAS; i++)
    {
        sum += gasto.precios[i];
    }

    return sum / NUM_HORAS;
    
}

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario &gasto) {

    double sum = 0;

    for (unsigned i = 0; i < NUM_HORAS; i++)
    {
        sum += gasto.consumos[i] * gasto.precios[i];
    }
    
}

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que todo el
 *       consumo eléctrico reflejado en el registro «gasto» hubiera tenido lugar
 *       en la hora con el precio más barato del registro «gasto».
 */
double costeDiarioMinimo(const GastoDiario &gasto) {

    //Primero hallamos el total de consumo eléctrico del día.
    double total_consumo = 0;

    for (unsigned i = 0; i < NUM_HORAS; i++)
    {
        total_consumo += gasto.consumos[i];
    }
    
    //Ahora hallamos la hora más barata del día

    unsigned hora_mas_barata;
    double min = gasto.precios[0];

    for (unsigned i = 1; i < NUM_HORAS; i++)
    {
        if (gasto.precios[i] < min) {
            min = gasto.precios[i];
            hora_mas_barata = i;
        }
    }

    return total_consumo * gasto.precios[hora_mas_barata];
    
}