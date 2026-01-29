#include <iostream>
#include <fstream>
#include <conio.h>      // _kbhit(), _getch()
#include <windows.h>    // Sleep(), system("cls")
#include <string>
#include <string.h>
#include <locale>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>










using namespace sf;

using namespace std;


// COLORES ANSI
#define RESET   "\x1B[0m"
#define AZUL    "\x1B[34m"
#define ROJO    "\x1B[31m"
#define VERDE   "\x1B[32m"
#define AMARILLO "\x1B[33m"
#define NARANJA "\x1B[38m"
#define MORADO  "\x1B[35m"
#define NEGRO   "\x1B[30m"
#define BLANCO   "\x1B[37m"

// Función para configurar la consola en UTF-8
void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    // Opcional: para evitar problemas con caracteres especiales
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

//Clock reloj;
//Time tiempo = reloj.getElapsedTime();
//double tiempo_sincrono;



SoundBuffer buffer1, buffer2, buffer3, buffer4, buffer5;
Sound sound1(buffer1), sound2(buffer2), sound3(buffer3), sound4(buffer4), sound5(buffer5);

class Robot {
public:
    bool vivo;
    int jugadorx, jugadory;
    float vida, vidaTotal;
    int largo, ancho;
    int tesoro, bomba, vidasRestantes, tesoroRestante;
    char mapa[150][150];
    int minutos, segundos;

    //CONSTRUCTOR
    Robot(bool v, int x, int y, float vida_, float vidaTot, int tes, int tesRes, int bom, int vr, int min, int sg) {
        vivo = true;
        jugadorx = x;
        jugadory = y;
        vida = vida_;
        vidaTotal = vidaTot;
        tesoro = tes;
        tesoroRestante = tesRes;
        bomba = bom;
        vidasRestantes = vr;
        largo = 0;
        ancho = 0;
        minutos = min;
        segundos = sg;

        for (int i = 0; i < 150; i++)
            for (int j = 0; j < 150; j++)
                mapa[i][j] = ' ';
    }


    // ANIMACION MUERTE
    void animacionMuerte() {
        
      sound1.stop();

        Music buffer;
        if (!buffer.openFromFile("darksouls.wav")) {
            cout << "Error al cargar musica!" << endl;
        }
        else {
            buffer.play();
        
        }


        char muerte[5][83]= {

            {'0','0','1','1','1','0','0','0','0','1','0','0','0','0','0','1','0','1','0','0','0','0','1','1','0','0','t','0','1','1','1','0','0','0','1','0','0','0','1','0','0','0','1','1','0','0','1','1','0','0','0'},
            {'0','1','0','0','0','0','0','0','1','1','1','0','0','0','0','1','1','1','0','0','0','1','0','0','0','0','t','1','0','1','0','1','0','0','1','0','0','0','1','0','0','1','0','0','0','0','1','0','1','0','0'},
            {'0','1','0','1','1','1','0','0','1','0','1','0','0','0','1','0','1','0','1','0','0','1','1','1','0','0','t','1','1','0','1','1','0','0','0','1','0','1','0','0','0','1','1','1','0','0','1','0','1','0','0'},
            {'0','1','0','0','1','0','0','1','1','0','1','1','0','0','1','0','1','0','1','0','0','1','0','0','0','0','t','1','0','1','0','1','0','0','0','1','0','1','0','0','0','1','0','0','0','0','1','1','1','0','0'},
            {'0','0','1','1','1','0','0','1','0','0','0','1','0','0','1','0','1','0','1','0','0','0','1','1','0','0','t','0','1','1','1','0','0','0','0','0','1','0','0','0','0','0','1','1','0','0','1','0','0','1','0'}



        };

		bool salir = false;
		int contador = 0; //Variable para limitar la animacion


        while (!salir && contador < 10) {
            system("cls");
            cout << ROJO << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

           for (int i = 0; i <5; i++) {
               cout << "\t\t\t\t\t\t\t\t\t\t";
               for (int j = 0; j < 83; j++) {

                   if (muerte[i][j] == 't') {
                       printf("\t");
                   }

                   if (muerte[i][j] == '1') {
                       printf("█");
                   }
                   else {
                       cout << " ";
                   }
               }
               cout << "\n";
           }

            cout << RESET << "\n\n\t\t\t\t\t\t\t\t\t\tPresiona cualquier tecla para volver al menú...";

            Sleep(300);
            system("cls");

           

            if (_kbhit()) {       // ¿Se presionó una tecla?
                _getch();         // Consumir la tecla
                salir = true;     // ¡SALIR DEL BUCLE!
            }

            Sleep(200);
			contador++; // Incrementar el contador

            
        }
        
        
    }

