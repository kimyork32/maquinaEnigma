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
#include <cmath>

using namespace std;

class Enigma{
private:

  //VARIABLES INDEPENDIENTES
  double u = 3.99446;
  double a0 = 0.0927856134324;
  int b = 4;
  int nIteraciones=500;

  vector<double> valores;
  vector<Rotor> rotores;
  vector<int> posiciones_rotores;
  int num_de_rotores;
  Componente *tablero_de_enchufes{nullptr};
  Componente *reflector{nullptr};
public:
  Enigma(vector<string> confi);
  ~Enigma();
  void print(string t);
  void checkConfigTableroEnchufes(string ruta, vector<int>& contactos);
  void checkConfigReflector(string ruta, vector<int>& contactos);
  void checkConfigRotor(string ruta, vector<int>& contacts);
  void checkConfigPosicionesRotor(string ruta);
  bool esEntradaValidaTableroConexiones(string ruta, fstream& in_stream, int& index_num);
  bool rangoDeNumerosEsCorrecto(int num);
  int checkAparecioAntes(vector<int> contactos, int num, int posicion);
  void encriptarMensaje(char& letra);
  void desencriptarMensaje(char& letra);
  double logisticMap(double a, double u, int iterations);
  double logisticMapNoRecursive(double a, double u);
};

#endif
