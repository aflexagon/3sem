#include <cassert>
#include <string>
#include <chrono>
#include <filesystem>

#include <iostream>
#include <format>

int main() {
	using namespace std::chrono;

	std::string path;
	std::cout << "Enter path for directory: ";
	//path-name without spaces
	std::cin >> path;
	//check if path is valid
	if (!std::filesystem::is_directory(path)) { throw std::runtime_error("Directory doesn't exist"); };

	for (const auto& entity : std::filesystem::directory_iterator(path))
	{
		//standard stream doesn't support std::filesystem::file_time_type
		auto last_changes = std::filesystem::last_write_time(entity.path());
		//convert to yy_mm_dd
		year_month_day format_date{ floor < days >(clock_cast<system_clock>(last_changes)) };
		//standard output stream
		std::cout << '\n'    <<
			"File name: "	 << entity.path().filename() .string() << std::endl <<
			"Type: "		 << entity.path().extension().string() << std::endl <<
			"Last changes: " << format_date << std::endl;
	}
}