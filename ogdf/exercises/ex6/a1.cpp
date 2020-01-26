#include <sstream>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/misclayout/BertaultLayout.h>

using namespace ogdf;
using namespace std;

int main()
{
    string file = "test";

    Graph G;
    if (!GraphIO::read(G, "./exercises/ex6/test.graphml"))
    {
        cerr << "Could not read file" << endl;
        return 1;
    }

    for (node n : G.nodes)
    {
        if (n->degree() == 0)
            G.delNode(n);
    }

    cout << G.numberOfNodes() << "," << G.numberOfEdges();

    GraphCopy GC(G);
    GraphAttributes GA(GC);

    FMMMLayout fmmm;
    fmmm.randSeed(randomNumber(100000, 999999));
    fmmm.useHighLevelOptions(false);
    fmmm.unitEdgeLength(15.0);
    fmmm.newInitialPlacement(true);
    fmmm.qualityVersusSpeed(FMMMOptions::QualityVsSpeed::GorgeousAndEfficient);

    fmmm.call(GA);

    // cout << file << "," << i;

    ostringstream s;
    s << "./exercises/ex6/output/" << file << "(" << 0 << ").svg";
    string path(s.str());
    GraphIO::write(GA, path, GraphIO::drawSVG);
    // }

    return 0;
}
