#include "fmmm.h"
#include "multi.h"
#include "ort.h"

using namespace ogdf;

double t;
void startTime()
{
	t = 0;
	usedTime(t);
}

void stopTime(string layout)
{
	std::cout << layout << ": " << usedTime(t) << "s" << std::endl
			  << std::endl;
}

int main()
{
	string file = "add32.gml";
	string file1 = "crack.gml";
	string file2 = "Protein_core_2.gml";


	/*
	**  force directed layout
	*/
	startTime();
	layoutForceDir(file);
	stopTime("Force directed 1");
	startTime();
	layoutForceDir(file1);
	stopTime("Force directed 2");
	startTime();
	layoutForceDir(file2);
	stopTime("Force directed 3");

	/*
	** Hierarchical layout
	*/
	startTime();
	layoutMulti(file);
	stopTime("Multi 1");
	startTime();
	layoutMulti(file1);
	stopTime("Multi 2");
	startTime();
	layoutMulti(file2);
	stopTime("Multi 3");

	/*
	** Orthogonal layout
	*/
	startTime();
	layoutOrthogonal(file);
	stopTime("Orthogonal 1");
	startTime();
	layoutOrthogonal(file1);
	stopTime("Orthogonal 2");
	startTime();
	layoutOrthogonal(file2); // creates segmentation fault
	stopTime("Orthogonal 3");

	return 0;
}
