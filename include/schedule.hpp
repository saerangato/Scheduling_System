#pragma once
#include<iostream>
#include <string>

class schedule {
    private:
        std::string day_of_week;
        int start_time, end_time;
    public:
        schedule();
        schedule(std::string day, int start, int end);
        ~schedule();
        std::string get_day_of_week();
        int get_start_time();
        int get_end_time();
        void set_day_of_week(std::string day);
        void set_start_time(int start);
        void set_end_time(int end);
};
