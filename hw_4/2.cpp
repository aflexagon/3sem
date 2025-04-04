#include <string>
#include <format>
#include <filesystem>
#include <iostream>

std::uintmax_t count_size(const std::filesystem::path& path) {
	std::uintmax_t total_size = 0;

	for (const auto& entity : std::filesystem::directory_iterator(path))
	{
		if (std::filesystem::is_directory(entity)) {
			total_size += count_size(entity);
		}
		else if (std::filesystem::is_regular_file(entity))
		{
			//std::cout << std::format("Path for current file {}, and its size: {} bytes", entity.path().string(), curr_size) << std::endl;
			std::uintmax_t curr_size = std::filesystem::file_size(entity);
			total_size += curr_size;
		}
	}

	return total_size;
}

int main() {
	std::string path;
	std::cout << "Enter path for directory: ";
	//path-name without spaces
	std::cin >> path;
	//call size-count function
	auto size = count_size(path);
	std::cout << std::format("Size of user's directory: {} bytes", size);
}