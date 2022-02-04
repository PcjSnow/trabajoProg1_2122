#include <iostream>
#include <fstream>

using namespace std;


int main() {

    ifstream f;

    f.open("prueba.csv");

    int agno, mes, dia, hora;
    string basura;
    double precio, consumo;

    //Para el fichero de tarifas
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');
    
    f >> precio;
    f.get();
    //getline(f, agno_string, '-');
    f >> agno;
    f.get();
    f >> mes;
    f.get();
    f >> dia;
    f.get();
    f >> hora;

    getline(f, basura, '\n');
    

    cout <<" precio:" << precio << " año: " << agno << " mes: " << mes << " dia: " << 
        dia << " hora: " << hora;

    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');

    f >> precio;
    f.get();
    // getline(f, agno_string, '-');
    f >> agno;
    f.get();
    f >> mes;
    f.get();
    f >> dia;
    f.get();
    f >> hora;

    getline(f, basura, '\n');

    cout << "\n precio:" << precio << " año: " << agno << " mes: " << mes << " dia: " << dia << " hora: " << hora;

    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');

    f >> precio;
    f.get();
    // getline(f, agno_string, '-');
    f >> agno;
    f.get();
    f >> mes;
    f.get();
    f >> dia;
    f.get();
    f >> hora;

    getline(f, basura, '\n');

    cout << "\n precio:" << precio << " año: " << agno << " mes: " << mes << " dia: " << dia << " hora: " << hora;
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');
    getline(f, basura, ';');

    f >> precio;
    f.get();
    // getline(f, agno_string, '-');
    f >> agno;
    f.get();
    f >> mes;
    f.get();
    f >> dia;
    f.get();
    f >> hora;

    getline(f, basura, '\n');

    cout << "\n precio:" << precio << " año: " << agno << " mes: " << mes << " dia: " << dia << " hora: " << hora;

    // Para el fichero de consumos:

    /*getline(f, basura, ';');
    f >> dia;
    f.get();
    f >> mes;
    f.get();
    f >> agno;
    f.get();
    f >> hora;
    hora -= 1;
    f.get();
    f >> consumo;

    getline(f, basura, '\n');

    cout << "dia: " << dia << " mes: " << mes << " agno: " << agno << " hora: " << hora << 
        " consumo: " << consumo;

    getline(f, basura, ';');
    f >> dia;
    f.get();
    f >> mes;
    f.get();
    f >> agno;
    f.get();
    f >> hora;
    hora -= 1;
    f.get();
    f >> consumo;

    getline(f, basura, '\n');

    cout << "\ndia: " << dia << " mes: " << mes << " agno: " << agno << " hora: " << hora << " consumo: " << consumo;*/

    return 0;
}