#ifndef SUBCOMPONENTE_H
#define SUBCOMPONENTE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Componente{
private:
    std::vector<int> entrada_par;
    std::vector<int> entrada_impar;
public:
    Componente(std::string ruta);
    int mapear(int input);
};

#endif