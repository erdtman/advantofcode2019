#ifndef START_H
#define START_H

#include <iostream>

class Start {
public:
	int x;
	int y;
};

std::istream& operator>>(std::istream &input, Start &o) {
	char separator;
	input >> o.x >> separator >> o.y >> separator;
    return input;
}

std::ostream& operator<<(std::ostream& out, Start &o) {
    out << o.x << "," << o.y;
    return out;
}

#endif
