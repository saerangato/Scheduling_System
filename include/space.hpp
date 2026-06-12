#ifndef SPACE_HPP
#define SPACE_HPP

#include <string>

// It becomes an abstract class
class space {
protected:
    std::string building_name;
    int room_number;
    int max_seating_capacity;

public:
    space(std::string b_name, int r_num, int capacity);
    virtual ~space();

    std::string get_building_name() const;
    int get_room_number() const;
    int get_max_seating_capacity() const;

    /*It's declared as a pure virtual function since there isn't 
    any general "spaces" just classrooms and laboratories.*/
    virtual void print_details() const = 0;

};

#endif