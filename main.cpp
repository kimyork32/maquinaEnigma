#include "Enigma.h"
#include "alfabeto.h"
#include "errores.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cctype>
#include <locale>
#include <string>
#include <codecvt>
#include <fstream>
#include <cctype>


using namespace std;

string stringArchivo(string ruta){
    string texto;
    char caracter;
    ifstream arch(ruta);
    if(!arch.is_open()) return "";
    while(arch.get(caracter)){
        caracter= toupper(caracter);
        if(caracter == '\n') texto += " ";
        else if(caracter>=65 && caracter<=90){
            texto += caracter;
        }
    }
    // for(char& c:texto) c=toupper(c);
    arch.close();
    return texto;
}

wstring getTextWArchivo(string ruta){
    wstring texto;
    wifstream arch(ruta);
    wstring linea;
        while (getline(arch, linea)) {
            texto += linea + L" ";
        }
    arch.close();
    
    return texto;
}

wstring textSinFormato(wstring textoConTildes){

    wstring textoSinTildes;
    for(int i=0; i<textoConTildes.size(); i++){
        switch(textoConTildes[i]){
            case(225):
                textoSinTildes += 'a';
                break;
            case(233):
                textoSinTildes += 'e';
                break;
            case(237):
                textoSinTildes += 'i';
                break;
            case(243):
                textoSinTildes += 'o';
                break;
            case(250):
                textoSinTildes += 'u';
                break;
            case(193):
                textoSinTildes += 'A';
                break;
            case(201):
                textoSinTildes += 'E';
                break;
            case(205):
                textoSinTildes += 'I';
                break;
            case(211):
                textoSinTildes += 'O';
                break;
            case(218):
                textoSinTildes += 'U';
                break;
            case(241):
                textoSinTildes += 'n';
                break;
            case(209):
                textoSinTildes += 'N';
                break;
            case(32):
                textoSinTildes += ' ';
            default:
                if((textoConTildes[i]>=65 && textoConTildes[i]<=90)||(textoConTildes[i]>=97&&textoConTildes[i]<=122)){
                    textoSinTildes += textoConTildes[i];
                }   
        }
    }

    return textoSinTildes;
}


void guardarTextoArchivo(string ruta, string texto){
    ofstream arch(ruta);
    arch << texto;
    arch.close();
}

void frecuencias(vector<int>&frecuencias, string texto){
    for(char c : texto){
        frecuencias[static_cast<int>(c)-'A']++;
    }
}
    

int main(){
    // Menu menuPrincipal;
    // menuPrincipal.menu();
    wstring tempTexto = getTextWArchivo("archivos/texto.txt");
    wstring tempTexto2  = textSinFormato(tempTexto);;
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    
    string texto  = converter.to_bytes(tempTexto2);
    for(char &c : texto) c = toupper(c);

    string textoCifrado;
    string textoDescifrado;
    vector<int> posEsp;
    Enigma *enigmaEmisora = nullptr;
    Enigma *enigmaReceptora = nullptr;
    vector<string> confi = {"plugboards/I.pb", "reflectores/I.rf", "rotores/I.rot", "rotores/II.rot", "rotores/III.rot", "rotores/I.pos"};
    enigmaEmisora = new Enigma(confi);
    enigmaReceptora = new Enigma(confi);


    // OBTENER LOS ESPACIOS 
    for(int i=0; i<texto.size(); i++){
        if(texto[i]==' '){
            posEsp.push_back(i); 
            // cout << i << endl;
        }     
    }

    cout << "tamanho:\t" << texto.size() << endl;
    // cout << "texto:\t\t" << texto << endl;
    for(int i=0; i<100; i++){
        cout << texto[i];
    }
    cout << endl;

    // // CIFRAR
    for(char letra : texto){
        if(letra!=' '){
            if(letra - 'A' < 0 || ALFABETO_LENGTH -1 < letra - 'A'){
                cerr << letra << " <No es un caracter de entrada valido (A-Z)>" << endl;
                delete enigmaEmisora;
                return INVALID_INPUT_CHARACTER;
            }        
            enigmaEmisora->encriptarMensaje(letra);
            textoCifrado+=letra;
        }
    }

    // poniendo espacios en texto cifrado
    // for(int i=0; i<posEsp.size(); i++){
    //     textoCifrado.insert(textoCifrado.begin() + posEsp[i], ' ');
    // }
    // cout << "texto cifrado:\t" << textoCifrado << endl;
    for(int i=0; i<100; i++){
        cout << textoCifrado[i];
    }
    cout << endl;

    guardarTextoArchivo("archivos/textoCifrado.txt", textoCifrado);

    // FIN DE CIFRADO

    textoCifrado = stringArchivo("archivos/textoCifrado.txt");
    // DESENCRIPTAR
    for(char letra : textoCifrado){
        if(letra!=' '){
            if(letra - 'A' < 0 || ALFABETO_LENGTH -1 < letra - 'A'){
                cerr << letra << " no es un caracter de entrada valido (A-Z)" << endl;
                delete enigmaReceptora;
                return INVALID_INPUT_CHARACTER;
            }        
            enigmaReceptora->desencriptarMensaje(letra);
            textoDescifrado+=letra;
        }
    }
    
    // poniendo espacios en texto cifrado
    for(int i=0; i<posEsp.size(); i++){
        textoDescifrado.insert(textoDescifrado.begin() + posEsp[i], ' ');
    }
    // cout << "texto descifrado:" << textoDescifrado << endl;
    for(int i=0; i<100; i++){
        cout << textoDescifrado[i];
    }
    cout << endl;

    guardarTextoArchivo("archivos/textoDescifrado.txt", textoDescifrado);


    // FRECUENCIAS DEL TEXTO CIFRADO
    vector<int> frecuenciasT(26);
    vector<int> frecuenciasTC(26);
    
    frecuencias(frecuenciasT, texto);
    frecuencias(frecuenciasTC, textoCifrado);
    
    for(int i=0; i<frecuenciasT.size(); i++){
        cout << static_cast<char>(i+'A') << ": " << frecuenciasT[i] << endl;    
    }
    cout << endl;

    for(int i=0; i<frecuenciasTC.size(); i++){
        cout << static_cast<char>(i+'A') << ": " << frecuenciasTC[i] << endl;    
    }



    // FIN DE DESCIFRADO
    delete enigmaEmisora;
    delete enigmaReceptora;
    return NO_ERROR;
}   
