#include "tarifas-comerciales.hpp"
#include <iostream>


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que se han
 *       aplicado los costes especificados por la tarifa del parámetro «tarifa».
 */
double costeDiarioTarifaPlanaTramos(const GastoDiario& gasto,
                                    const TarifaPlanaTramos tarifa) {
    
    double total = 0;

    //Hallemos el coste total

    for (unsigned i = 0; i < NUM_HORAS; i++)
    {
        //Horas valle
        if (i >= 0 && i <= 7)
        {
            total += gasto.consumos[i] * tarifa.valle;
        }
        else if ((i >= 8 && i <= 9) || (i >= 14 && i <= 17) || (i >= 22 && i <= 23)) { // Horas llano
            
            total += gasto.consumos[i] * tarifa.llano;
        }
        else { // Horas punta

            total += gasto.consumos[i] * tarifa.punta;
        }
        
    }

    return total;
}


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos de las «numRegs» primeras componentes del
 *       vector «regDiario» suponiendo que se han aplicado en cada uno de los
 *       días de dichas componentes los costes especificados por la tarifa del
 *       parámetro «tarifa».
 */
double costeTarifaPlanaTramos(const GastoDiario regDiario[],
                        const unsigned numRegs, const TarifaPlanaTramos tarifa) {

    double total = 0;

    for (unsigned i = 0; i < numRegs; i++)
    {
        total += costeDiarioTarifaPlanaTramos(regDiario[i], tarifa);
    }
    
    return total;
}


