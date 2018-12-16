#ifndef PATCH_H
#define PATCH_H

#include <iostream>
#include <vector>

#include "Size.h"
#include "Start.h"

class Patch {
public:
	std::string id;
	Start start;
	Size size;
    bool isFree(std::vector<Patch> & patches);
};

std::istream& operator>>(std::istream &input, Patch &o) {
    std::string ignore;
	input >> o.id >> ignore >> o.start >> o.size;
    return input;
}

std::ostream& operator<<(std::ostream& out, Patch &o) {
    out << o.id << ": " << o.start << " " << o.size ;
    return out;
}

#endif