    // ANIMACION VICTORIA
   void animacionVictoria() {
       
       sound1.stop();

       Music buffer;
       if(!buffer.openFromFile("victoria.wav")){
           cout << "Error al cargar musica!" << endl;
       }
       else {
           buffer.play();
		   buffer.setLooping(true); //Entra en bucle la musica de victoria
         
       }

        char victoria[10][83] = {
            {'0','1','1','0','0','1','1','t','0','0','1','1','1','0','t','0','1','0','0','1','t','0','1','0','0','0','1','t','0','1','1','1','1','1','t','0','1','0','0','1'},
            {'0','1','1','0','0','1','1','t','0','1','0','1','0','1','t','0','1','0','0','1','t','0','1','0','0','0','1','t','0','0','0','1','0','0','t','0','1','1','0','1'},
            {'0','1','1','1','1','1','1','t','0','1','1','0','1','1','t','0','1','0','0','1','t','0','1','0','0','0','1','t','0','0','1','1','1','0','t','0','1','1','0','1'},
            {'0','0','1','1','1','1','0','t','0','1','1','0','1','1','t','0','1','0','0','1','t','0','1','0','1','0','1','t','0','0','1','1','1','0','t','0','1','0','1','1'},
            {'0','0','0','1','1','0','0','t','0','1','0','1','0','1','t','0','1','0','0','1','t','0','1','1','0','1','1','t','0','0','0','1','0','0','t','0','1','0','1','1'},
            {'0','0','0','1','1','0','0','t','0','0','1','1','1','0','t','0','1','1','1','1','t','0','1','1','0','1','1','t','0','1','1','1','1','1','t','0','1','0','0','1'}

        };

        bool salir = false;
        int contador = 0;

        while (!salir && contador < 10) {
            system("cls");
            cout << VERDE << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            for (int i = 0; i < 10; i++) {
                cout << "\t\t\t\t\t\t\t\t\t\t";
                for (int j = 0; j < 83; j++) {

                    if (victoria[i][j] == 't') {
                        printf("\t");
                    }

                    if (victoria[i][j] == '1') {
                        printf("█");
                    }
                    else {

                        cout << " ";
                    }
                }
                cout << "\n";
            }

            cout << RESET << "\n\n\t\t\t\t\t\t\t\t\t\tPresiona cualquier tecla para volver al menú...";

            Sleep(300);
            system("cls");

            //skipea con cualquier tecla
            if (_kbhit()) break;
        }

        Sleep(200);
        contador++;
        _getch();
    }

    void matriz() {
        ifstream f("mapa2.txt");
        string linea;
        largo = 0;

        while (getline(f, linea)) {
            for (int i = 0; i < (int)linea.size(); i++) {
                mapa[largo][i] = linea[i];
            }
            ancho = linea.size();
            largo++;
        }
    }

