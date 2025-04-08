#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "json.hpp"

using json_t = nlohmann::json;

struct Course {
    std::string discipline;
    int lecture_hours;
    int seminar_hours;
    int lab_hours;
    int self_study_hours;
    bool exam;
};

void to_json(json_t& object, const Course& course) {
    object = json_t{
        {"discipline", course.discipline},
        {"lecture_hours", course.lecture_hours},
        {"seminar_hours", course.seminar_hours},
        {"self_study_hours", course.self_study_hours},
        {"exam", course.exam},
        { "lab_hours", course.lab_hours}
    };
}

void from_json(const json_t& object, Course& course) {
    course.discipline = object["discipline"].get<std::string>();
    course.lecture_hours = object["lecture_hours"].get<int>();
    course.seminar_hours = object["seminar_hours"].get<int>();
    course.self_study_hours = object["self_study_hours"].get<int>();
    course.exam = object["exam"].get<bool>();
    course.lab_hours = object["lab_hours"].get<int>();
}

std::istream& operator>>(std::istream& istream, Course& course) {
    std::cout << "Enter MIPT courses data: " << '\n';

    std::cout << "Discipline name: ";
    std::getline(istream, course.discipline);

    std::cout << "Lecture hours: ";
    istream >> course.lecture_hours;

    std::cout << "Seminar hours: ";
    istream >> course.seminar_hours;

    std::cout << "Lab hours (0 if no): ";
    istream >> course.lab_hours;

    std::cout << "Self-study hours: ";
    istream >> course.self_study_hours;

    std::cout << "Does exam exist? (1/0): ";
    istream >> course.exam;
    istream.ignore();

    return istream;
}

int main() {
    std::filesystem::create_directory("courses_data");

    std::vector<Course> courses;
    char chr = 'y';

    while (chr == 'y') {
        Course course;
        std::cin >> course;
        courses.push_back(course);

        std::cout << "\nWant to add another course? (y/n): ";
        std::cin >> chr;
        std::cin.ignore();

        if (chr != 'y' && chr != 'n') { throw std::runtime_error("Invalid input"); }
    }

    json_t j;
    j["courses"] = courses;

    std::ofstream("courses_data/courses.json") << j.dump(4);
    std::cout << "\nData saved";
}