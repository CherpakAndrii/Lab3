#pragma once
#include <string>
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

vector<std::string> readlines(std::string name){
	std::ifstream f(name);
	vector<std::string> lines;
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

vector<std::string> f_processing(std::string name) {
	vector <std::string> lines = readlines(name);
	vector<std::string> matrix;
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
	int y;			//coordinates in input matrix
	int min_dist;
	bool passed;
	vector<int> path;
	int seq_num;	//the sequential number of vertice in path
	vector<std::pair<int, int>> adjacent;	//the list of adjacent vertices' index and path len
	vertice(int x1, int y1) { x = x1; y = y1; min_dist = 0; passed = false; }
	void n_adj(vertice v, int n) { adjacent.push_back({v, n});}	//that's for me, don't warry about)
};

vector<vertice> get_vertices(vector<std::string> matr) {
	vector<vertice> vertice_list;
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
			if (vertice_list[i].x - vertice_list[j].x == 1 && vertice_list[i].y== vertice_list[j].y ||
					vertice_list[i].y - vertice_list[j].y == 1 && vertice_list[i].x == vertice_list[j].x) {
				vertice_list[i].n_adj(j, 1);
				vertice_list[j].n_adj(i, 0);
			}
		}
	}
	return vertice_list;
}

void outp_path(vector<std::string> &inp_matrix, vector<vertice> vert) {
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

void remove_some_vertices(vector<vertice> &vert, int x_st, int y_st, int x_fin, int y_fin){
	for (int i = 0; i<vert.size(); i++){
		vertice v = vert[i];
		if (v.x == x_st&&v.y == y_st||v.x == x_fin&&v.y == y_fin) continue;
		if (v.adjacent.size()!=2||vert[v.adjacent[0].first].x!=vert[v.adjacent[1].first].x && vert[v.adjacent[0].first].y!=vert[v.adjacent[1].first].y) continue;
		vertice &adj1 = vert[v.adjacent[0].first];
		vertice &adj2 = vert[v.adjacent[1].first];
		adj1.n_adj(v.adjacent[1].first, v.adjacent[1].second+v.adjacent[0].second);
		adj2.n_adj(v.adjacent[0].first, v.adjacent[1].second+v.adjacent[0].second);
		adj1.adjacent.erase(find(adj1.adjacent.begin(), adj1.adjacent.end(), {i, v.adjacent[0].second}));
		adj2.adjacent.erase(find(adj2.adjacent.begin(), adj2.adjacent.end(), {i, v.adjacent[1].second}));
		vert.erase(vert.begin()+i);
	}
}
