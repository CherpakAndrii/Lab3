#pragma once
#include <string>
#include <math.h>
#include <vector>
#include <iostream>
#include "PriorityQueue.h"
#include "Stack.h"
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
	int x = 0;
	int y = 0;			//coordinates in input matrix
	int min_dist = 1000000;
	bool passed = false;
	int last;
	vector<std::pair<int, int>> adjacent;	//the list of adjacent vertices' index and path len
	vertice(int x1, int y1) { x = x1; y = y1; }
	vertice() = default;
	void n_adj(int v, int n) { adjacent.push_back({v, n}); }	//that's for me, don't warry about)
};

int is_adj(vector<std::string> matr, int xs, int ys, int xf, int yf) {
	if (xs != xf and ys != yf) return 0;
	else if (xs == xf) {
		int y1 = std::min(ys, yf);
		int y2 = std::max(ys, yf);
		for (int j = y1; j < y2; j++) {
			if (matr[xs][j] == 'X')return 0;
		}
		return y2 - y1;
	}
	else {
		int x1 = std::min(xs, xf);
		int x2 = std::max(xs, xf);
		for (int i = x1; i < x2; i++) {
			if (matr[i][ys] == 'X')return 0;
		}
		return x2 - x1;
	}
}

vector<vertice> get_vertices(vector<std::string> matr, int x_st, int y_st, int x_fin, int y_fin) {
	time_t t0 = clock();
	vector<vertice> vertice_list;
	int count = 0;
	int** n_matr = new int* [matr.size()];
	for (int i = 0; i < int(matr.size()); i++) {
		n_matr[i] = new int[matr[0].length()];
		for (int j = 0; j < int(matr[0].length()); j++) {
			if (matr[i][j]==' ') n_matr[i][j] = -1;
			else n_matr[i][j] = -2;
		}
	}

	for (int i = 1; i < int(matr.size()-1); i++) {
		for (int j = 1; j < int(matr[i].length()-1); j++) {
			if (matr[i][j] == ' ' && ((i == x_st&&j==y_st|| i == x_fin && j == y_fin)||!(matr[i-1][j]==' ' && matr[i+1][j]==' ' || matr[i][j-1] == ' ' && matr[i][j+1] == ' ')|| (matr[i - 1][j] == ' ' && matr[i + 1][j] == ' ' && (matr[i][j - 1] == ' ' || matr[i][j + 1] == ' '))|| ((matr[i - 1][j] == ' ' || matr[i + 1][j] == ' ') && matr[i][j - 1] == ' ' && matr[i][j + 1] == ' '))) {
				vertice v(i, j);
				vertice_list.push_back(v);
				n_matr[i][j] = count++;
			}
		}
	}
	time_t t1 = clock();
	std::cout << "Vertice search time: " << double(t1 - t0) / CLOCKS_PER_SEC <<" seconds" << std::endl;
	for (int i = 0; i < vertice_list.size(); i++) {
		if (n_matr[vertice_list[i].x + 1][vertice_list[i].y]+2) {
			int n = 1;
			while (n_matr[vertice_list[i].x + n][vertice_list[i].y] == -1) n++;
			int j = n_matr[vertice_list[i].x + n][vertice_list[i].y];
			vertice_list[i].n_adj(j, n);
			vertice_list[j].n_adj(i, n);
		}
		if (n_matr[vertice_list[i].x - 1][vertice_list[i].y]+2) {
			int n = 1;
			while (n_matr[vertice_list[i].x - n][vertice_list[i].y] == -1) n++;
			int j = n_matr[vertice_list[i].x - n][vertice_list[i].y];
			vertice_list[i].n_adj(j, n);
			vertice_list[j].n_adj(i, n);
		}
		if (n_matr[vertice_list[i].x][vertice_list[i].y + 1]+2) {
			int n = 1;
			while (n_matr[vertice_list[i].x][vertice_list[i].y+n] == -1) n++;
			int j = n_matr[vertice_list[i].x][vertice_list[i].y+n];
			vertice_list[i].n_adj(j, n);
			vertice_list[j].n_adj(i, n);
		}
		if (n_matr[vertice_list[i].x][vertice_list[i].y-1] + 2) {
			int n = 1;
			while (n_matr[vertice_list[i].x][vertice_list[i].y-n]==-1) n++;
			int j = n_matr[vertice_list[i].x][vertice_list[i].y-n];
			vertice_list[i].n_adj(j, n);
			vertice_list[j].n_adj(i, n);
		}
	}				//?? 113 ???????(7:13 ? ???????) ?????? ???????? ?? ???? ???????(
	cout << "Edge search time: " << double(clock() - t1) / CLOCKS_PER_SEC <<" seconds" << endl;
	return vertice_list;
}

char count(int& counter) {
	char val = (counter < 10 ? counter + 48 : counter + 87);
	counter < 35 ? counter++ : counter = 1;
	return val;
}

void outp_path(vector<std::string> &matrix, vector<vertice> vert, int finish) {
	Stack<int> path;
	int m, n, last = finish;
	while (last < 999999) {
		path.push(last);
		last = vert[last].last;
	}
	int counter = 1;
	m = path.pop();
	while (path.size()) {
		n = m; m = path.pop();
		vertice a = vert[n];
		vertice b = vert[m];
		if (a.x == b.x) {
			for (int y = (a.y < b.y ? (a.y+1) : (a.y-1)); (a.y < b.y ? (y <= b.y) : (y >= b.y)); (a.y < b.y ? (y++) : (y--))) {
				matrix[a.x][y] = count(counter);
			}
		}
		else {
			for (int x = (a.x < b.x ? (a.x + 1) : (a.x - 1)); (a.x < b.x ? (x <= b.x) : (x >= b.x)); (a.x < b.x ? (x++) : (x--))) {
				matrix[x][a.y] = count(counter);
			}
		}
	}

	for (int i = 0; i < int(matrix.size()); i++) {
		for (int j = 0; j < int(matrix[i].length()); j++) {
			if (matrix[i][j]=='X' or matrix[i][j] == ' ') std::cout << matrix[i][j] << " ";
			else std::cout << "\033[1;35m"<<matrix[i][j]<<"\033[0m" << " ";
		}
		std::cout << std::endl;
	}
}


int get_fin_ind(vector<vertice> &vert, int x_st, int y_st, int x_fin, int y_fin, int& st_ind){
	int f_ind = -1;
	for (int i = 0; i< int(vert.size()); i++){
		vertice &v = vert[i];
		if (v.x == x_st && v.y == y_st) { v.min_dist = 0; v.last = 10000000; st_ind = i; }
		if (v.x == x_fin && v.y == y_fin) { f_ind = i; }
	}
	return f_ind;
}

inline double heur(int cur, int goal, vector<vertice> vert) {
	return sqrt(pow(vert[cur].x - vert[goal].x, 2) + pow(vert[cur].y - vert[goal].y, 2));
}

int A_star(int start, int finish, vector<vertice> &vertices) {
	PriorityQueue<std::pair<int, double>> q;
	q.push({ start, 0 });
    while (1) {
		if (q.empty()) return -1;
        int a = q.pop().first;
		if (a == finish) return vertices[finish].min_dist;
        for (std::pair<int, int> p : vertices[a].adjacent) {
            if (vertices[a].min_dist + p.second < vertices[p.first].min_dist) {
                vertices[p.first].min_dist = vertices[a].min_dist + p.second;
                vertices[p.first].last= a;
				if (!vertices[p.first].passed) q.push({ p.first , vertices[p.first].min_dist+heur(p.first, finish, vertices) });
            }
        }
        vertices[a].passed = true;
    }
}
