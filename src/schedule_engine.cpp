#include "../include/schedule_engine.hpp"
#include "../include/course.hpp"
#include "../include/space.hpp"
#include "../include/instructor.hpp"
#include "../include/full_time_professor.hpp"
#include "../include/occasional_lecturer.hpp"
#include "../include/classroom.hpp"
#include "../include/laboratory.hpp"
#include "../include/schedule.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;

// ══════════════════════════════════════════════════════════
// Load data
// ══════════════════════════════════════════════════════════
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
    tokens[index] = current;

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
// HELPER: Check schedule overlap between two courses
// ══════════════════════════════════════════════════════════
bool schedule_engine::schedules_overlap(course& a, course& b) {
    if (a.get_course_day() != b.get_course_day()) return false;
    return a.get_start_hour() < b.get_end_hour() &&
            b.get_start_hour() < a.get_end_hour();
}

// ══════════════════════════════════════════════════════════
// LOAD INSTRUCTORS
// Expected CSV format: type,name,payroll,department
// ══════════════════════════════════════════════════════════
void schedule_engine::load_instructors(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
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
            std::cerr << "[Loading...] Malformed line, skipping: " << line << "\n";
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
            std::cerr << "[Loading...] Unknown type ignored: " << type << "\n";
        }
    }

    file.close();
    std::cout << "[Loading...] Instructors loaded: " << num_instructors << "\n";
}

// ══════════════════════════════════════════════════════════
// LOAD SPACES
// Expected CSV format: type,building,room,capacity,equipment
// ══════════════════════════════════════════════════════════
void schedule_engine::load_spaces(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
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
            std::cerr << "[Loading...] Malformed line, skipping: " << line << "\n";
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
            std::string* eq_ptr = equipment.empty() ? nullptr : new std::string(equipment);
            spaces_array[num_spaces++] = new laboratory(building, room, capacity, eq_ptr);
        } else {
            std::cerr << "[load_spaces] Unknown type ignored: " << type << "\n";
        }
    }

    file.close();
    std::cout << "[Loading...] Spaces loaded: " << num_spaces << "\n";
}

// ══════════════════════════════════════════════════════════
// LOAD COURSES
// Expected CSV format: 
// code,name,department,students,day,start_hour,end_hour
// ══════════════════════════════════════════════════════════
void schedule_engine::load_courses(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    std::getline(file, line); // skip header

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
            std::cerr << "[Loading...] Malformed line, skipping: " << line << "\n";
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
    std::cout << "[Loading...] Courses loaded: " << num_courses << "\n";
}

// ══════════════════════════════════════════════════════════
// Assign instructor to a course
// ══════════════════════════════════════════════════════════
void schedule_engine::assign_instructor_to_course() {
    std::cout << "\n--- Courses ---\n";
    for (int i = 0; i < num_courses; i++) {
        std::cout << i << ". " << courses_array[i].course_code
                    << " - " << courses_array[i].course_name;
        if (courses_array[i].get_instructor() != nullptr) {
            std::cout << " [Instructor: " << courses_array[i].get_instructor()->get_name() << "]";
        }
        std::cout << "\n";
    }

    int course_idx;
    std::cout << "Select course index: ";
    std::cin >> course_idx;
    if (course_idx < 0 || course_idx >= num_courses) {
        std::cout << "[ERROR] Invalid course index.\n";
        return;
    }

    std::cout << "\n--- Instructors ---\n";
    for (int i = 0; i < num_instructors; i++) {
        std::cout << i << ". " << instructors_array[i]->get_name()
                    << " (" << instructors_array[i]->get_department() << ")\n";
    }

    int inst_idx;
    std::cout << "Select instructor index: ";
    std::cin >> inst_idx;
    if (inst_idx < 0 || inst_idx >= num_instructors) {
        std::cout << "[ERROR] Invalid instructor index.\n";
        return;
    }

    instructor* new_inst = instructors_array[inst_idx];
    course& target = courses_array[course_idx];

    // ── RULE: Do not exceed the course limit ──
    if (new_inst->exceeds_maximum_courses()) {
        std::cout << "[BLOCKED] " << new_inst->get_name()
                    << " has reached their maximum course limit.\n";
        return;
    }

    // ── RULE: No double booking of an instructor ──
    for (int i = 0; i < num_courses; i++) {
        if (i == course_idx) continue;
        if (courses_array[i].get_instructor() == new_inst &&
            schedules_overlap(courses_array[i], target)) {
            std::cout << "[BLOCKED] " << new_inst->get_name()
                        << " is already assigned to "
                        << courses_array[i].course_code
                        << " at an overlapping time.\n";
            return;
        }
    }

    // ── RULE: full_time professors have priority over occasional lecturers ──
    instructor* current_inst = target.get_instructor();

    if (current_inst != nullptr) {
        bool new_is_fulltime = (dynamic_cast<full_time_professor*>(new_inst) != nullptr);
        bool cur_is_fulltime = (dynamic_cast<full_time_professor*>(current_inst) != nullptr);

        // If the current one is full-time and the new one is occasional => blocked
        if (cur_is_fulltime && !new_is_fulltime) {
            std::cout << "[BLOCKED] A full-time professor is already assigned. "
                        << "Occasional lecturers cannot displace them.\n";
            return;
        }

        // If both are full-time => compare department
        if (cur_is_fulltime && new_is_fulltime) {
            bool new_same_dept = (new_inst->get_department() == target.department);
            bool cur_same_dept = (current_inst->get_department() == target.department);

            if (cur_same_dept && !new_same_dept) {
                std::cout << "[BLOCKED] Current professor is from the same department "
                            << "and has priority.\n";
                return;
            }
            if (!cur_same_dept && new_same_dept) {
                std::cout << "[INFO] " << new_inst->get_name()
                            << " from same department displaces "
                            << current_inst->get_name() << ".\n";
                occasional_lecturer* occ = dynamic_cast<occasional_lecturer*>(current_inst);
                full_time_professor* ftp = dynamic_cast<full_time_professor*>(current_inst);
                if (occ) occ->decrement_courses();
                if (ftp) ftp->decrement_courses();
            }
        }

        // If the current one is occasional and the new one is full_time => displace
        if (!cur_is_fulltime && new_is_fulltime) {
            std::cout << "[INFO] Full-time professor displaces occasional lecturer "
                        << current_inst->get_name() << ".\n";
            occasional_lecturer* occ = dynamic_cast<occasional_lecturer*>(current_inst);
            if (occ) occ->decrement_courses();
        }
    }

    // ── Assign ──
    target.set_instructor(new_inst);
    new_inst->increment_courses();
    std::cout << "[OK] " << new_inst->get_name()
                << " assigned to " << target.course_code << ".\n";
}

