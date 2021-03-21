#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

std::vector<std::string> readlines(std::string name){
	std::ifstream f(name);
	std::vector<std::string> lines;
	int count = 0;
	while (!f.eof()) {
		std::string line;
		getline(f, line);
		lines.push_back(line);
		count++;
	}
	f.close();
	return lines;
}

void rstrip(std::string& s, char r = ' ') {
	auto p = s.end()-1;
	while (*p == r) {
		s.erase(p);
		p -= 1;
	}
}

std::vector<std::string> f_processing(std::string name) {
	std::vector <std::string> lines = readlines(name);
	std::vector<std::string> matrix;
	for (std::string s : lines) {
		std::string n_s = "";
		for (int i = 0; i < int(s.length()); i += 2) { n_s += s[i]; }
		rstrip(n_s);
		matrix.push_back(n_s);
	}
	return matrix;
}

class vertice{
public:
	int x;
	int y;			//координати в цій матриці, яка дається на вхід
	int min_dist;
	bool passed;
	int seq_num;	//ми там повинні будемо потім циферки розставити вздовж маршруту, пам'ятаєш? Так от, це вони.
	std::vector<vertice> adjacent;	//список суміжних вершин, корисна річ))
	vertice(int x1, int y1) { x = x1; y = y1; min_dist = 0; passed = false; }
	void n_adj(vertice v) { adjacent.push_back(v);}	//це для мене, не парся)
};
