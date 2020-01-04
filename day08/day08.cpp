// https://adventofcode.com/2019/day/8

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using layer_t = std::vector<std::vector<char>>;
using sif_image_t = std::vector<layer_t>;

sif_image_t get_image(const std::string& filename) {
	std::fstream in{ filename };
	if (!in) throw std::runtime_error("Could not open file");

	sif_image_t image;
	for (int z{ 0 }; z < 100; ++z) {
		layer_t layer;
		for (int y{ 0 }; y < 6; ++y) {
			std::vector<char> line;
			for (int x{ 0 }; x < 25; ++x) {
				char ch;
				in.get(ch);
				line.push_back(ch);
			}
			layer.push_back(line);
		}
		image.push_back(layer);
	}
	return image;
}

int count_zeroes(layer_t layer) {
	int zeroes{ 0 };
	for (const auto& line : layer) {
		zeroes += static_cast<int>(std::count(line.begin(), line.end(), '0'));
	}
	return zeroes;
}

int get_layer_with_min_zeroes(sif_image_t image) {
	std::vector<int> zeroes_in_layers;
	for (const auto& layer : image) {
		zeroes_in_layers.push_back(count_zeroes(layer));
	}
	return static_cast<int>(std::distance(begin(zeroes_in_layers), std::min_element(begin(zeroes_in_layers), end(zeroes_in_layers))));
}

int count_ones_times_twos(std::vector<std::vector<char>> layer) {
	int ones{ 0 };
	int twos{ 0 };
	for (const auto& line : layer) {
		ones += static_cast<int>(std::count(begin(line), end(line), '1'));
		twos += static_cast<int>(std::count(begin(line), end(line), '2'));
	}
	return ones * twos;
}

layer_t process_image(sif_image_t image) {
	layer_t processed_layer(6, std::vector<char>(25, '0'));
	for (size_t y{ 0 }; y < 6; ++y) {
		for (size_t x{ 0 }; x < 25; ++x) {
			int z{ 0 };
			while (image.at(z).at(y).at(x) == '2') {
				++z;
			}
			processed_layer.at(y).at(x) = image.at(z).at(y).at(x);
		}
	}
	return processed_layer;
}

void print_layer(layer_t layer) {
	for (size_t y{ 0 }; y < 6; ++y) {
		for (size_t x{ 0 }; x < 25; ++x) {
			if (layer.at(y).at(x) == '0') std::cout << '.';
			else std::cout << '*';
		}
		std::cout << "\n";
	}
}

int main()
{
	const sif_image_t image{ get_image("day08_input.txt") };
	assert(image.size() == 100);

	const int min_layer{ get_layer_with_min_zeroes(image) };
	const int part1_answer{ count_ones_times_twos(image.at(min_layer)) };
	std::cout << "part1_answer: " << part1_answer << "\n";
	assert(part1_answer == 2500);

	layer_t part2_answer{ process_image(image) };
	print_layer(part2_answer); // "CYUAH"

	return 0;
}

