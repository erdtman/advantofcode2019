#ifndef FABRIC_H
#define FABRIC_H

#include <map>

#include <iostream>
#include "Patch.h"

class Fabric {
public:
	std::map<std::string, int> fabric;
	void addPatch(Patch& patch);
	unsigned int countOverlap();
    bool isFree(Patch& patch);
};

void Fabric::addPatch(Patch& patch) {
    for (int x = patch.start.x; x < (patch.start.x + patch.size.x); ++x) {
        for (int y = patch.start.y; y < (patch.start.y + patch.size.y); ++y) {
            std::string coordinate = std::to_string(x) + "x" + std::to_string(y);
            fabric[coordinate] = fabric[coordinate] ? ++fabric[coordinate] : 1;
        }
    }
}

unsigned int Fabric::countOverlap() {
    unsigned int counter = 0;
    for ( auto const& [key, val] : this->fabric ) {
        counter = (val != 1) ? counter+1 : counter;
    }
    return counter;
}

bool Fabric::isFree(Patch& patch) {
     for (int x = patch.start.x; x < (patch.start.x + patch.size.x); ++x) {
        for (int y = patch.start.y; y < (patch.start.y + patch.size.y); ++y) {
            std::string coordinate = std::to_string(x) + "x" + std::to_string(y);
            if(fabric[coordinate] != 1) {
                return false;
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, Fabric &o) {
    for ( auto const& [key, val] : o.fabric ) {
    	std::cout << key << ':' << val << std::endl ;
	}
    return out;
}

#endif
