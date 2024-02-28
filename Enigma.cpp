#include "Enigma.h"

void Enigma::print(string t){
  cout << t << endl;
}
Enigma::Enigma(vector<string> confi){
  float ax = logisticMap(a0, u, nIteraciones);
  valores.push_back(logisticMapNoRecursive(ax, u));

  int num_confi=confi.size();
  vector<int> tablero_de_enchufescontacts;
  checkConfigTableroEnchufes(confi[0],tablero_de_enchufescontacts);
  vector<int> contactos_reflector;
  checkConfigReflector(confi[1], contactos_reflector);
  vector<vector<int>> contactos_rotor_array;

  vector<int> contactos_rotor;
  for(int i = 2; i < num_confi-1; i++){ 
    checkConfigRotor(confi[i], contactos_rotor);
    contactos_rotor_array.push_back(contactos_rotor);
    contactos_rotor.clear();
  }
  // 3 argc significa que no se proporciona ningun rotor
  if(num_confi == 3){
    num_de_rotores = 0;
  }
  else{
    num_de_rotores = num_confi-3;
  }
  checkConfigPosicionesRotor(confi[num_confi-1]);
  tablero_de_enchufes = new Componente(confi[0]);
  reflector = new Componente(confi[1]);
  for(int i = 0; i < num_de_rotores; i++){
    Rotor rotor(confi[2+i], posiciones_rotores[i]);
    rotores.push_back(rotor);
  }
}

Enigma::~Enigma(){
    if(tablero_de_enchufes){
        delete tablero_de_enchufes;
    }
    if(reflector){
        delete reflector;
    }
}

bool Enigma::esEntradaValidaTableroConexiones(string archivo, fstream& in_stream, int& index_num){
  in_stream >> ws;
  int end_of_file = in_stream.peek();
  if(end_of_file == EOF){
    return false;
  }
  in_stream >> index_num;
  if(in_stream.fail()){
    cerr << "Caracter no numerico en el archivo del panel de conexiones " << archivo << endl;
    in_stream.close();
    throw string("CARACTER NO NUMERICO");
  }
  if(!rangoDeNumerosEsCorrecto(index_num)){
    cerr << "El archivo " << archivo << \
    " contiene un numero que no esta entre 0 y 25" << endl;
    in_stream.close();
    // throw(INVALID_INDEX);
    throw string("INDICE INVALIDO");
  }
  return true;
}

void Enigma::checkConfigTableroEnchufes(string archivo, vector<int>& contacts){
  int indice_num_par; // par
  int indice_num_impar; // impar
  int count = 0;
  fstream in_stream;
  in_stream.open(archivo);
  if(in_stream.fail()){
    cerr << "Error al abrir o leer el archivo de configuracion " << archivo << endl;
    in_stream.close();
    throw string("ERROR_OPENING_CONFIGURATION_FILE");
  }

  while(!in_stream.eof()){
    if(!esEntradaValidaTableroConexiones(archivo, in_stream, indice_num_par)){
      break;
    }
    if(!esEntradaValidaTableroConexiones(archivo, in_stream, indice_num_impar)){
      cerr << "Numero incorrecto de parametros en el archivo del panel de conexiones " \
      << archivo << endl;
      in_stream.close();
      throw string("INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS");
    }
    contacts.push_back(indice_num_par);
    if(checkAparecioAntes(contacts, indice_num_par, count) != -1){
      in_stream.close();
      throw string("INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS");
    }
    count++;

    contacts.push_back(indice_num_impar);
    if(checkAparecioAntes(contacts, indice_num_impar, count) != -1){
      in_stream.close();
      throw ("INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS");
    }
    count++;
  }
  in_stream.close();
}

