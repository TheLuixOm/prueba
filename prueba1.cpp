#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

class Usuario {
public:
    string cedula;
    string nombre;
    string direccion;
    string telefono;

    Usuario(string c, string n, string d, string t) : cedula(c), nombre(n), direccion(d), telefono(t) {}
};

class Vehiculo {
public:
    string placa;
    string modelo;
    string marca;
    int anio;
    string chofer;
    string sector_actual;
    bool disponible;

    Vehiculo(string p, string m, string ma, int a, string c) : placa(p), modelo(m), marca(ma), anio(a), chofer(c), disponible(true) {}
};

class Sector {
public:
    string id;
    string nombre;

    Sector(string i, string n) : id(i), nombre(n) {}
};

vector<Usuario> usuarios;
vector<Vehiculo> vehiculos;
vector<Sector> sectores;

void agregarUsuario() {
    string cedula, nombre, direccion, telefono;
    cout << "Ingrese cedula del usuario: "; cin >> cedula;
    cout << "Ingrese nombre del usuario: "; cin >> nombre;
    cout << "Ingrese dirección del usuario: "; cin >> direccion;
    cout << "Ingrese telefono del usuario: "; cin >> telefono;
    usuarios.push_back(Usuario(cedula, nombre, direccion, telefono));
    cout << "Usuario agregado exitosamente.\n";
}

void agregarVehiculo() {
    string placa, modelo, marca, chofer;
    int anio;
    cout << "Ingrese placa del vehiculo: "; cin >> placa;
    cout << "Ingrese modelo del vehiculo: "; cin >> modelo;
    cout << "Ingrese marca del vehiculo: "; cin >> marca;
    cout << "Ingrese anio del vehiculo: "; cin >> anio;
    cout << "Ingrese nombre del chofer: "; cin >> chofer;
    vehiculos.push_back(Vehiculo(placa, modelo, marca, anio, chofer));
    cout << "Vehiculo agregado exitosamente.\n";
}

void agregarSector() {
    string id, nombre;
    cout << "Ingrese ID del sector: "; cin >> id;
    cout << "Ingrese nombre del sector: "; cin >> nombre;
    sectores.push_back(Sector(id, nombre));
    cout << "Sector agregado exitosamente.\n";
}

void mostrarVehiculosDisponibles(string sectorID) {
    cout << "Vehiculos disponibles en el sector " << sectorID << ":\n";
    
    // Usamos un bucle tradicional en lugar de un bucle basado en rangos
    for (size_t i = 0; i < vehiculos.size(); ++i) {
        if (vehiculos[i].sector_actual == sectorID && vehiculos[i].disponible) {
            cout << "Placa: " << vehiculos[i].placa 
                 << ", Modelo: " << vehiculos[i].modelo 
                 << ", Marca: " << vehiculos[i].marca 
                 << ", Anio: " << vehiculos[i].anio 
                 << ", Chofer: " << vehiculos[i].chofer << "\n";
        }
    }
}


void actualizarUbicacion() {
    string placa, sectorID;
    cout << "Ingrese la placa del vehiculo: "; 
    cin >> placa;
    cout << "Ingrese el ID del sector actual: "; 
    cin >> sectorID;

    // Usamos un bucle tradicional en lugar de un bucle basado en rangos
    for (size_t i = 0; i < vehiculos.size(); ++i) {
        if (vehiculos[i].placa == placa) {
            vehiculos[i].sector_actual = sectorID;
            cout << "Ubicacion del vehiculo actualizada.\n";
            return;
        }
    }
    cout << "Vehículo no encontrado.\n";
}


void solicitarTraslado() {
    string cedula, sector_origen, sector_destino;
    cout << "Ingrese la cédula del usuario: "; 
    cin >> cedula;
    cout << "Ingrese ID del sector origen: "; 
    cin >> sector_origen;
    cout << "Ingrese ID del sector destino: "; 
    cin >> sector_destino;

    mostrarVehiculosDisponibles(sector_origen);

    string placa;
    cout << "Ingrese la placa del vehiculo seleccionado: "; 
    cin >> placa;

    // Usamos un bucle tradicional en lugar de un bucle basado en rangos
    for (size_t i = 0; i < vehiculos.size(); ++i) {
        if (vehiculos[i].placa == placa && vehiculos[i].disponible) {
            vehiculos[i].disponible = false;
            vehiculos[i].sector_actual = sector_destino;
            cout << "Traslado en proceso...\n";
            return;
        }
    }

    cout << "Vehiculo no disponible o no encontrado.\n";
}


void finalizarTraslado() {
    string placa;
    cout << "Ingrese la placa del vehiculo que finalizo el traslado: "; 
    cin >> placa;
    
    // Usamos un bucle tradicional en lugar de un bucle basado en rangos
    for (size_t i = 0; i < vehiculos.size(); ++i) {
        if (vehiculos[i].placa == placa) {
            vehiculos[i].disponible = true;
            cout << "Traslado finalizado y vehiculo disponible nuevamente.\n";
            return;
        }
    }
    cout << "Vehículo no encontrado.\n";
}


void generarReporte() {
    ofstream archivo("reporte.txt");
    if (archivo.is_open()) {
        archivo << "Reporte de traslados del dia:\n";
        archivo << "Usuarios y vehiculos mas frecuentes.\n";
        archivo.close();
        cout << "Reporte generado exitosamente.\n";
    } else {
        cout << "No se pudo generar el reporte.\n";
    }
}

void subMenuGestion() {
    int opcion;
    do {
        cout << "Submenu de Gestion:\n";
        cout << "1. Agregar Usuario\n";
        cout << "2. Agregar Vehículo\n";
        cout << "3. Agregar Sector\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarUsuario(); break;
            case 2: agregarVehiculo(); break;
            case 3: agregarSector(); break;
            case 4: break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 4);
}

void subMenuServicioDiario() {
    int opcion;
    do {
        cout << "Submenu de Servicio Diario:\n";
        cout << "1. Actualizar Ubicacion de Vehiculo\n";
        cout << "2. Solicitar Traslado\n";
        cout << "3. Finalizar Traslado\n";
        cout << "4. Generar Reporte\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: actualizarUbicacion(); break;
            case 2: solicitarTraslado(); break;
            case 3: finalizarTraslado(); break;
            case 4: generarReporte(); break;
            case 5: break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 5);
}

int main() {
    srand(time(0)); // Inicializar random

    int opcion;
    do {
        cout << "Menú Principal:\n";
        cout << "1. Gestion\n";
        cout << "2. Servicio Diario\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: subMenuGestion(); break;
            case 2: subMenuServicioDiario(); break;
            case 3: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 3);

    return 0;
}

