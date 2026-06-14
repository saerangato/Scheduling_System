#include "../include/schedule_engine.hpp"
#include "../include/course.hpp"
#include "../include/space.hpp"
#include "../include/instructor.hpp"
#include "../include/full_time_professor.hpp"
#include "../include/occasional_lecturer.hpp"
#include "../include/classroom.hpp"
#include "../include/laboratory.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <fstream> 
#include <string>

using namespace std;

// ══════════════════════════════════════════════════════════
// Load data
// ══════════════════════════════════════════════════════════
// Split CSV without using a vector
// Returns a dynamic array; writes the quantity to out_count
static std::string* split_csv(const std::string& line, int& out_count) {
    out_count = 1;
    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == ',') out_count++; 
    }

    std::string* tokens = new std::string[out_count];
    int index = 0;
    std::string current = "";

    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == ',') {
            tokens[index++] = current;
            current = "";
        } else {
            current += line[i];
        }
    }
    tokens[index] = current; // last token after the last comma

    return tokens;
}

// ══════════════════════════════════════════════════════════
// Constructor & Destructor
// ══════════════════════════════════════════════════════════
schedule_engine::schedule_engine()
    : instructors_array(nullptr),
        spaces_array(nullptr),
        courses_array(nullptr),
        num_instructors(0),
        num_spaces(0),
        num_courses(0) {}

schedule_engine::~schedule_engine() {
    for (int i = 0; i < num_instructors; i++) {
        delete instructors_array[i];
    }
    delete[] instructors_array;

    for (int i = 0; i < num_spaces; i++) {
        delete spaces_array[i];
    }
    delete[] spaces_array;

    delete[] courses_array;
}

// ══════════════════════════════════════════════════════════
// LOAD INSTRUCTORS
// Expected CSV format: type,name,payroll,department
// ══════════════════════════════════════════════════════════
void schedule_engine::load_instructors(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }

    std::string line;
    std::getline(file, line); 

    int count = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) count++;
    }

    file.clear();
    file.seekg(0);
    std::getline(file, line); 

    if (instructors_array != nullptr) {
        for (int i = 0; i < num_instructors; i++) {
            delete instructors_array[i];
        }
        delete[] instructors_array;
        instructors_array = nullptr;
    }

    instructors_array = new instructor*[count];
    num_instructors = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        int token_count = 0;
        std::string* tokens = split_csv(line, token_count);

        if (token_count < 4) {
            std::cerr << "[load_instructors] Línea malformada, se omite: " << line << "\n";
            delete[] tokens;
            continue;
        }

        std::string type       = tokens[0];
        std::string name       = tokens[1];
        std::string payroll    = tokens[2];
        std::string department = tokens[3];

        delete[] tokens;

        if (type == "full_time") {
            instructors_array[num_instructors++] = new full_time_professor(name, payroll, department);
        } else if (type == "occasional") {
            instructors_array[num_instructors++] = new occasional_lecturer(name, payroll, department);
        } else {
            std::cerr << "[load_instructors] Tipo desconocido ignorado: " << type << "\n";
        }
    }

    file.close();
    std::cout << "[load_instructors] Instructores cargados: " << num_instructors << "\n";
}

// ══════════════════════════════════════════════════════════
// LOAD SPACES
// Expected CSV format: type,building,room,capacity,equipment
// ══════════════════════════════════════════════════════════
void schedule_engine::load_spaces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }

    std::string line;
    std::getline(file, line);

    int count = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) count++;
    }

    file.clear();
    file.seekg(0);
    std::getline(file, line); 

    if (spaces_array != nullptr) {
        for (int i = 0; i < num_spaces; i++) {
            delete spaces_array[i];
        }
        delete[] spaces_array;
        spaces_array = nullptr;
    }

    spaces_array = new space*[count];
    num_spaces = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        int token_count = 0;
        std::string* tokens = split_csv(line, token_count);

        if (token_count < 4) {
            std::cerr << "[load_spaces] Línea malformada, se omite: " << line << "\n";
            delete[] tokens;
            continue;
        }

        std::string type      = tokens[0];
        std::string building  = tokens[1];
        int room              = std::stoi(tokens[2]);
        int capacity          = std::stoi(tokens[3]);

        std::string equipment = (token_count >= 5) ? tokens[4] : "";

        delete[] tokens;

        if (type == "classroom") {
            spaces_array[num_spaces++] = new classroom(building, room, capacity);
        } else if (type == "laboratory") {
            // laboratory espera std::string* para el equipo
            std::string* eq_ptr = equipment.empty() ? nullptr : new std::string(equipment);
            spaces_array[num_spaces++] = new laboratory(building, room, capacity, eq_ptr);
        } else {
            std::cerr << "[load_spaces] Tipo desconocido ignorado: " << type << "\n";
        }
    }

    file.close();
    std::cout << "[load_spaces] Espacios cargados: " << num_spaces << "\n";
}