    void mostrarMapa() {
        if (vivo) {
            mapa[jugadory][jugadorx] = 'R';
        }

        for (int i = 0; i < largo; i++) {
            for (int j = 0; j < ancho; j++) {
                char c = mapa[i][j];
                if (c == 'C') cout << NEGRO << "█" << RESET;
                else if (c == 'A') cout << ROJO << "█" << RESET;
                else if (c == 'B') cout << MORADO << "█" << RESET;
                else if (c == 'v') cout << VERDE << "▄" << RESET;
                else if (c == 'R') cout << NEGRO << "▄" << RESET;
                else if (c == 'M') cout << AZUL << "█" << RESET;
                else if (c == 'V') cout << VERDE << "█" << RESET;
                else if (c == 'P') cout << NEGRO << "█" << RESET;
                else cout << " ";
            }
            cout << "\n";
        }

        cout << NEGRO;
        cout << "Vida actual: " << vida << "%"
            << "\tBombas: " << bomba
            << "\tTesoro: " << tesoro
            << "\tTesoro Restantes: " << tesoroRestante
            << "\tBaterías Restantes: " << vidasRestantes << "\n";

      

        // Mostrar controles debajo del mapa
        cout << "paso: w,a,s,d    salto: i,j,k,l    bomba: g\n";
        cout << RESET;
    }


    void movimiento() {
        char tecla = ' ';
        while (!_kbhit());
        tecla = _getch();

        if (vivo) mapa[jugadory][jugadorx] = ' ';

        char movimiento = tecla;

        switch (tecla) {
        case 'w': jugadory--; vida -= 0.5f; break;
        case 'a': jugadorx--; vida -= 0.5f; break;
        case 's': jugadory++; vida -= 0.5f; break;
        case 'd': jugadorx++; vida -= 0.5f; break;

        case 'i': jugadory -= 2; vida -= 1.5f; break;
        case 'j': jugadorx -= 2; vida -= 1.5f; break;
        case 'k': jugadory += 2; vida -= 1.5f; break;
        case 'l': jugadorx += 2; vida -= 1.5f; break;

        case 'g':

            if (bomba > 0) { sound2.play(); }
            explotarBomba();
            

            if (bomba < 0) {
                bomba = 0;
            }
            break;

        }

        // Verificar colisión con paredes ('C')
        if (jugadory >= 0 && jugadory < largo && jugadorx >= 0 && jugadorx < ancho) {
            if (mapa[jugadory][jugadorx] == 'C' || mapa[jugadory][jugadorx] == 'P') {
                switch (movimiento) {
                case 'w': jugadory++; break;
                case 'a': jugadorx++; break;
                case 's': jugadory--; break;
                case 'd': jugadorx--; break;
                case 'i': jugadory += 2; break;
                case 'j': jugadorx += 2; break;
                case 'k': jugadory -= 2; break;
                case 'l': jugadorx -= 2; break;
                }
            }
        }

        // Activar lava en posición específica
        if (jugadory == 3 && jugadorx == 115) {
            mapa[4][115] = 'A';
        }
    }

    void vidaRobot() {
        if (!vivo) return;

        if (mapa[jugadory][jugadorx] == 'v') {

            sound3.play();

            vida += (vidaTotal * 15) / 100.0f;
            vidasRestantes--;
        }
        if (mapa[jugadory][jugadorx] == 'V') {

            sound3.play();

            vida += (vidaTotal * 20) / 100.0f;
            vidasRestantes--;
        }
        if (vida > 100) vida = 100;
    }

    bool muerte() {
        if (vida <= 0) {
            vivo = false;
            system("cls");
			//mostrarMapa(); No hace falta mostrar el mapa muerto
            animacionMuerte();
            return true;
        }
        return false;
    }

    bool muerteQuemao() {
        if (!vivo) return false;
        if (jugadory >= 0 && jugadory < largo && jugadorx >= 0 && jugadorx < ancho) {
            if (mapa[jugadory][jugadorx] == 'A') {
                
                sound4.play();
                system("cls");

				//No hace falta mostrar el mapa muerto
                //mapa[jugadory][jugadorx] = 'A';
                //mostrarMapa();

                cout << "GAME OVER! Has caído en la lava\n";
                Sleep(100);
                animacionMuerte();
                return true;
               
            }
        }
        return false;

    }

