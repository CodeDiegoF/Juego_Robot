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
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>

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
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

SoundBuffer buffer1, buffer2, buffer3, buffer4, buffer5, buffer6, buffer7, buffer8;
Sound sound1(buffer1), sound2(buffer2), sound3(buffer3), sound4(buffer4), sound5(buffer5), sound6(buffer6), sound7(buffer7), sound8(buffer8);

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
        vivo = v;
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

    void guardarPartida(const string& mapaGuardado);
    void cargarPartida(const string& cargarMapa);

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

        char muerte[5][83] = {
            {'0','0','1','1','1','0','0','0','0','1','0','0','0','0','0','1','0','1','0','0','0','0','1','1','0','0','t','0','1','1','1','0','0','0','1','0','0','0','1','0','0','0','1','1','0','0','1','1','0','0','0'},
            {'0','1','0','0','0','0','0','0','1','1','1','0','0','0','0','1','1','1','0','0','0','1','0','0','0','0','t','1','0','1','0','1','0','0','1','0','0','0','1','0','0','1','0','0','0','0','1','0','1','0','0'},
            {'0','1','0','1','1','1','0','0','1','0','1','0','0','0','1','0','1','0','1','0','0','1','1','1','0','0','t','1','1','0','1','1','0','0','0','1','0','1','0','0','0','1','1','1','0','0','1','0','1','0','0'},
            {'0','1','0','0','1','0','0','1','1','0','1','1','0','0','1','0','1','0','1','0','0','1','0','0','0','0','t','1','0','1','0','1','0','0','0','1','0','1','0','0','0','1','0','0','0','0','1','1','1','0','0'},
            {'0','0','1','1','1','0','0','1','0','0','0','1','0','0','1','0','1','0','1','0','0','0','1','1','0','0','t','0','1','1','1','0','0','0','0','0','1','0','0','0','0','0','1','1','0','0','1','0','0','1','0'}
        };

        bool salir = false;
        int contador = 0;

        while (!salir && contador < 10) {
            system("cls");
            cout << ROJO << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            for (int i = 0; i < 5; i++) {
                cout << "\t\t\t\t\t\t\t\t\t\t";
                for (int j = 0; j < 83; j++) {
                    if (muerte[i][j] == 't') {
                        printf("\t");
                    }
                    else if (muerte[i][j] == '1') {
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

            if (_kbhit()) {
                _getch();
                sound5.play();
                sound5.setLooping(true);
                salir = true;
            }

            Sleep(200);
            contador++;
        }
    }

    // ANIMACION VICTORIA
    void animacionVictoria() {
        sound1.stop();

        Music buffer;
        if (!buffer.openFromFile("victoria.wav")) {
            cout << "Error al cargar musica!" << endl;
        }
        else {
            buffer.play();
            buffer.setLooping(true);
        }

        char victoria[6][83] = {
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

            for (int i = 0; i < 6; i++) {
                cout << "\t\t\t\t\t\t\t\t\t\t";
                for (int j = 0; j < 83; j++) {
                    if (victoria[i][j] == 't') {
                        printf("\t");
                    }
                    else if (victoria[i][j] == '1') {
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

            if (_kbhit()) {
                _getch();
                sound5.play();
                sound5.setLooping(true);
                salir = true;
            }

            Sleep(200);
            contador++;
        }
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

        cout << "Controles: w,a,s,d (mover) | i,j,k,l (saltar) | g (bomba) | q (guardar)\n";
        cout << RESET;
    }

    char movimiento() {
        char tecla = ' ';
        while (!_kbhit());
        tecla = _getch();

        if (tecla == 'q' || tecla == 'Q') {
            return 'q';
        }

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
            if (bomba < 0) bomba = 0;
            break;

        default:
            if (vivo) mapa[jugadory][jugadorx] = 'R';
            return tecla;
        }

        // Verificar colisión con paredes ('C' o 'P')
        if (jugadory >= 0 && jugadory < largo && jugadorx >= 0 && jugadorx < ancho) {
            if (mapa[jugadory][jugadorx] == 'C' || mapa[jugadory][jugadorx] == 'P') {
                sound8.play();
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

        return tecla;
    }

    void vidaRobot() {
        if (!vivo) return;

        if (mapa[jugadory][jugadorx] == 'v') {
            sound3.play();
            vida += (vidaTotal * 15) / 100.0f;
            vidasRestantes--;
            mapa[jugadory][jugadorx] = ' ';
        }
        if (mapa[jugadory][jugadorx] == 'V') {
            sound3.play();
            vida += (vidaTotal * 20) / 100.0f;
            vidasRestantes--;
            mapa[jugadory][jugadorx] = ' ';
        }
        if (vida > 100) vida = 100;
    }

    bool muerte() {
        if (vida <= 0) {
            vivo = false;
            system("cls");
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

// Implementación de guardar/cargar
void Robot::guardarPartida(const string& mapaGuardado) {
    ofstream archivo(mapaGuardado);
    if (!archivo.is_open()) {
        cout << ROJO << "Error al abrir el archivo para guardar: " << mapaGuardado << RESET << endl;
        return;
    }


    archivo << jugadorx << "\n";
    archivo << jugadory << "\n";
    archivo << vida << "\n";
    archivo << vidaTotal << "\n";
    archivo << bomba << "\n";
    archivo << tesoro << "\n";
    archivo << tesoroRestante << "\n";
    archivo << vidasRestantes << "\n";
    archivo << (vivo ? 1 : 0) << "\n";
    archivo << minutos << "\n";
    archivo << segundos << "\n";
    archivo << largo << "\n";
    archivo << ancho << "\n";

    for (int i = 0; i < largo; i++) {
        for (int j = 0; j < ancho; j++) {
            archivo << mapa[i][j];
        }
        archivo << "\n";
    }

    archivo.close();
    cout << VERDE << "Partida guardada en: " << mapaGuardado << RESET << endl;
}

void Robot::cargarPartida(const string& cargarMapa) {
    ifstream archivo(cargarMapa);
    if (!archivo.is_open()) {
        cout << ROJO << "Error al abrir el archivo para cargar: " << cargarMapa << RESET << endl;
        return;
    }

    archivo >> jugadorx;
    archivo >> jugadory;
    archivo >> vida;
    archivo >> vidaTotal;
    archivo >> bomba;
    archivo >> tesoro;
    archivo >> tesoroRestante;
    archivo >> vidasRestantes;

    int vivoInt;
    archivo >> vivoInt;
    vivo = (vivoInt == 1);

    archivo >> minutos;
    archivo >> segundos;
    archivo >> largo;
    archivo >> ancho;

    string linea;
    getline(archivo, linea); // consumir salto tras 'ancho'

    for (int i = 0; i < largo; i++) {
        getline(archivo, linea);
        for (int j = 0; j < ancho; j++) {
            if (j < (int)linea.size()) {
                mapa[i][j] = linea[j];
            }
            else {
                mapa[i][j] = ' ';
            }
        }
    }

    archivo.close();
    cout << VERDE << "Partida cargada desde: " << cargarMapa << RESET << endl;
}

// ==================== MAIN ====================
int main() {
    // Cargar música del menú
    if (!buffer5.loadFromFile("inicio.wav")) {
        cerr << "Error: No se pudo cargar inicio.wav" << endl;
        return -1;
    }
    sound5.setBuffer(buffer5);
    sound5.setLooping(true);
    sound5.play();

    // BUCLE DEL MENÚ PRINCIPAL
    while (true) {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\t1. JUGAR\n";
        cout << "\t\t\t\t\t\t\t\t\t\t2. ESTADISTICAS\n";
        cout << "\t\t\t\t\t\t\t\t\t\t3. CARGAR PARTIDA\n";
        cout << "\t\t\t\t\t\t\t\t\t\t4. SALIR\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\tSelecciona una opcion: ";

        int opcion;
        cin >> opcion;

        switch (opcion) {
        case 1: {
            sound5.stop();
            setupConsole();

            // Cargar sonidos
            bool ok = true;
            if (!buffer1.loadFromFile("1-11. Route 101_.mp3")) { cout << ROJO << "Error al cargar musica de fondo" << RESET << endl; ok = false; }
            if (!buffer2.loadFromFile("explosion-80108.wav")) { cout << ROJO << "Error al cargar sonido de explosion" << RESET << endl; ok = false; }
            if (!buffer3.loadFromFile("objeto.wav")) { cout << ROJO << "Error al cargar sonido de objeto" << RESET << endl; ok = false; }
            if (!buffer4.loadFromFile("quick_fart_x.wav")) { cout << ROJO << "Error al cargar sonido de lava" << RESET << endl; ok = false; }
            if (!buffer8.loadFromFile("bonk.mp3")) { cout << ROJO << "Error al cargar sonido de colisión" << RESET << endl; ok = false; }

            if (!ok) {
                _getch();
                break;
            }

            // Asignar buffers a los sonidos
            sound1.setBuffer(buffer1);
            sound2.setBuffer(buffer2);
            sound3.setBuffer(buffer3);
            sound4.setBuffer(buffer4);
            sound8.setBuffer(buffer8);

            Robot robot(true, 2, 2, 100.0f, 100.0f, 0, 3, 0, 4, 0, 0);
            robot.matriz();

            sound1.setLooping(true);
            sound1.play();

            bool partidaActiva = true;
            while (partidaActiva) {
                system("cls");
                robot.mostrarMapa();
                char tecla = robot.movimiento();

                if (tecla == 'q' || tecla == 'Q') {
                    robot.guardarPartida("partida_guardada.txt");
                    cout << "\nPartida guardada. Presiona cualquier tecla para continuar...\n";
                    _getch();
                    continue;
                }

                robot.vidaRobot();
                robot.inventario();

                if (robot.muerteQuemao() || robot.muerte()) {
                    partidaActiva = false;
                    continue;
                }

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

        case 2: {
            
        }

        case 3: {
            sound5.stop();
            setupConsole();

            // Cargar sonidos
            bool ok = true;
            if (!buffer1.loadFromFile("1-11. Route 101_.mp3")) { ok = false; }
            if (!buffer2.loadFromFile("explosion-80108.wav")) { ok = false; }
            if (!buffer3.loadFromFile("objeto.wav")) { ok = false; }
            if (!buffer4.loadFromFile("quick_fart_x.wav")) { ok = false; }
            if (!buffer8.loadFromFile("bonk.mp3")) { ok = false; }

            if (!ok) {
                cout << ROJO << "Error al cargar recursos de audio." << RESET << endl;
                _getch();
                break;
            }

            sound1.setBuffer(buffer1);
            sound2.setBuffer(buffer2);
            sound3.setBuffer(buffer3);
            sound4.setBuffer(buffer4);
            sound8.setBuffer(buffer8);

            Robot robot(false, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            robot.cargarPartida("partida_guardada.txt");

            sound1.setLooping(true);
            sound1.play();

            bool partidaActiva = true;
            while (partidaActiva) {
                system("cls");
                robot.mostrarMapa();
                char tecla = robot.movimiento();

                if (tecla == 'q' || tecla == 'Q') {
                    robot.guardarPartida("partida_guardada.txt");
                    cout << "\nPartida guardada. Presiona cualquier tecla para continuar...\n";
                    _getch();
                    continue;
                }

                robot.vidaRobot();
                robot.inventario();

                if (robot.muerteQuemao() || robot.muerte()) {
                    partidaActiva = false;
                    continue;
                }

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
            return 0;
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