// ══════════════════════════════════════════════════════════
// LOAD COURSES
// Expected CSV format: 
// code,name,department,students,day,start_hour,end_hour
// ══════════════════════════════════════════════════════════
void schedule_engine::load_courses(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    }

    std::string line;
    std::getline(file, line); 

    int count = 0;
    while (std::getline(file, line)) {
        if (!line.empty()) count++;
    }

    file.clear();
    file.seekg(0);
    std::getline(file, line);

    if (courses_array != nullptr) {
        delete[] courses_array;
        courses_array = nullptr;
    }

    courses_array = new course[count];
    num_courses = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        int token_count = 0;
        std::string* tokens = split_csv(line, token_count);

        if (token_count < 7) {
            std::cerr << "[load_courses] Línea malformada, se omite: " << line << "\n";
            delete[] tokens;
            continue;
        }

        std::string code       = tokens[0];
        std::string name       = tokens[1];
        std::string department = tokens[2];
        int students           = std::stoi(tokens[3]);
        std::string day        = tokens[4];
        int start_hour         = std::stoi(tokens[5]);
        int end_hour           = std::stoi(tokens[6]);

        delete[] tokens;

        schedule sched(day, start_hour, end_hour);
        courses_array[num_courses++] = course(code, name, department, students, sched);
    }

    file.close();
    std::cout << "[load_courses] Cursos cargados: " << num_courses << "\n";
}

// ══════════════════════════════════════════════════════════
// Functions
// ══════════════════════════════════════════════════════════
bool schedule_engine::room_assignment(course* cour, space* spac) {
    
    // Validate capacity
    if (cour->get_enrollment() > spac->get_max_seating_capacity()) {
        cout << "Error: Hay mas alumnos que sillas." << endl;
        return false; 
    }

    // Check for conflicts
    for (int i = 0; i < num_courses; i++) {
        course* otro = &courses_array[i];
        
        bool mismo_salon = (otro->get_assigned_space() == spac);
        bool mismo_dia = (otro->get_course_day() == cour->get_course_day());

        if (mismo_salon && mismo_dia) {
            // Usando los nombres de funciones que salen en tu archivo
            bool choca_inicio = (cour->get_start_hour() < otro->get_end_hour());
            bool choca_fin = (cour->get_end_hour() > otro->get_start_hour());

            if (choca_inicio && choca_fin) {
                cout << "Error: Este salon ya esta ocupado." << endl;
                return false; 
            }
        }
    }

    cour->assign_space(spac);
    cout << "Exito: Salon asignado." << endl;
    return true;
}


bool schedule_engine::lecturer_limit_classes() {
    for (int i = 0; i < num_instructors; i++) {
        // Le preguntamos directo al instructor si ya se pasó de su límite
        if (instructors_array[i]->exceeds_maximum_courses()) {
            cout << "Error: Un profesor de catedra excede el maximo de 3 clases." << endl;
            return false;
        }
    }
    return true;
}

bool schedule_engine::exit_program() {
    bool can_exit = true; 

    for (int i = 0; i < num_instructors; i++) {
        // Le preguntamos directo al instructor si NO cumple con su mínimo
        if (!instructors_array[i]->meets_minimum_courses()) {
            cout << "Error al salir: Un profesor de planta tiene menos de 2 clases asignadas." << endl;
            can_exit = false; 
        }
    }

    if (can_exit) {
        cout << "Obligaciones del contrato cumplidas. Cerrando sistema" << endl;
    }
    
    return can_exit;
}