#include "fmmm.h"
#include "hir.h"
#include "ort.h"

using namespace ogdf;

int main()
{
	string file = "add32.gml";
	string file1 = "crack.gml";
	string file2 = "Protein_core_2.gml";

	// start time
	auto t1 = std::chrono::high_resolution_clock::now();

	/*
	**  force directed layout
	*/

	layoutForceDir(file);
	layoutForceDir(file1);
	layoutForceDir(file2);

	// stop time
	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = t2 - t1;

	std::cout << "Force directed: " << diff.count() << "s" << std::endl
			  << std::endl;

	// start time
	t1 = std::chrono::high_resolution_clock::now();

	/*
	** Hierarchical layout
	*/
	layoutHierarchical(file);
	// layoutHierarchical(file1); // takes too long
	layoutHierarchical(file2);

	// stop time
	t2 = std::chrono::high_resolution_clock::now();
	diff = t2 - t1;

	std::cout << "Hierarchical: " << diff.count() << "s" << std::endl
			  << std::endl;

	// start time
	t1 = std::chrono::high_resolution_clock::now();

	/*
	** Orthogonal layout
	*/
	layoutOrthogonal(file);
	// layoutOrthogonal(file1); // takes to long
	// layoutOrthogonal(file2); // creates segmentation fault

	// stop time
	t2 = std::chrono::high_resolution_clock::now();
	diff = t2 - t1;

	std::cout << "Orthogonal: " << diff.count() << "s" << std::endl
			  << std::endl;

	return 0;
}
