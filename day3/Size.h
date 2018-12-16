#ifndef SIZE_H
#define SIZE_H


#include <iostream>

class Size {
public:
	int x;
	int y;
};

std::istream& operator>>(std::istream &input, Size &o) {
	char separator;
	input >> o.x >> separator >> o.y; 
    return input;
}

std::ostream& operator<<(std::ostream& out, Size &o) {
    out << o.x << "x" << o.y;
    return out;
}

#endif
