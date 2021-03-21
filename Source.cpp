#include "Header.h"
using namespace std;
int main() {
	vector<string> matr = f_processing("inp.txt");
	vector<vertice> vertices = get_vertices(matr);
	for (vertice v : vertices) {
		cout << v.x << ":" << v.y << endl;
	}
}
