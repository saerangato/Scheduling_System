#include<iostream>
#include<string>
#include"schedule.hpp"

schedule::schedule() {
    day_of_week = "unassigned";
    start_time = -1;
    end_time = -1;
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
    if (end_time == -1||start_time < end_time) {
        start_time = start;
    }
}

void schedule::set_end_time(int end) {
    if (start_time == -1 || end_time > start_time) {
        end_time = end;
    }
}