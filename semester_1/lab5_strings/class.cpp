#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <numeric>


// проверка на пустоту
bool IsEmptyFile(std::istream& file) {
	return file.peek() == std::ifstream::traits_type::eof();
}


double CalculateAverage(const std::vector<int32_t> nums) {
	int64_t sum = std::accumulate(nums.begin(), nums.end(), int64_t{});
	return static_cast<double>(sum) / nums.size();
}


void WriteAvgToOutputFile(const std::string& filename, double value) {

	std::ofstream out{ filename };
	if (!out.is_open()) {
		throw ("Error!!! Could not open file \"" + filename + "\"");
	}
	out << value;
	out.close();
}


std::vector<int32_t> ReadDataFromFile(const std::string& filename) {

	std::ifstream in(filename);

	// проверка на открытие файла
	if (!in.is_open()) {
		throw ("Error!!! Could not open file \"" + filename + "\"");
	}

	if (IsEmptyFile(in)) {
		throw ("Error!!! file \"" + filename + "\" is empty!");
	}

	std::vector<int32_t> numbers;

	int x;
	while (in >> x) { // чениt до конца
		numbers.push_back(x);
	}

	in.close();
	return numbers;
}


void PrintVector(const std::vector<int32_t>& vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << ' ';
	}
}


int main() {


	const std::string input_file{ "input.txt" };
	const std::string output_file{ "output.txt" };


	try {

		std::vector<int32_t> numbers = ReadDataFromFile(input_file);
#if 0
		/*std::cout << "------------------- \n";
		PrintVector(numbers);
		std::cout << "------------------- \n";*/
#endif
		double avg = CalculateAverage(numbers);
		WriteAvgToOutputFile(output_file, avg);
		std::cout << "Result has been written to " << std::quoted(output_file) << '\n';
	}
	catch (const std::string& msg) {
		std::cerr << msg << std::endl;
	}
}