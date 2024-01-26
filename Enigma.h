#ifndef ENIGMA_H
#define ENIGMA_H

#include "Componente.h"
#include "Rotor.h"
#include "alfabeto.h"
#include "errores.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Enigma{
private:
vector<Rotor> rotores;
vector<int> posiciones_rotores;
int num_de_rotores;
Componente *tablero_de_enchufes{nullptr};
Componente *reflector{nullptr};
public:
  Enigma(vector<string> confi);
  ~Enigma();
  void checkConfigTableroEnchufes(string ruta, vector<int>& contactos);
  void checkConfigReflector(string ruta, vector<int>& contactos);
  void checkConfigRotor(string ruta, vector<int>& contacts);
  void checkConfigPosicionesRotor(string ruta);
  bool esEntradaValidaTableroConexiones(string ruta, fstream& in_stream, int& index_num);
  bool rangoDeNumerosEsCorrecto(int num);
  int checkAparecioAntes(vector<int> contactos, int num, int posicion);
  void encriptarMensaje(char& letra);
};

#endif
