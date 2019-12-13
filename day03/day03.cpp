// https://adventofcode.com/2019/day/3

#include <algorithm>
#include <cassert>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

constexpr int dimension{ 40'000 }; // Grid length & width

enum class Direction {
	up, down, left, right
};

using Grid = std::vector<std::vector<int>>;
using Path = std::vector<std::pair<Direction, int>>;

Path parse_path(std::string line) {
	const std::regex rect_regex{ R"(([UDLR])(\d+))" };
	Path path;
	// Split string on comma
	// https://stackoverflow.com/a/10861816
	std::stringstream ss{ line };
	while (ss.good()) {
		std::string substr;
		getline(ss, substr, ',');
		std::smatch sm;
		if (std::regex_match(substr, sm, rect_regex)) {
			if (sm[1] == 'U') {
				path.push_back(std::make_pair(Direction::up, std::stoi(sm[2])));
			}
			else if (sm[1] == 'D') {
				path.push_back(std::make_pair(Direction::down, std::stoi(sm[2])));
			}
			else if (sm[1] == 'L') {
				path.push_back(std::make_pair(Direction::left, std::stoi(sm[2])));
			}
			else if (sm[1] == 'R') {
				path.push_back(std::make_pair(Direction::right, std::stoi(sm[2])));
			}
		}
	}
	return path;
}

int manhattan_dist(int x, int y) noexcept {
	return abs(x - dimension / 2) + abs(y - dimension / 2);
}

std::vector<int> get_intersections_from_paths(Path path1, Path path2, int part = 1) {
	std::vector<int> intersections;
	Grid grid(dimension, std::vector<int>(dimension, -1));
	int x{ static_cast<int>(grid[0].size()) / 2 };
	int y{ static_cast<int>(grid.size()) / 2 };

	int path1_counter{ 0 };
	for (auto segment : path1) {
		if (segment.first == Direction::up) {
			while (segment.second--) {
				++path1_counter;
				--y;
				if (grid[y][x] < 0) grid[y][x] = path1_counter;
			}
		}
		else if (segment.first == Direction::down) {
			while (segment.second--) {
				++path1_counter;
				++y;
				if (grid[y][x] < 0) grid[y][x] = path1_counter;
			}
		}
		else if (segment.first == Direction::left) {
			while (segment.second--) {
				++path1_counter;
				--x;
				if (grid[y][x] < 0) grid[y][x] = path1_counter;
			}
		}
		else if (segment.first == Direction::right) {
			while (segment.second--) {
				++path1_counter;
				++x;
				if (grid[y][x] < 0) grid[y][x] = path1_counter;
			}
		}
	}

	x = static_cast<int>(grid[0].size() / 2);
	y = static_cast<int>(grid.size() / 2);
	int path2_counter{ 0 };
	for (auto segment : path2) {
		if (segment.first == Direction::up) {
			while (segment.second--) {
				++path2_counter;
				--y;
				if (grid[y][x] > 0) {
					if (part == 1) intersections.push_back(manhattan_dist(x, y));
					else intersections.push_back(grid[y][x] + path2_counter);
				}
			}
		}
		else if (segment.first == Direction::down) {
			while (segment.second--) {
				++path2_counter;
				++y;
				if (grid[y][x] > 0) {
					if (part == 1) intersections.push_back(manhattan_dist(x, y));
					else intersections.push_back(grid[y][x] + path2_counter);
				}
			}
		}
		else if (segment.first == Direction::left) {
			while (segment.second--) {
				++path2_counter;
				--x;
				if (grid[y][x] > 0) {
					if (part == 1) intersections.push_back(manhattan_dist(x, y));
					else intersections.push_back(grid[y][x] + path2_counter);
				}
			}
		}
		else if (segment.first == Direction::right) {
			while (segment.second--) {
				++path2_counter;
				++x;
				if (grid[y][x] > 0) {
					if (part == 1) intersections.push_back(manhattan_dist(x, y));
					else intersections.push_back(grid[y][x] + path2_counter);
				}
			}
		}
	}

	return intersections;
}

int main() {
	auto path1{ parse_path("R990,U944,L921,U993,L64,U29,R899,D406,R841,U716,L32,U658,L830,D481,L441,U491,L687,D847,"
		"L459,U920,R165,U224,L896,D868,L191,U877,L909,U467,R798,U132,R234,U49,R484,U911,R108,D308,R867,U350,L404,U107,"
		"L84,U668,R850,U470,L182,U93,R284,U999,L664,U110,R650,D189,R540,D112,R794,U999,R871,D829,L549,U988,R654,D411,"
		"R323,D774,R529,U275,L909,U936,R122,D922,L331,U813,L748,U770,R511,D892,L770,U318,R661,U823,R210,D393,L694,U929,"
		"L76,D619,R395,U651,R526,U145,R851,U112,R73,D89,R17,U929,R807,U87,R764,D158,L820,U803,L785,D205,L828,D271,L839,"
		"D482,L797,U338,R322,D633,L292,U16,R627,U19,R548,U516,L384,U83,R256,U937,R404,U322,R671,D543,L412,U446,R238,U246,"
		"L794,D750,L34,U317,L994,U874,L247,D20,R491,U834,L498,D987,R2,U175,R452,U168,R495,D183,R201,U532,L192,U984,L566,"
		"D471,L704,D2,L776,U5,R911,U308,R763,D555,R458,D439,L968,D78,R549,D583,R289,D355,L503,D871,L881,U516,L507,D551,"
		"R711,U702,L308,D905,L408,U932,L884,U218,L158,D562,L200,D114,R673,U448,R887,U181,R247,U329,L965,U495,L329,D162,"
		"L265,D389,R419,U435,R258,U146,R208,D184,R730,D19,L78,D886,R472,D350,R484,U392,L542,U601,L202,U974,L310,U52,L537,"
		"U597,L163,D655,R928,U269,L926,D790,L513,U441,L90,U581,L211,U871,R603,D130,L220,U459,L933,U648,R721,U642,R301,U537,"
		"L858,D777,R823,U14,R820,D218,L96,D318,L206,U280,R887,D241,L752,U828,R354,U864,R844,D872,L728,D298,L234,U695,R434,"
		"D94,R905,D592,L32,D860,R680,D197,R886,U760,L232,U916,L452,U248,R715,D773,R867,U77,R751,D36,R565,U897,R782,U931,"
		"R546,U261,R920,D296,R451,U258,L394,U965,R912,D593,L990") };
	auto path2{ parse_path("L994,U515,R163,U863,L343,U162,L875,D92,L483,D601,R79,D761,L389,U167,L145,U145,L247,U886,R61,"
		"U820,L584,D239,R402,U805,R956,U126,R615,D322,R431,D460,R397,D511,R805,D177,L778,U296,R599,U759,R40,U1,L422,U751,"
		"R94,U401,R504,U940,L564,U24,R595,U944,R815,U672,R787,D854,R579,D604,L62,U670,L516,U199,L639,D919,L485,U655,R391,"
		"U669,R772,D34,R868,D12,L108,U295,R701,D603,R493,U927,R29,D34,R499,U111,L87,U190,R884,D658,R474,D166,R921,U698,R592,"
		"U25,R710,D398,L26,U696,L432,D887,R469,U656,L428,D188,L543,D150,R160,U543,R743,U692,R618,D148,R956,U753,L175,D789,R897,"
		"U305,L137,D914,R330,D780,R744,D473,L754,U482,L975,D413,L698,U656,L177,U419,R13,D827,L67,D800,R369,U97,L34,D588,L41,D760,"
		"L164,U224,L921,D311,R489,U956,R277,U180,R724,U748,R785,U826,L426,D957,R303,U16,L729,U224,L712,U43,L280,D648,R987,D941,"
		"R154,D581,R876,U615,L480,D103,R636,D276,R948,U89,R434,D212,R837,D295,R532,D390,R374,D926,R911,D110,R258,U83,L955,U747,"
		"L925,D366,R571,U241,R628,D344,R919,U117,R337,D683,L720,U261,L124,D545,R979,D601,L906,D324,R441,U678,L978,U744,L472,D217,"
		"R799,U740,L77,U964,L278,U497,R441,U21,L37,U319,L24,D211,L44,U459,R35,D609,R900,D538,R397,D776,R629,D860,R519,D340,R168,"
		"U603,R46,U889,R897,D442,R997,U705,L82,D963,R941,U701,L347,D824,R269,U891,L569,D558,L867,U145,R121,D369,R542,U227,L198,"
		"U863,L755,U273,L734,D233,R578,U67,L821,U600,L203,D234,R695,U819,L639,D700,R295,D129,L612,U157,R212,U536,L968,U562,L999,"
		"D391,L231,U262,R334,D967,R463,U748,R842,D500,R860,U856,R263,D633,R460,D337,L880,U146,R910") };

	std::vector<int> part1_intersections{ get_intersections_from_paths(path1, path2) };
	const auto part_one_answer{ std::min_element(begin(part1_intersections), end(part1_intersections)) };
	std::cout << "part_one_answer: " << *part_one_answer << "\n";
	assert(*part_one_answer == 2427);

	std::vector<int> part2_intersections{ get_intersections_from_paths(path1, path2, 2) };
	const auto part_two_answer{ std::min_element(begin(part2_intersections), end(part2_intersections)) };
	std::cout << "part_two_answer: " << *part_two_answer << "\n";
	assert(*part_one_answer == 27890);

	return 0;
}