    void inventario() {
        if (!vivo) return;

        if (mapa[jugadory][jugadorx] == 'B') {

            sound3.play();

            bomba++;
            mapa[jugadory][jugadorx] = ' ';
        }
        if (mapa[jugadory][jugadorx] == 'M') {

            sound3.play();

            tesoro++;
            tesoroRestante--;
            mapa[jugadory][jugadorx] = ' ';
        }


    }
    


    void explotarBomba() {
        if (bomba >= 1) {

            for (int i = jugadory - 3; i <= jugadory + 3; i++) {
                for (int j = jugadorx - 3; j <= jugadorx + 3; j++) {
                    if (i >= 0 && i < largo && j >= 0 && j < ancho) {
                        if (mapa[i][j] == 'P') {
                            mapa[i][j] = ' ';
                        }
                    }
                }
            }
            bomba--;

            system("cls");
            mostrarMapa();
            Sleep(300);
        }
    }


};

int main() {

    // Cargar música del menú
    if (!buffer5.loadFromFile("inicio.wav")) {
        cerr << "Error: No se pudo cargar inicio.wav" << endl;
        return -1;
    }
    sound5.setLooping(true);
    sound5.play();

    // BUCLE DEL MENÚ PRINCIPAL
    while (true) {
        system("cls");  // Limpiar pantalla ANTES de mostrar menú

        
        cout << "1. JUGAR\n";
        cout << "2. GUARDAR PARTIDA\n";
        cout << "3. CARGAR PARTIDA\n";
        cout << "4. SALIR\n\n";
        cout << "Selecciona una opcion: ";

        int opcion;
        cin >> opcion;
        

        switch (opcion) {
        case 1: {  
            sound5.stop();  // Detener música del menú
            setupConsole();

            // Cargar recursos de audio (con validación)
            if (!buffer1.loadFromFile("1-11. Route 101_.mp3")) {
                cout << ROJO << "Error al cargar musica de fondo" << RESET << endl;
                _getch();
                break;  // Volver al menú
            }
            if (!buffer2.loadFromFile("explosion-80108.wav")) {
                cout << ROJO << "Error al cargar sonido de explosion" << RESET << endl;
                _getch();
                break;
            }
            if (!buffer3.loadFromFile("objeto.wav")) {
                cout << ROJO << "Error al cargar sonido de objeto" << RESET << endl;
                _getch();
                break;
            }
            if (!buffer4.loadFromFile("quick_fart_x.wav")) {
                cout << ROJO << "Error al cargar sonido de lava" << RESET << endl;
                _getch();
                break;
            }

            
            Robot robot(true, 2, 2, 100.0f, 100.0f, 2, 3, 0, 4, 0, 0);
            robot.matriz();

            sound1.play();
            sound1.setLooping(true);

            
            bool partidaActiva = true;
            while (partidaActiva) {
                system("cls");
                robot.mostrarMapa();
                robot.movimiento();
                robot.vidaRobot();
                robot.inventario();

                // Verificar muerte por lava
                if (robot.muerteQuemao()) {
                    partidaActiva = false;
                    continue;
                }

                // Verificar muerte por vida agotada
                if (robot.muerte()) {
                    partidaActiva = false;
                    continue;
                }

                // Verificar victoria (3 tesoros recolectados)
                if (robot.tesoro >= 3) {
                    robot.animacionVictoria();
                    partidaActiva = false;
                    continue;
                }

                Sleep(10);
            }

            sound1.stop();  
            break;
        }  

        case 4: {  
            sound5.stop();
            cout << "\n¡Gracias por jugar!\n";
            Sleep(1000);
            return 0;  // Salir del programa
        }

        default: {
            cout << ROJO << "\nOpción no válida. Presiona una tecla para continuar..." << RESET;
            _getch();
        break;

        }
        }
    }

    return 0;
}