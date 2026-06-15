#include <iostream>
#include <string>
#include "../include/schedule_engine.hpp"
#include "../include/instructor.hpp"
#include "../include/full_time_professor.hpp"
#include "../include/occasional_lecturer.hpp"
#include "../include/course.hpp"
#include "../include/space.hpp"

void print_separator() {
    std::cout << "\n========================================\n";
}

void print_menu() {
    print_separator();
    std::cout << "   UNIVERSITY SCHEDULING SYSTEM\n";
    print_separator();
    std::cout << "1. Load data from files\n";
    std::cout << "2. Assign instructor to course\n";
    std::cout << "3. Assign room to course\n";
    std::cout << "4. List all courses\n";
    std::cout << "5. List all instructors\n";
    std::cout << "6. List all spaces\n";
    std::cout << "7. Exit\n";
    print_separator();
    std::cout << "Select an option: ";
}

int main() {
    schedule_engine engine;

    instructor** instructors = nullptr;
    space**      spaces      = nullptr;
    course*      courses     = nullptr;
    int num_instructors = 0, num_spaces = 0, num_courses = 0;

    bool data_loaded = false;
    int option = 0;

    while (true) {
        print_menu();
        std::cin >> option;

        switch (option) {

        case 1: {
            try {
                engine.load_instructors("instructors.csv");
                engine.load_spaces("spaces.csv");
                engine.load_courses("courses.csv");

                instructors     = engine.get_instructors();
                num_instructors = engine.get_num_instructors();
                spaces          = engine.get_spaces();
                num_spaces      = engine.get_num_spaces();
                courses         = engine.get_courses();
                num_courses     = engine.get_num_courses();

                data_loaded = true;
                std::cout << "[OK] Data loaded successfully.\n";
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] " << e.what() << "\n";
            }
            break;
        }

        case 2: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            engine.assign_instructor_to_course();
            break;
        }

        case 3: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            engine.assign_room_to_course();
            break;
        }

        case 4: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            print_separator();
            for (int i = 0; i < num_courses; i++) {
                std::cout << "Course: " << courses[i].course_code
                            << " | " << courses[i].course_name
                            << " | Students: " << courses[i].get_enrollment()
                            << " | Day: " << courses[i].get_course_day()
                            << " " << courses[i].get_start_hour()
                            << "-" << courses[i].get_end_hour();
                if (courses[i].get_instructor())
                    std::cout << " | Instructor: " << courses[i].get_instructor()->get_name();
                if (courses[i].get_assigned_space())
                    std::cout << " | Room: " << courses[i].get_assigned_space()->get_building_name()
                                << " " << courses[i].get_assigned_space()->get_room_number();
                std::cout << "\n";
            }
            break;
        }

        case 5: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            print_separator();
            for (int i = 0; i < num_instructors; i++) {
                full_time_professor* ftp = dynamic_cast<full_time_professor*>(instructors[i]);
                std::cout << instructors[i]->get_name()
                            << " | " << instructors[i]->get_department()
                            << " | " << (ftp ? "Full-time" : "Occasional")
                            << " | Courses: ";
                if (ftp) std::cout << ftp->get_assigned_courses_count();
                else {
                    occasional_lecturer* occ = dynamic_cast<occasional_lecturer*>(instructors[i]);
                    if (occ) std::cout << occ->get_assigned_courses_count();
                }
                std::cout << "\n";
            }
            break;
        }

        case 6: {
            if (!data_loaded) { std::cout << "[ERROR] Load data first (option 1).\n"; break; }
            print_separator();
            for (int i = 0; i < num_spaces; i++) {
                spaces[i]->print_details();
            }
            break;
        }


        case 7: {
            if (!data_loaded || engine.exit_program()) {
                return 0; 
            }
            std::cout << "[BLOCKED] Cannot exit: not all obligations are met.\n";
            break;
        }

        default:
            std::cout << "[ERROR] Invalid option.\n";
            break;
        }
    }

    return 0;
}