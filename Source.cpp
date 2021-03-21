#include "Header.h"
#include "Vector.h"

using namespace std;

int main() {
	vector<string> matr = f_processing("inp.txt");
	vector<vertice> vertices = get_vertices(matr);

	/* Zeeelensky, there is some place for your code) */

	outp_path(matr, vertices);
}