// ══════════════════════════════════════════════════════════
// ASSIGN ROOM TO COURSE
// ══════════════════════════════════════════════════════════
void schedule_engine::assign_room_to_course() {
    std::cout << "\n--- Courses ---\n";
    for (int i = 0; i < num_courses; i++) {
        std::cout << i << ". " << courses_array[i].course_code
                    << " - " << courses_array[i].course_name;
        if (courses_array[i].get_assigned_space() != nullptr)
            std::cout << " [Room assigned]";
        std::cout << "\n";
    }

    int course_idx;
    std::cout << "Select course index: ";
    std::cin >> course_idx;
    if (course_idx < 0 || course_idx >= num_courses) {
        std::cout << "[ERROR] Invalid course index.\n";
        return;
    }

    std::cout << "\n--- Spaces ---\n";
    for (int i = 0; i < num_spaces; i++) {
        std::cout << i << ". " << spaces_array[i]->get_building_name()
                    << " Room " << spaces_array[i]->get_room_number()
                    << " (Capacity: " << spaces_array[i]->get_max_seating_capacity() << ")\n";
    }

    int space_idx;
    std::cout << "Select space index: ";
    std::cin >> space_idx;
    if (space_idx < 0 || space_idx >= num_spaces) {
        std::cout << "[ERROR] Invalid space index.\n";
        return;
    }

    course& target = courses_array[course_idx];
    space* new_space = spaces_array[space_idx];

    // ── RULE: room capacity ──
    if (target.get_enrollment() > new_space->get_max_seating_capacity()) {
        std::cout << "[BLOCKED] Room capacity (" << new_space->get_max_seating_capacity()
                    << ") is less than course enrollment (" << target.get_enrollment() << ").\n";
        return;
    }

    // ── RULE: no double-booking of spaces ──
    for (int i = 0; i < num_courses; i++) {
        if (i == course_idx) continue;
        if (courses_array[i].get_assigned_space() == new_space &&
            schedules_overlap(courses_array[i], target)) {
            std::cout << "[BLOCKED] Room " << new_space->get_building_name()
                        << " " << new_space->get_room_number()
                        << " is already booked for " << courses_array[i].course_code
                        << " at an overlapping time.\n";
            return;
        }
    }

    // ── Assign space ──
    target.assign_space(new_space);
    std::cout << "[OK] Room " << new_space->get_building_name()
                << " " << new_space->get_room_number()
                << " assigned to " << target.course_code << ".\n";
}

// ══════════════════════════════════════════════════════════
// Assign spaces
// ══════════════════════════════════════════════════════════
bool schedule_engine::room_assignment(course* cour, space* spac) {
    if (cour->get_enrollment() > spac->get_max_seating_capacity()) {
        std::cout << "[BLOCKED] Room capacity exceeded.\n";
        return false;
    }

    for (int i = 0; i < num_courses; i++) {
        course* other = &courses_array[i];
        bool same_room = (other->get_assigned_space() == spac);
        bool same_day  = (other->get_course_day() == cour->get_course_day());

        if (same_room && same_day) {
            bool overlap_start = (cour->get_start_hour() < other->get_end_hour());
            bool overlap_end   = (cour->get_end_hour()   > other->get_start_hour());
            if (overlap_start && overlap_end) {
                std::cout << "[BLOCKED] Room already occupied at that time.\n";
                return false;
            }
        }
    }

    cour->assign_space(spac);
    std::cout << "[OK] Room assigned.\n";
    return true;
}

// ══════════════════════════════════════════════════════════
// Lecturer limit clases
// ══════════════════════════════════════════════════════════
bool schedule_engine::lecturer_limit_classes() {
    for (int i = 0; i < num_instructors; i++) {
        if (instructors_array[i]->exceeds_maximum_courses()) {
            std::cout << "[ERROR] An occasional lecturer exceeds the maximum of 3 classes.\n";
            return false;
        }
    }
    return true;
}

// ══════════════════════════════════════════════════════════
// Exit program
// ══════════════════════════════════════════════════════════
bool schedule_engine::exit_program() {
    bool result = true;
    for (int i = 0; i < num_instructors; i++) {
        if (!instructors_array[i]->meets_minimum_courses()) {
            std::cout << "[ERROR] A full-time professor has fewer than 2 classes assigned.\n";
            result = false;
        }
    }
    if (result) {
        std::cout << "All contractual obligations met. Closing system.\n";
    }
    return result;
}