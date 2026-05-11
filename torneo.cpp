#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Equipo {
    string nombre;
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int puntos;
};

int totalEquipos = 16;
const int MAX_EQUIPOS = 20; // 16 originales + max 4 nuevos

// Reconstruye partidosEmpatados y partidosPerdidos a partir de los datos disponibles
void reconstruirDatos(Equipo equipos[], int n) {
    for (int i = 0; i < n; i++) {
        // puntos = 3*G + 1*E  =>  E = puntos - 3*G
        equipos[i].partidosEmpatados = equipos[i].puntos - 3 * equipos[i].partidosGanados;
        // jugados = G + E + P  =>  P = jugados - G - E
        equipos[i].partidosPerdidos = equipos[i].partidosJugados
                                     - equipos[i].partidosGanados
                                     - equipos[i].partidosEmpatados;
    }
}

// Imprime encabezado de tabla
void imprimirEncabezado() {
    cout << left
         << setw(25) << "Equipo"
         << setw(5)  << "PJ"
         << setw(5)  << "PG"
         << setw(5)  << "PE"
         << setw(5)  << "PP"
         << setw(6)  << "PTS"
         << endl;
    cout << string(51, '-') << endl;
}

// Imprime una fila de la tabla
void imprimirFila(const Equipo& e, int pos) {
    cout << left
         << setw(3)  << pos
         << setw(22) << e.nombre
         << setw(5)  << e.partidosJugados
         << setw(5)  << e.partidosGanados
         << setw(5)  << e.partidosEmpatados
         << setw(5)  << e.partidosPerdidos
         << setw(6)  << e.puntos
         << endl;
}

// Opcion 1: tabla de mayor a menor por puntos
void mostrarMayorAMenor(Equipo equipos[], int n) {
    Equipo temp[MAX_EQUIPOS];
    for (int i = 0; i < n; i++) temp[i] = equipos[i];

    // Burbuja descendente
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j].puntos < temp[j+1].puntos)
                swap(temp[j], temp[j+1]);

    cout << "\n=== TABLA DE POSICIONES (Mayor a Menor) ===" << endl;
    cout << left << setw(3) << "#";
    imprimirEncabezado();
    for (int i = 0; i < n; i++)
        imprimirFila(temp[i], i + 1);
}

// Opcion 2: tabla de menor a mayor por puntos
void mostrarMenorAMayor(Equipo equipos[], int n) {
    Equipo temp[MAX_EQUIPOS];
    for (int i = 0; i < n; i++) temp[i] = equipos[i];

    // Burbuja ascendente
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (temp[j].puntos > temp[j+1].puntos)
                swap(temp[j], temp[j+1]);

    cout << "\n=== TABLA DE POSICIONES (Menor a Mayor) ===" << endl;
    cout << left << setw(3) << "#";
    imprimirEncabezado();
    for (int i = 0; i < n; i++)
        imprimirFila(temp[i], i + 1);
}

// Opcion 3: equipo con mas empates
void mostrarMasEmpates(Equipo equipos[], int n) {
    int idx = 0;
    for (int i = 1; i < n; i++)
        if (equipos[i].partidosEmpatados > equipos[idx].partidosEmpatados)
            idx = i;

    cout << "\n=== EQUIPO CON MAS EMPATES ===" << endl;
    cout << left << setw(3) << "#";
    imprimirEncabezado();
    imprimirFila(equipos[idx], idx + 1);
}

// Opcion 4: buscar equipo por nombre
void buscarEquipo(Equipo equipos[], int n) {
    string nombre;
    cout << "\nIngrese el nombre del equipo: ";
    cin.ignore();
    getline(cin, nombre);

    bool encontrado = false;
    for (int i = 0; i < n; i++) {
        // Comparacion sin distinguir mayusculas/minusculas
        string a = equipos[i].nombre, b = nombre;
        for (char& c : a) c = tolower(c);
        for (char& c : b) c = tolower(c);

        if (a == b) {
            cout << "\n=== INFORMACION DEL EQUIPO ===" << endl;
            cout << left << setw(3) << "#";
            imprimirEncabezado();
            imprimirFila(equipos[i], i + 1);
            encontrado = true;
            break;
        }
    }
    if (!encontrado)
        cout << "Equipo no encontrado." << endl;
}

