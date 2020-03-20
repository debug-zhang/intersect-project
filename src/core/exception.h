#ifndef FILE_EXCEPTION_H
#define FILE_EXCEPTION_H

#include <exception>
#define RANGE 100000

struct not_integer_exception :public std::exception {
	const char* what() const throw () {
		return "require a integer";
	}
};

struct not_valid_integer_exception :public std::exception {
	const char* what() const throw () {
		return "require a integer larger or equal than 1";
	}
};

struct not_char_exception :public std::exception {
	const char* what() const throw () {
		return "require a char";
	}
};

struct undefined_graph_exception :public std::exception {
	const char* what() const throw () {
		return "graph not in [L, R, S, C]";
	}
};

struct over_range_exception :public std::exception {
	const char* what() const throw () {
		return "number not in range (-100000, 100000)";
	}
};

struct dot_superposition_exception :public std::exception {
	const char* what() const throw () {
		return "two dots are the same";
	}
};

struct infinate_intersect_exception :public std::exception {
	const char* what() const throw () {
		return "two graphs have infinate intersections";
	}
};

struct file_not_exist_exception :public std::exception {
	const char* what() const throw () {
		return "the specific file does not exist";
	}
};

#endif // FILE_EXCEPTION