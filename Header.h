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
	int y;			//coordinates in entered matrix
	int min_dist;
	bool passed;
	int seq_num;	//the sequential number of vertice in path
	std::vector<vertice> adjacent;	//the list of adjacent vertices
	vertice(int x1, int y1) { x = x1; y = y1; min_dist = 0; passed = false; }
	void n_adj(vertice v) { adjacent.push_back(v);}	//that's for me, don't warry about)
};

std::vector<vertice> get_vertices(std::vector<std::string> matr) {
	std::vector<vertice> vertice_list;
	for (int i = 0; i < int(matr.size()); i++) {
		for (int j = 0; j < int(matr[i].size()); j++) {
			if (matr[i][j] == ' ') {
				vertice v(i, j);
				vertice_list.push_back(v);
			}
		}
	}
	for (int i = 0; i < int(vertice_list.size()); i++) {
		for (int j = 0; j < int(vertice_list.size()); j++) {
			if (vertice_list[i].x - vertice_list[j].x == 1 && vertice_list[i].y== vertice_list[j].y || vertice_list[i].y - vertice_list[j].y == 1 && vertice_list[i].x == vertice_list[j].x) {
				vertice_list[i].n_adj(vertice_list[j]);
				vertice_list[j].n_adj(vertice_list[i]);
			}
		}
	}
	return vertice_list;
}

void outp_path(std::vector<std::string> &inp_matrix, std::vector<vertice> vert) {
	for (vertice v : vert) {
		if (v.seq_num) {
			char path_n = (v.seq_num<10?v.seq_num+48:v.seq_num+96);
			inp_matrix[v.x][v.y] = path_n;
		}
	}
	for (std::string line : inp_matrix) {
		for (int i = 0; i < int(line.length()); i++) {
			std::cout << line[i] << " ";
		}
		std::cout << std::endl;
	}
}