// Verifica consistencia de datos de un equipo nuevo
bool verificarConsistencia(const Equipo& e) {
    int puntosEsperados = 3 * e.partidosGanados + e.partidosEmpatados;
    int jugadosEsperados = e.partidosGanados + e.partidosEmpatados + e.partidosPerdidos;

    if (e.puntos != puntosEsperados) {
        cout << "ERROR: Los puntos (" << e.puntos << ") no coinciden con "
             << "3xG + 1xE = " << puntosEsperados << endl;
        return false;
    }
    if (e.partidosJugados != jugadosEsperados) {
        cout << "ERROR: Partidos jugados (" << e.partidosJugados << ") no coinciden con "
             << "G+E+P = " << jugadosEsperados << endl;
        return false;
    }
    return true;
}

// Opcion 5: agregar nuevo equipo
void agregarEquipo(Equipo equipos[], int& n) {
    if (n >= MAX_EQUIPOS) {
        cout << "No se pueden agregar mas equipos (maximo 4 nuevos alcanzado)." << endl;
        return;
    }

    Equipo nuevo;
    cout << "\n=== AGREGAR NUEVO EQUIPO ===" << endl;
    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nuevo.nombre);
    cout << "Partidos jugados: ";   cin >> nuevo.partidosJugados;
    cout << "Partidos ganados: ";   cin >> nuevo.partidosGanados;
    cout << "Partidos empatados: "; cin >> nuevo.partidosEmpatados;
    cout << "Partidos perdidos: ";  cin >> nuevo.partidosPerdidos;
    cout << "Puntos: ";             cin >> nuevo.puntos;

    if (verificarConsistencia(nuevo)) {
        equipos[n++] = nuevo;
        cout << "Equipo agregado exitosamente." << endl;
    } else {
        cout << "ADVERTENCIA: Datos inconsistentes. El equipo NO fue guardado." << endl;
    }
}

int main() {
    Equipo equipos[MAX_EQUIPOS] = {
        {"Andromeda FC",           12, 4, 0, 0, 13},
        {"Vulcano Academia",       11, 2, 0, 0, 10},
        {"Orion Confederacion",    11, 4, 0, 0, 14},
        {"Sirio Estrellas",        10, 6, 0, 0, 20},
        {"Caronte Titanes",        11, 1, 0, 0,  6},
        {"Quiron Cometas",         10, 5, 0, 0, 17},
        {"Pegaso Pulsares",        11, 7, 0, 0, 24},
        {"Osos Cosmicos",          11, 5, 0, 0, 18},
        {"Via Lactea Nomadas",     11, 6, 0, 0, 20},
        {"Leonidas FC",            11, 5, 0, 0, 16},
        {"Cangrejo Fortaleza",     11, 4, 0, 0, 16},
        {"Cefeo Cumulo",           11, 3, 0, 0, 14},
        {"Atletico Interestelar",  11, 4, 0, 0, 16},
        {"Deportivo Galactico",    11, 2, 0, 0,  8},
        {"Estrella Estelar",       11, 5, 0, 0, 17},
        {"Inter Galaxia",          10, 2, 0, 0, 10}
    };

    reconstruirDatos(equipos, totalEquipos);

    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "  TORNEO INTERGALACTICO DE FUTBOL" << endl;
        cout << "========================================" << endl;
        cout << "1. Tabla de posiciones (mayor a menor)" << endl;
        cout << "2. Tabla de posiciones (menor a mayor)" << endl;
        cout << "3. Equipo con mas empates"              << endl;
        cout << "4. Buscar equipo por nombre"            << endl;
        cout << "5. Agregar nuevo equipo"                << endl;
        cout << "0. Salir"                               << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: mostrarMayorAMenor(equipos, totalEquipos); break;
            case 2: mostrarMenorAMayor(equipos, totalEquipos); break;
            case 3: mostrarMasEmpates(equipos, totalEquipos);  break;
            case 4: buscarEquipo(equipos, totalEquipos);       break;
            case 5: agregarEquipo(equipos, totalEquipos);      break;
            case 0: cout << "Hasta luego!" << endl;            break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}