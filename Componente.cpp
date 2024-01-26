#include "Componente.h"

Componente::Componente(std::string ruta){
  std::fstream archivo;
  archivo.open(ruta);
  int num;
  int count = 0;
  while(archivo >> num){
    if(count%2 == 0){ // PARES
      entrada_par.push_back(num);
    }
    else{ // IMPARES
      entrada_impar.push_back(num);
    }
    count++;
  }
  archivo.close();
}

int Componente::mapear(int input){
  int tam = entrada_par.size();
  for(int i = 0; i< tam; i++){
    if(input == entrada_par[i]){
      return entrada_impar[i];
    }
    if(input == entrada_impar[i]){
      return entrada_par[i];
    }
  }
  return input;
}
