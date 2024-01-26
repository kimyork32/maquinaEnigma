#include "Enigma.h"
#include "alfabeto.h"
#include "errores.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;

string stringArchivo(string ruta){
    string texto;
    char caracter;
    ifstream arch(ruta);
    if(!arch.is_open()) return "";
    while(arch.get(caracter)){
        if(caracter == '\n') texto += " ";
        else texto += caracter;
    }
    for(char& c:texto) c=toupper(c);
    arch.close();
    return texto;
}

void guardarTextoArchivo(string ruta, string texto){
    ofstream arch(ruta);
    arch << texto;
    arch.close();
}

int main(int argc, char** argv){

    string texto = stringArchivo("archivos/texto.txt");
    string textoCifrado;
    string textoDescifrado;
    vector<int> posEsp;
    Enigma *enigmaEmisora = nullptr;
    Enigma *enigmaReceptora = nullptr;
    vector<string> confi = {"plugboards/I.pb", "reflectors/I.rf", "rotors/I.rot", "rotors/II.rot", "rotors/III.rot", "rotors/I.pos"};
    enigmaEmisora = new Enigma(confi);
    enigmaReceptora = new Enigma(confi);
    
    // OBTENER LOS ESPACIOS 
    for(int i=0; i<texto.size(); i++){
        if(texto[i]==' '){
            posEsp.push_back(i); 
            // cout << i << endl;
        }     
    }

    cout << "texto:\t\t" << texto << endl;

    // CIFRAR
    for(char letra : texto){
        if(letra!=' '){
            if(letra - 'A' < 0 || ALFABETO_LENGTH -1 < letra - 'A'){
                cerr << letra << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
                delete enigmaEmisora;
                return INVALID_INPUT_CHARACTER;
            }        
            enigmaEmisora->encriptarMensaje(letra);
            textoCifrado+=letra;
        }
    }

    // poniendo espacios en texto cifrado
    for(int i=0; i<posEsp.size(); i++){
        textoCifrado.insert(textoCifrado.begin() + posEsp[i], ' ');
    }
    cout << "texto cifrado:\t" << textoCifrado << endl;

    guardarTextoArchivo("archivos/textoCifrado.txt", textoCifrado);

    // DESENCRIPTAR
    for(char letra : textoCifrado){
        if(letra!=' '){
            if(letra - 'A' < 0 || ALFABETO_LENGTH -1 < letra - 'A'){
                cerr << letra << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
                delete enigmaReceptora;
                return INVALID_INPUT_CHARACTER;
            }        
            enigmaReceptora->encriptarMensaje(letra);
            textoDescifrado+=letra;
        }
    }
    
    // poniendo espacios en texto cifrado
    for(int i=0; i<posEsp.size(); i++){
        textoDescifrado.insert(textoDescifrado.begin() + posEsp[i], ' ');
    }
    cout << "texto descifrado:" << textoDescifrado << endl;

    guardarTextoArchivo("archivos/textoDescifrado.txt", textoDescifrado);

    delete enigmaEmisora;
    delete enigmaReceptora;
    return NO_ERROR;
}   
