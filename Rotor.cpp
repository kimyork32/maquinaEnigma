#include "Rotor.h"
#include "Alfabeto.h"

Rotor::Rotor(std::string ruta, int pos_inicial){
  std::fstream archivo;
  archivo.open(ruta);
  int num;
  int count = 0;
  while(archivo >> num){
    if(count < ALFABETO_LENGTH){
      contactos[count] = num;
    }
    else{
      muescas.push_back(num);
    }
    count++;
  }
  pos_actual = pos_inicial;
}

int Rotor::getPosAnterior(){
  return pos_anterior;
}

int Rotor::getPosActual(){
  return pos_actual;
}

void Rotor::rotar(){
  pos_anterior = pos_actual;
  pos_actual = (pos_actual + 1) % ALFABETO_LENGTH;
}

int Rotor::cambiarArriba(int indice){
  return (indice - getPosActual() + ALFABETO_LENGTH) % ALFABETO_LENGTH;
}

int Rotor::cambiarAbajo(int indice){
  return (indice + getPosActual()) % ALFABETO_LENGTH;
}

int Rotor::mapearAdelante(int indice){
  return contactos[indice];
}

int Rotor::mapearAtras(int contact){
  for(int i = 0; i < ALFABETO_LENGTH; i++){
      if(contact == contactos[i]){
        return i;
      }
  }
  return contact;
}

bool Rotor::esPosActualEnMuesca(){
  int num_de_muescas = muescas.size();
  for(int i= 0; i< num_de_muescas; i++){
    if(pos_actual == muescas[i]){
      return true;
    }
  }
  return false;
}

const int* Rotor::getContactos() const {
    return contactos;
}