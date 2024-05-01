#include <iostream>

#define _2DVector std::vector<std::vector<double>> 
#define _1DVector std::vector<double>
#define map std::unordered_map<std::string, _1DVector>
#define dic std::unordered_map <int, std::string>

enum Mode {
	dev = 0,
	user = 1,
};
template <typename Any> void simpleTest(Any thing) {
	std::cout << std::endl << "simple test: " << thing << std::endl;
}
template <typename Any> void test2DArray(int rows, int cols, Any** array, Mode mode) {
	std::cout << "2d array test : " << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			switch (mode) {
			case dev:
				std::cout << array[i][j] << "          ";
				break;
			case user:
				std::cout << array[j][i] << "          ";
				break;
			default:
				std::cout << "ERROR";
				break;
			}
		}
		std::cout << std::endl;
	}
}
template <typename Any>Any** Initiate_2dArray(int rows, int cols) {
	Any** array = new Any * [rows];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			array[i] = new double[cols];
		}
	}
	std::cout << "the given array has been Initiated" << std::endl;
	return array;
}
template <typename Any>void test1DArray(int size, Any* array) {
	std::cout << "\nthe given array is :" << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << "  ";
	}
	std::cout << std::endl;
}
template<typename key, typename value>void testHashmap(std::unordered_map<key, value> x) {
	for (const auto& pair : x) {
		std::cout << "key: " << pair.first << "     value: " << pair.second << std::endl;
	}
}
template<typename Any> void testVector(std::vector<Any> v) {

	for (auto i = v.begin(); i != v.end(); i++) {
		std::cout << *i << " ";
	}

}
template <typename Any> void testMultiVector(std::vector<std::vector<Any>> v) {
	for (int i = 0; i < v.size(); i++) {
		for (auto k = v[i].begin(); k != v[i].end(); k++) {
			std::cout << *k << "     ";
		}
		std::cout << std::endl;
	}
}
template <typename Any> void Initiate_2DVector(_2DVector& v, int size) {
	for (int i = 0; i < size; i++) {
		_1DVector innerV;
		for (int j = 0; j < size; j++) {
			innerV.push_back(0);
		}
		v.push_back(innerV);
	}
}
void line(std::string s) {
	for (int i = 0; i < 5; i++) {
		s += s;
	}
	std::cout << "\n" + s << std::endl;
}


