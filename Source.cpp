#include "Header.h"

int main() {
	int x_st, y_st, x_fin, y_fin, st_ind = -1, fin_ind, dist;
	vector<std::string> matr = f_processing("inp2.txt");
	std::cout<<"Enter the coordinates of the starting point: "<< std::endl;
	std::cout<<"\tx = "; std::cin>>x_st; std::cout<< std::endl;
	std::cout<<"\ty = "; std::cin>>y_st; std::cout<< std::endl;
	std::cout<<"Enter the coordinates of the end point: "<< std::endl;
	std::cout<<"\tx = "; std::cin>>x_fin; std::cout<< std::endl;
	std::cout<<"\ty = "; std::cin>>y_fin; std::cout<< std::endl;
	time_t t0 = clock();
	if (matr[x_st][y_st]=='X'|| matr[x_fin][y_fin] == 'X') { std::cout << "The path doesn't exist!" << std::endl; exit(0); }
	vector<vertice> vertices = get_vertices(matr, x_st, y_st, x_fin, y_fin);
	fin_ind = get_fin_ind(vertices, x_st, y_st, x_fin, y_fin, st_ind);
	if (fin_ind<0) { std::cout << "Error" << std::endl; exit(0); }
	time_t t1 = clock();
	dist = A_star(st_ind, fin_ind, vertices);
	time_t t2 = clock();
	std::cout << "Path search time: " << double(t2 - t1) / CLOCKS_PER_SEC << " seconds" << endl;
	if (dist < 0 || dist == 1000000) { std::cout << "The path doesn't exist!" << std::endl; exit(0); }
	matr[x_st][y_st] = 48;
	outp_path(matr, vertices, fin_ind);
	std::cout << "Path output time: " << double(clock() - t2) / CLOCKS_PER_SEC << " seconds"<<std::endl;
	std::cout << "Execution time: " << double(clock() - t0) / CLOCKS_PER_SEC << " seconds, path length: " << dist << std::endl;

}
