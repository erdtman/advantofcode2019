/*Day 2*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Patch.h"
#include "Fabric.h"

int main(int argc, const char * argv[]) {
	if (argc < 2) {
		std::cout << "Usage:" << std::endl;
		std::cout << "day3 <input>" << std::endl;
		return 1;
	}
	
	std::vector<Patch> patches;

	{
		std::string file = argv[1];
		std::cout << "Start with input file '" << argv[1] << "'" <<std::endl;
		std::ifstream infile(argv[1]);
		Patch patch;
		while (infile >> patch) {
			patches.push_back(patch);
		}
	}
	
	Fabric fabric;
	{
		for (auto p : patches) {
			fabric.addPatch(p);
		}

		std::cout << "part one: " << fabric.countOverlap() << std::endl;
	}

	{
		Patch *freePatch;

		for (auto patch : patches) {
			if (fabric.isFree(patch)) {
				freePatch = &patch;
				break;
			}
		}

		std::cout << "part two: " << freePatch->id << std::endl;
	}	
	
    return 0;
}