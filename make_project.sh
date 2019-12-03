#!/bin/sh

# Create CMakeLists.txt for project
cat <<- EOF > CMakeLists.txt
	cmake_minimum_required(VERSION 3.10)

	project(advent_of_code_2019)

EOF

# Add subproject for each day
for i in `seq --format "%02g" 1 25`
do
	echo "add_subdirectory(day${i})" >> CMakeLists.txt
	mkdir -p day${i}/src
	mkdir -p day${i}/test

	cat <<- EOF > day${i}/CMakeLists.txt
	CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

	set(CMAKE_CXX_STANDARD 17)

	add_subdirectory(src)
	EOF

	cat <<- EOF > day${i}/src/day${i}.cpp
		// https://adventofcode.com/2019/day/

		#include <iostream>

		int main() {
		    std::cout << "Day ${i}" << "\n";
		    return 0;
		}
	EOF

	touch day${i}/src/day${i}_input.txt

	cat <<- EOF > day${i}/src/CMakeLists.txt
		cmake_minimum_required(VERSION 3.10)

		configure_file(day${i}_input.txt day${i}_input.txt COPYONLY)
		
		add_executable(day${i} day${i}.cpp)
	EOF
done
