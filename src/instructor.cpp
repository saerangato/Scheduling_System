#include "../include/instructor.hpp"

// constructor por defecto
instructor::instructor() {
    name = "";
    payroll_numbers = "";
    department = "";
}

// constructor con parámetros
instructor::instructor(std::string n, std::string pnum, std::string dep) {
    name = n;
    payroll_numbers = pnum;
    department = dep;
}

// destructor virtual (vacío, pero necesario para el polimorfismo)
instructor::~instructor() {}

// getters y setters 

void instructor::set_name(std::string n) {
    name = n;
}

std::string instructor::get_name() {
    return name;
}

void instructor::set_payroll_numbers(std::string pnum) {
    payroll_numbers = pnum;
}

std::string instructor::get_payroll_numbers() {
    return payroll_numbers;
}

void instructor::set_department(std::string dep) {
    department = dep;
}

std::string instructor::get_department() {
    return department;
}

// sobrecarga de operadores 

bool instructor::operator==(const instructor& other) {
    // dos instructores son iguales si tienen el mismo numero de nomina
    return this->payroll_numbers == other.payroll_numbers;
}

bool instructor::operator<(const instructor& other) {
    // logica basica para que el motor de horarios la expanda
    // un profe ocasional es "menor que" un profes de tiempo completo
    return false; // placeholder simple
}

bool instructor::operator>(const instructor& other) {
    // igual que el operador < pero a la inversa
    return false; // placeholder simple
}