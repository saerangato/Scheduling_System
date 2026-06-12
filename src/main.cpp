#include <iostream>
// Incluye el header de tu motor
#include "../include/schedule_engine.hpp"

using namespace std;

int main() {
    // 1. Encender el motor
    schedule_engine motor;
    int opcion = 0;

    cout << "--- Sistema de Horarios Universitario ---" << endl;

    // 2. El bucle del CLI 
    while (true) {
        cout << "\nMenu Principal:" << endl;
        cout << "1. Simular asignacion de salon" << endl;
        cout << "2. Revisar limites de profesores" << endl;
        cout << "3. Salir del sistema" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Opcion en construccion por falta de tiempo..." << endl;
            // Aquí iría la llamada a motor.room_assignment() si tuvieran los objetos listos
        } 
        else if (opcion == 2) {
            motor.lecturer_limit_classes();
        } 
        else if (opcion == 3) {
            // Aquí entra en acción la regla estricta de salida que programamos
            if (motor.exit_program()) {
                break; // Rompe el ciclo y termina el programa correctamente
            }
        } 
        else {
            cout << "Opcion no valida." << endl;
        }
    }

    return 0;
}