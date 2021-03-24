#include "Header.h"

using namespace std;

int main() {
	int x_st, y_st, x_fin, y_fin, fin_ind, dist;
	vector<std::string> matr = f_processing("inp.txt");
	cout<<"Enter the coordinates of start point: "<<endl;
	cout<<"\tx = "; cin>>x_st; cout<<endl;
	cout<<"\ty = "; cin>>y_st; cout<<endl;
	cout<<"Enter the coordinates of finish point: "<<endl;
	cout<<"\tx = "; cin>>x_fin; cout<<endl;
	cout<<"\ty = "; cin>>y_fin; cout<<endl;
	if (matr[x_st][y_st]=='X'|| matr[x_fin][y_fin] == 'X') { cout << "The path doesn't exist!" << endl; exit(0); }
	vector<vertice> vertices = get_vertices(matr, x_st, y_st, x_fin, y_fin);
	fin_ind = get_fin_ind(vertices, x_st, y_st, x_fin, y_fin);
	if (fin_ind<0) { cout << "Error" << endl; exit(0); }
	dist = Deikstra(fin_ind, vertices);
	if (dist < 0 || dist == 1000000) { cout << "The path doesn't exist!" << endl; exit(0); }
	matr[x_st][y_st] = 48;
	outp_path(matr, vertices, fin_ind);
}

