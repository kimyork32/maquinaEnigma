#include "Menu.h"


Menu::Menu() : enigmaEmisora(nullptr), enigmaReceptora(nullptr) {
    confIniciada=false;
    configuraciones.reserve(4);
}

void Menu::menu(){
    int opc=-1;
    while(opc){
        cout << "Menu\n"
            << "1) Maquina enigma\n"
            << "2) Magia negra\n"
            << "0) Salir\n"
            << "Opc: ";
        
        cin >> opc;

        switch (opc){
            case 1:
                opc1_maquinaEnigma();
                break;
            case 2:
                break;
            case 0:
                cout << "Saliendo\n"; 
                opc=0;
                break;
        }
    }
    // confi = {"plugboards/I.pb", "reflectors/I.rf", "rotors/I.rot", "rotors/II.rot", "rotors/III.rot", "rotors/I.pos"};
    // enigmaEmisora = new Enigma(confi);
    // enigmaReceptora = new Enigma(confi);

    // enigmaEmisora->print("hola");
}

void Menu::opc1_maquinaEnigma(){
    int opc=-1;
    while(opc){
        cout << "Maquina Enigma\n"
            << "1) Maquina emisora\n"
            << "2) Maquina receptora\n"
            << "3) Cambiar configuraciones\n"
            << "0) atras\n"
            << "opc: ";
        cin >> opc;
        switch(opc){
            case 1:
                opc1_1_maquinaEmisora();
                break;
            case 2:
                opc1_2_maquinaReceptora();
                break;
            case 3:
                opc1_3_cambiarConfiguraciones();
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }
    }
    
}
void Menu::opc1_1_maquinaEmisora(){
    if(confIniciada){
        int opc=-1;
        while(opc){
            cout << "Maquina Emisora\n"
                << "1) Enviar mensaje encriptado\n"
                << "2) Ver mensaje enviado\n"
                << "3) Desencriptar mensaje encriptado\n"
                << "0) atras\n"
                << "opc: ";
            cin >> opc;

            switch(opc){
                case 1: 
                    opc1_n_1_enviarMensaje(1);
                    break;
                case 2:
                    opc1_n_2_verMensajeEnviado(1);
                    break;
                case 3:
                    opc1_n_3_desencriptarMensajeEncriptado(1);
                    break;
                default:
                    cout << "Opcion invalida\n";
                    break;
            }
        }
    } else{
        opc1_3_cambiarConfiguraciones();
    }
}
void Menu::opc1_2_maquinaReceptora(){
    if(confIniciada){
        int opc=-1;
        while(opc){
            cout << "Maquina receptora\n"
                << "1) Enviar mensaje encriptado\n"
                << "2) Ver mensaje enviado\n"
                << "3) Desencriptar mensaje encriptado\n"
                << "0) atras\n"
                << "opc: ";
            cin >> opc;

            switch(opc){
                case 1: 
                    opc1_n_1_enviarMensaje(2);
                    break;
                case 2:
                    opc1_n_2_verMensajeEnviado(2);
                    break;
                case 3:
                    opc1_n_3_desencriptarMensajeEncriptado(2);
                    break;
                default:
                    cout << "Opcion invalida\n";
                    break;
            }
        }

    } else{
        opc1_3_cambiarConfiguraciones();
    }
}
void Menu::opc1_3_cambiarConfiguraciones(){
    int opc=-1;
    while(opc){
        cout << "Configuraciones\n"
            << "1) Tablero de enchufes\n"
            << "2) Reflector\n"
            << "3) Rotores\n"
            << "4) Configuraciones aleatorias\n"
            << "0) atras\n"
            << "opc: ";
        cin >> opc;

        switch(opc){
            case 1:
                opc1_3_1_tableroDeEnchufes();
                break;
            case 2:
                opc1_3_2_reflector();
                break;
            case 3:
                opc1_3_3_rotores();
                break;
            case 4: 
                opc1_3_4_generarConfiguracionesAleatorias();
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }
    }
    enigmaEmisora = new Enigma(configuraciones);
    enigmaReceptora = new Enigma(configuraciones);
}

