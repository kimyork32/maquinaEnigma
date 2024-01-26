#ifndef ROTOR_H
#define ROTOR_H

#include "Alfabeto.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Rotor{
private:
    int pos_actual;
    int pos_anterior;
    int contactos[ALFABETO_LENGTH];
    std::vector<int> muescas;

public:
    Rotor(std::string ruta, int pos_inicial);
    int getPosActual();
    int getPosAnterior();
    void rotar();
    int cambiarArriba(int indice);
    int cambiarAbajo(int indice);
    int mapearAdelante(int indice);
    int mapearAtras(int contacto);
    bool esPosActualEnMuesca();
    
    const int* getContactos() const;
};

#endif
