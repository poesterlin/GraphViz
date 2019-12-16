#include <sstream>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/misclayout/BertaultLayout.h>

using namespace ogdf;
using namespace std;

void analyse(GraphAttributes GA)
{
    auto G = GA.constGraph();
    BertaultLayout ba(1);
    cout << "," << ba.edgeCrossings(GA);

    auto size = GA.boundingBox();
    cout << "," << size.width();
    cout << "," << size.height();
}

int main()
{
    string files[6] = {
        "grafo121.20",
        "grafo1327.50",
        "grafo1405.50",
        "grafo190.20",
        "grafo8224.100",
        "grafo8674.100"};

    for (string file : files)
    {
        Graph G;
        if (!GraphIO::read(G, string("./exercises/ex5/graphs/").append(file).append(".graphml")))
        {
            cerr << "Could not read file" << endl;
            return 1;
        }

        // cout << file << "," << G.numberOfNodes() << "," << G.numberOfEdges();
        for (int i = 1; i <= 5; i++)
        {

            GraphCopy GC(G);
            GraphAttributes GA(GC);

            FMMMLayout fmmm;
            fmmm.randSeed(randomNumber(100000, 999999));
            fmmm.useHighLevelOptions(true);
            fmmm.unitEdgeLength(15.0);
            fmmm.newInitialPlacement(true);
            fmmm.qualityVersusSpeed(FMMMOptions::QualityVsSpeed::GorgeousAndEfficient);

            fmmm.call(GA);

            cout << file << "," << i;
            analyse(GA);
            cout << endl;

            ostringstream s;
            s << "./exercises/ex5/output/" << file << "(" << i << ").svg";
            string path(s.str());
            GraphIO::write(GA, path, GraphIO::drawSVG);
        }
    }

    return 0;
}
