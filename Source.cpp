#include "Header.h"

using namespace std;

int main() {
	int x_st, y_st, x_fin, y_fin, fin_ind, dist;
	vector<std::string> matr = f_processing("inp.txt");
	vector<vertice> vertices = get_vertices(matr);
	cout<<"Enter the coordinates of start point: "<<endl;
	cout<<"\tx = "; cin>>x_st; cout<<endl;
	cout<<"\ty = "; cin>>y_st; cout<<endl;
	cout<<"Enter the coordinates of finish point: "<<endl;
	cout<<"\tx = "; cin>>x_fin; cout<<endl;
	cout<<"\ty = "; cin>>y_fin; cout<<endl;
	remove_some_vertices(vertices, x_st, y_st, x_fin, y_fin, fin_ind);
	dist = Deikstra(fin_ind, vertices);
	/* Zeeelensky, there is some place for your code) */

	outp_path(matr, vertices);
}