void Enigma::checkConfigReflector(string archivo, vector<int>& contacts){
  int num;
  int count = 0;
  fstream in_stream;
  in_stream.open(archivo);
  if(in_stream.fail()){
    cerr << "Error al abrir o leer el archivo de configuracion " << archivo << endl;
    in_stream.close();
    throw string("ERROR AL ABRIR EL ARCHIVO DE CONFIGURACIÓN");
  }

  while(!in_stream.eof()){
    in_stream >> ws;
    int end_of_file = in_stream.peek();
    if(end_of_file == EOF){
      break;
    }
    in_stream >> num;
    if(in_stream.fail()){
      cerr << "Caracter no numerico en el archivo reflector " << archivo << endl;
      in_stream.close();
      throw string("NON_NUMERIC_CHARACTER");
    }
    if(!rangoDeNumerosEsCorrecto(num)){
      cerr << "El archivo " << archivo << " contiene un numero que no esta entre 0 y 25" << endl;
      in_stream.close();
      throw string("INDICE INVALIDO");
    }
    contacts.push_back(num);
    if(count < ALFABETO_LENGTH && \
      checkAparecioAntes(contacts, num, count) != -1){
      in_stream.close();
      throw string("MAPEO DE REFLECTORES NO VALIDO");
    }
    count++;

  }
  in_stream.close();

  if(count%2!=0){
      cerr << "Numero incorrecto (impar) de parámetros en el archivo reflector "
      << archivo << endl;
      throw string("NUMERO INCORRECTO DE PARAMETROS DEL TABLERO");
  }
  if(count != ALFABETO_LENGTH){
    cerr << "Numero insuficiente de asignaciones en el archivo reflector: "
    << archivo << endl;
    throw string("NUMERO INCORRECTO DE PARAMETROS DEL REFLECTOR");
  }
}

void Enigma::checkConfigRotor(string archivo, vector<int>& contacts){
  int num;
  int count = 0;
  fstream in_stream;
  in_stream.open(archivo);
  if(in_stream.fail()){
    cerr << "Error al abrir o leer el archivo de configuracion " << archivo << endl;
    in_stream.close();
    throw string("ERROR AL ABRIR EL ARCHIVO DE CONFIGURACION");
  }

  while(!in_stream.eof()){
    in_stream >> ws;
    int end_of_file = in_stream.peek();
    if(end_of_file == EOF){
      break;
    }
    in_stream >> num;

    if(in_stream.fail()){
      cerr << "Caracter no numerico para mapeo en archivo de rotor "
      << archivo << endl;
      in_stream.close();
      throw string("CARACTER NO NUMERICO");
    }
    if(!rangoDeNumerosEsCorrecto(num)){
      cerr << "El archivo " << archivo \
      << " contiene un número que no está entre 0 y 25" << endl;
      in_stream.close();
      throw string("INDICE INVALIDO");
    }
    contacts.push_back(num);

    if(count < ALFABETO_LENGTH-1 && \
      checkAparecioAntes(contacts, num, count) != -1){
      in_stream.close();
      throw string("MAPEO DE ROTOR NO VALIDO");
    }
    count++;
  }
  in_stream.close();

  if(count < ALFABETO_LENGTH){
    cerr << "No todas las entradas asignadas en el archivo del rotor: " << archivo << endl;
    throw string("MAPEO DE ROTOR NO VALIDO");
  }
}

void Enigma::checkConfigPosicionesRotor(string archivo){
  int num;
  int count = 0;
  fstream in_stream;
  in_stream.open(archivo);
  if(in_stream.fail()){
    cerr << "Error al abrir o leer el archivo de configuracion " << archivo << endl;
    in_stream.close();
    throw string("ERROR AL ABRIR ARCHIVO DE CONFIGURACION");
  }
  while(!in_stream.eof()){
    in_stream >> ws;
    int eof = in_stream.peek();
    if(eof == EOF){
      break;
    }
    in_stream >> num;
    if(in_stream.fail()){
      cerr << "Caracter no numerico en el archivo de posiciones del rotor " << archivo  << endl;
      in_stream.close();
      throw string("CARACTER NO NUMERICO");
    }

    if(!rangoDeNumerosEsCorrecto(num)){
      cerr << "El archivo " << archivo \
      << " contiene un numero que no esta entre 0 y 25" << endl;
      in_stream.close();
      throw string("INDICE INVALIDO");
    }
    count++;
    posiciones_rotores.push_back(num);
  }

  int diff = count - num_de_rotores;
  if(diff < 0){
    cerr << "Sin posicion inicial para el rotor " << num_de_rotores + diff \
    << " en el archivo de posicion del rotor: " << archivo << endl;
    in_stream.close();
    throw string("POSICION DEL ROTOR NO INICIADA");
  }
  in_stream.close();
}

bool Enigma::rangoDeNumerosEsCorrecto(int num){
  return (num < ALFABETO_LENGTH && num >= 0);
}