void Menu::opc1_n_1_enviarMensaje(int m){
    if(m==1){
        //enviar mensaje desde maquina emisora
        // enigmaEmisora->print("hola");
        texto = stringArchivo("archivos/texto.txt");
            // // OBTENER LOS ESPACIOS 
        for(int i=0; i<texto.size(); i++){
            if(texto[i]==' '){
                posEsp.push_back(i); 
            }     
        }
        // // CIFRAR
        for(char letra : texto){
            if(letra!=' '){
                if(letra - 'A' < 0 || ALFABETO_LENGTH -1 < letra - 'A'){
                    cerr << letra << "| el caracter de entrada no es valido(A-Z)!" << endl;
                    delete enigmaEmisora;
                    cout << "caracter de entrada invalido" << endl;
                    return ;
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

        // cout << "mensaje enviado" << endl;
    }else{
        //enviar mensaje desde maquina receptora
        // enigmaEmisora->print("hola");


        // // DESCIFRAR
        for(char letra : textoCifrado){
            if(letra!=' '){
                if(letra - 'A' < 0 || ALFABETO_LENGTH -1 < letra - 'A'){
                    cerr << letra << "| el caracter de entrada no es valido(A-Z)!" << endl;
                    // delete dele;
                    return ;
                }        
                enigmaReceptora->desencriptarMensaje(letra);
                textoDescifrado+=letra;
            }
        }


        // poniendo espacios en texto cifrado
        for(int i=0; i<posEsp.size(); i++){
            textoDescifrado.insert(textoDescifrado.begin() + posEsp[i], ' ');
        }
        cout << "texto descifrado:\t" << textoDescifrado<< endl;
        guardarTextoArchivo("archivos/textoDescifrado.txt", textoDescifrado);

        // cout << "mensaje enviado" << endl;
    }
}
void Menu::opc1_n_2_verMensajeEnviado(int m){
    if(m==1){
        //ver mensaje enviado desde maquina emisora
    }else{
        //ver mensaje enviado desde maquina receptora
    }
}
void Menu::opc1_n_3_desencriptarMensajeEncriptado(int m){
    if(m==1){
        // desencriptar mensaje encriptado desde maquina emisora
    }else{
        // desencriptar mensaje encriptado desde maquina receptora
    }
}

void Menu::opc1_3_1_tableroDeEnchufes(){
    int opc=-1;
    while(opc){
        cout << "Tablero de enchufes\n"
            << "1) Mostrar configuraciones\n"
            << "2) Generar configuracion aleatoria\n"
            << "0) atras\n"
            << "opc:  ";

        cin >> opc;
        switch(opc){
            case 1:
                //Mostar configuraciones para cambiar
                opc1_3_n_1_listarConfiguracionesDeCompomente("plugboards");
            case 2:
                opc1_3_n_2_generarConfiguracionAleatoriaDeComponente(1);
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }
    }
}

void Menu::opc1_3_2_reflector(){
    int opc=-1;
    while(opc){
        cout << "Reflector\n"
            << "1) Mostrar configuraciones\n"
            << "2) Generar configuracion aleatoria\n"
            << "0) atras\n"
            << "opc:  ";
        cin >> opc;
        switch(opc){
            case 1:
                //Mostrar configuraciones para cambiar
                opc1_3_n_1_listarConfiguracionesDeCompomente("reflectors");
            case 2:
                opc1_3_n_2_generarConfiguracionAleatoriaDeComponente(2);
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }
    }
}

void Menu::opc1_3_3_rotores(){
    int opc=-1;
    while(opc){
        cout << "Rotores\n"
            << "1) Mostrar configuraciones\n"
            << "2) Generar configuracion aleatoria\n"
            << "0) atras\n"
            << "opc:  ";
        cin >> opc;
        switch(opc){
            case 1:
                //Mostar configuraciones para cambiar
                opc1_3_n_1_listarConfiguracionesDeCompomente("rotors");
            case 2:
                opc1_3_n_2_generarConfiguracionAleatoriaDeComponente(3);
                break;
            default:
                cout << "Opcion invalida\n";
                break;
        }    
    }
}

void Menu::opc1_3_n_1_listarConfiguracionesDeCompomente(const string componente){
    vector<string>lista = listarArchivosDeCarpeta(componente);
    int opc=-1;
    while(opc){
        cout << "Seleccionar archivo:\n";
        for(int i=0; i<lista.size(); i++){
            cout << i+1 << ") " << lista[i] << endl;
        }
        cout << "opc: "; cin >> opc;
        if(opc>=1 && opc<=lista.size()){
            if (componente=="plugboards"){
                configuraciones[0] = lista[opc-1];
            }else if (componente=="reflectors"){
                configuraciones[1] = lista[opc-1];
            }else if (componente == "rotors"){
                configuraciones.insert(configuraciones.end()-1, lista[opc-1]);
            }            
        }
        cout << "opcion invalida\n";
    }
}

void Menu:: opc1_3_4_generarConfiguracionesAleatorias(){
    //generar conf aleatoria
    vector<string> temp = {"plugboards/I.pb", "reflectors/I.rf", "rotors/I.rot", "rotors/II.rot", "rotors/III.rot", "rotors/I.pos"};
    configuraciones = move(temp);
    confIniciada = true;
}

void Menu::opc1_3_5_mostrarConfiguracionesEstablecidas(){
    for(int i=0; i<configuraciones.size(); i++){
        cout << "{" << configuraciones[i] << ", ";
    }
    cout << "}" << endl;
}

vector<string> Menu::listarArchivosDeCarpeta(const string& subdirectorio) {
    filesystem::path rutaActual = filesystem::current_path();
    rutaActual /= subdirectorio;
    vector<string>archivos;
    for (const auto& entry : filesystem::directory_iterator(rutaActual)) {
        // cout << entry.path().filename().string() << endl;
        archivos.push_back(entry.path().filename().string());
    }
    return archivos;
}

// }
void Menu::opc1_3_n_2_generarConfiguracionAleatoriaDeComponente(int componente){
    //generar configunracion aleatoria de cada compomente
    switch(componente){
        case 1:
            // TE random
            break;
        case 2:
            // Reflector random
            break;
        case 3:
            // Rotores random
            break;
        default:
            cout << "Opcion invalida\n";
            break;
    }
    
}

string Menu::stringArchivo(string ruta){
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

void Menu::guardarTextoArchivo(string ruta, string texto){
    ofstream arch(ruta);
    arch << texto;
    arch.close();
}