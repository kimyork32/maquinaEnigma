#ifndef MENU_H
#define MENU_H
#include "Enigma.h"
#include "alfabeto.h"
#include "errores.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cctype>
#include <memory>
#include <filesystem>
#include <vector>

class Menu{
private:
    Enigma *enigmaEmisora;
    Enigma *enigmaReceptora;
    
    vector<string> configuraciones;
    

    bool confIniciada;

    string texto;
    string textoCifrado;
    string textoDescifrado;
    vector<int> posEsp;

    void opc1_maquinaEnigma();

    void opc1_1_maquinaEmisora();
    void opc1_2_maquinaReceptora();
    void opc1_3_cambiarConfiguraciones();

    void opc1_n_1_enviarMensaje(int m);
    void opc1_n_2_verMensajeEnviado(int m);
    void opc1_n_3_desencriptarMensajeEncriptado(int m);
    
    void opc1_3_1_tableroDeEnchufes();
    void opc1_3_2_reflector();
    void opc1_3_3_rotores();
    void opc1_3_4_generarConfiguracionesAleatorias();
    void opc1_3_5_mostrarConfiguracionesEstablecidas();

    void opc1_3_n_1_listarConfiguracionesDeCompomente(string componente);
    void opc1_3_n_2_generarConfiguracionAleatoriaDeComponente(int componente);

    vector<string> listarArchivosDeCarpeta(const string& subdirectorio);
    string stringArchivo(string ruta);
    void guardarTextoArchivo(string ruta, string texto);

public:
    Menu();
    void menu();

};

#endif