int Enigma::checkAparecioAntes(vector<int> contacts, int num, int position){
  for(int i = 0; i < position; i++ ){
    if(contacts[i] == num){
      cerr << "Mapeo no valido de entrada " << position << " a la salida " << num 
      << " (output " << num << " ya esta asignado desde la entrada " 
      << i << ")" << endl;
      return i;
    }
  }
  return -1;
}

void Enigma::encriptarMensaje(char& letra){
  int indice_actual = letra - 'A'; 
  indice_actual = tablero_de_enchufes->mapear(indice_actual); 

  if(num_de_rotores > 0){
    rotores[num_de_rotores-1].rotar();
  }

  if(num_de_rotores > 0){
    for(int i = num_de_rotores ; i > 0; i--){
      indice_actual = rotores[i-1].cambiarAbajo(indice_actual); 
      indice_actual = rotores[i-1].mapearAdelante(indice_actual);
      indice_actual = rotores[i-1].cambiarArriba(indice_actual); 
      if(rotores[i-1].esPosActualEnMuesca() &&
         rotores[i-1].getPosAnterior() != \
         rotores[i-1].getPosActual()){
        if(i-1 > 0){
          rotores[i-2].rotar();
        }
      }
    }
  }
  indice_actual = reflector->mapear(indice_actual);
  if(num_de_rotores > 0){
    for(int i = 0; i < num_de_rotores; i++){
      indice_actual = rotores[i].cambiarAbajo(indice_actual);
      indice_actual = rotores[i].mapearAtras(indice_actual);
      indice_actual = rotores[i].cambiarArriba(indice_actual);
    }
  }
  indice_actual = tablero_de_enchufes->mapear(indice_actual);
  // letra = indice_actual+'A';
  letra = indice_actual;
  
  
  // ENCRIPTACION CESAR
  
  int r = (static_cast<int>(valores[valores.size()-1] * pow(10, b))) % ALFABETO_LENGTH;

  letra = (letra+r)%26+'A';
  valores.push_back(logisticMapNoRecursive(valores[valores.size()-1], u));
}

void Enigma::desencriptarMensaje(char& letra){


  // DESENCRIPTACION CESAR
  int r = (static_cast<int>(valores[valores.size()-1] * pow(10, b))) % ALFABETO_LENGTH; 

  letra = letra - 'A';
  if(letra-r <0){
    letra = letra-r+26+'A';
  }
  else{
    letra = (letra-r)%26+'A';
  }
  valores.push_back(logisticMapNoRecursive(valores[valores.size()-1], u));

  int indice_actual = letra - 'A'; 
  indice_actual = tablero_de_enchufes->mapear(indice_actual); 

  if(num_de_rotores > 0){
    rotores[num_de_rotores-1].rotar();
  }

  if(num_de_rotores > 0){
    for(int i = num_de_rotores ; i > 0; i--){
      indice_actual = rotores[i-1].cambiarAbajo(indice_actual); 
      indice_actual = rotores[i-1].mapearAdelante(indice_actual);
      indice_actual = rotores[i-1].cambiarArriba(indice_actual); 
      if(rotores[i-1].esPosActualEnMuesca() &&
         rotores[i-1].getPosAnterior() != \
         rotores[i-1].getPosActual()){
        if(i-1 > 0){
          rotores[i-2].rotar();
        }
      }
    }
  }
  indice_actual = reflector->mapear(indice_actual);
  if(num_de_rotores > 0){
    for(int i = 0; i < num_de_rotores; i++){
      indice_actual = rotores[i].cambiarAbajo(indice_actual);
      indice_actual = rotores[i].mapearAtras(indice_actual);
      indice_actual = rotores[i].cambiarArriba(indice_actual);
    }
  }
  indice_actual = tablero_de_enchufes->mapear(indice_actual);
  letra = indice_actual + 'A';
}

double Enigma::logisticMap(double a, double u, int iterations) {
    // Caso base: si las iteraciones llegan a 0, devuelve el valor actual de 'a'
    if (iterations == 0) {
        return a;
    } else {
        // Llamada recursiva con la siguiente iteración
        return logisticMap(u * a * (1 - a), u, iterations - 1);
    }
}
double Enigma::logisticMapNoRecursive(double a, double u) {
  return u * a * (1 - a);
}

