#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

vector<std::string> readlines(std::string name){
	std::ifstream f(name);
	vector<std::string> lines;
	while (!f.eof()) {
		std::string line;
		getline(f, line);
		lines.push_back(line);
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
	vector<std::pair<int, int>> adjacent;	//the list of adjacent vertices' index and path len
	vertice(int x1, int y1) { x = x1; y = y1; min_dist = 1000000; passed = false; }
	void n_adj(int v, int n) { adjacent.push_back({v, n}); }	//that's for me, don't warry about)
};

int is_free(vector<std::string> matr, int xs, int ys, int xf, int yf) {
	if (xs==xf){
		int y1 = min(ys, yf);
		int y2 = max(ys, yf);
		for (int j = y1; j < y2; j++) {
			if (matr[xs][j] == 'X')return false;
		}
		return y2 - y1;
	}
	else {
		int x1 = min(xs, xf);
		int x2 = max(xs, xf);
		for (int i = x1; i < x2; i++) {
			if (matr[i][ys] == 'X')return false;
		}
		return x2 - x1;
	}

}

vector<vertice> get_vertices(vector<std::string> matr, int x_st, int y_st, int x_fin, int y_fin) {
	vector<vertice> vertice_list;
	for (int i = 1; i < int(matr.size()-1); i++) {
		for (int j = 1; j < int(matr[i].size()-1); j++) {
			if (matr[i][j] == ' ' && ((i == x_st&&j==y_st|| i == x_fin && j == y_fin)||!(matr[i-1][j]==' ' && matr[i+1][j]==' ' || matr[i][j-1] == ' ' && matr[i][j+1] == ' ')|| (matr[i - 1][j] == ' ' && matr[i + 1][j] == ' ' && (matr[i][j - 1] == ' ' || matr[i][j + 1] == ' '))|| ((matr[i - 1][j] == ' ' || matr[i + 1][j] == ' ') && matr[i][j - 1] == ' ' && matr[i][j + 1] == ' '))) {
				vertice v(i, j);
				vertice_list.push_back(v);
			}
		}
	}
	for (int i = 0; i < int(vertice_list.size()); i++) {
		for (int j = 0; j < int(vertice_list.size()); j++) {
			int w = is_free(matr, vertice_list[i].x, vertice_list[i].y, vertice_list[j].x, vertice_list[j].y);
			if ((vertice_list[i].y == vertice_list[j].y || vertice_list[i].x == vertice_list[j].x) && w) {
				vertice_list[i].n_adj(j, w);
				vertice_list[j].n_adj(i, w);
			}
		}
	}
	return vertice_list;
}

void outp_path(vector<std::string> &matrix, vector<vertice> vert, vector<int> path) {
	int counter = 1;
	for (int i = 1; i < int(path.size()); i++) {
		vertice a = vert[path[i-1]];
		vertice b = vert[path[i]];
		if (a.x == b.x) {
			for (int y = (a.y < b.y ? (a.y+1) : (a.y-1)); (a.y < b.y ? (y <= b.y) : (y >= b.y)); (a.y < b.y ? (y++) : (y--))) {
				char c = (counter + 1 < 10 ? counter + 49 : counter + 88);
				matrix[a.x][y] = c;
				counter++;
			}
		}
		else {
			for (int x = a.x; (a.x < b.x ? (x < b.x) : (x > b.x)); (a.x < b.x ? (x++) : (x--))) {
				char c = (counter + 1 < 10 ? counter + 49 : counter + 88);
				matrix[x][a.y] = c;
				counter++;
			}
		}
	}

	for (int i = 0; i < int(matrix.size()); i++) {
		for (int j = 0; j < matrix[i].length(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int find(vector<pair<int, int>> vect, pair<int, int> val) {
	for (int i = 0; i < vect.size(); i++) {
		if (vect[i].first == val.first && vect[i].second == val.second) return i;
	}
	return -1;
}

int get_fin_ind(vector<vertice> &vert, int x_st, int y_st, int x_fin, int y_fin){
	int f_ind = -1;
	for (int i = 0; i< vert.size(); i++){
		vertice &v = vert[i];
		if (v.x == x_st&&v.y == y_st){ v.min_dist = 0; v.path.push_back(i); continue; }
		if (v.x == x_fin && v.y == y_fin) { f_ind = i; continue; }
	}
	return f_ind;
}

int min(vector<vertice> v) {
    int min_index;
    for (int i = 0; i < int(v.size()); i++) {
        min_index = i;
        if (!v[i].passed) break;
    }
    for (int i = 0; i < int(v.size()); i++) {
        if (!v[i].passed && v[i].min_dist < v[min_index].min_dist) min_index = i;
    }
    return min_index;
}

int Deikstra(int finish, vector<vertice> &vertices) {
    while (1) {
        int a = min(vertices);
        if (vertices[a].passed) return -1;
        for (std::pair<int, int> p : vertices[a].adjacent) {
            if (vertices[a].min_dist + p.second < vertices[p.first].min_dist) {
                vertices[p.first].min_dist = vertices[a].min_dist + p.second;
                vertices[p.first].path.erase(vertices[p.first].path.begin(), vertices[p.first].path.end());
                for (int w : vertices[a].path) vertices[p.first].path.push_back(w);
                vertices[p.first].path.push_back(a+1);
            }
        }
        vertices[a].passed = true;
        if (a==finish) return vertices[finish].min_dist;
    }
}
