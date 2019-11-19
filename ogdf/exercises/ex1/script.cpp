#include "fmmm.h"
#include "multi.h"
#include "ort.h"

using namespace ogdf;

int main()
{
	string file = "add32.gml";
	string file1 = "crack.gml";
	string file2 = "Protein_core_2.gml";

	double time = 0;
	usedTime(time);

	/*
	**  force directed layout
	*/

	layoutForceDir(file);
	layoutForceDir(file1);
	layoutForceDir(file2);

	usedTime(time);

	std::cout << "Force directed: " << time << "s" << std::endl
			  << std::endl;

	usedTime(time);

	/*
	** Hierarchical layout
	*/
	layoutMulti(file);
	layoutMulti(file1);
	layoutMulti(file2);

	usedTime(time);

	std::cout << "Hierarchical: " << time << "s" << std::endl
			  << std::endl;

	usedTime(time);

	/*
	** Orthogonal layout
	*/
	layoutOrthogonal(file);
	layoutOrthogonal(file1); // takes to long
	layoutOrthogonal(file2); // creates segmentation fault

	usedTime(time);

	std::cout << "Orthogonal: " << time << "s" << std::endl
			  << std::endl;

	return 0;
}
