#include<iostream>
#include<string>
#include"schedule.hpp"

schedule::schedule() {
    day_of_week = "unasigned";
    start_time = 0;
    end_time = 0;
}

schedule::schedule(std::string day, int start, int end) {
    day_of_week = day;
    start_time = start;
    end_time = end;
}

 schedule::~schedule() {
 }

std::string schedule::get_day_of_week() {
    return day_of_week;
}

int schedule::get_start_time() {
    return start_time;
}

int schedule::get_end_time() {
    return end_time;
}

void schedule::set_day_of_week(std::string day) {
    day_of_week = day;
}

void schedule::set_start_time(int start) {
    start_time = start;
}

void schedule::set_end_time(int end) {
    end_time = end;
}