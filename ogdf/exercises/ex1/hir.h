#ifndef HIR    // To make sure you don't declare the function more than once by including the header multiple times.
#define HIR

#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/SugiyamaLayout.h>

using namespace ogdf;

void layoutHierarchical(string);

#endif