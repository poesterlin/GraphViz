#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/orthogonal/OrthoLayout.h>
#include <ogdf/planarity/EmbedderMinDepthMaxFaceLayers.h>
#include <ogdf/planarity/PlanarSubgraphFast.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <ogdf/planarity/SubgraphPlanarizer.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
#include <ogdf/energybased/StressMinimization.h>
#include <ogdf/misclayout/BertaultLayout.h>

using namespace ogdf;
using namespace std;

double t;
void startTime()
{
	t = 0;
	usedTime(t);
}

void stopTime()
{
	cout << "," << usedTime(t) * 1000;
}

void save(GraphAttributes GA, string file, string method)
{
	string baseFolder = "./exercises/ex5/output/";
	GraphIO::write(GA, baseFolder.append(file).append("-" + method).append(".svg"), GraphIO::drawSVG);
}

void analyse(GraphAttributes GA)
{
	auto G = GA.constGraph();
	BertaultLayout ba(1);
	cout << "," << ba.edgeCrossings(GA);

	int sum = 0;
	for (edge e : G.edges)
	{
		sum += GA.bends(e).size();
	}
	cout << "," << sum;

	auto size = GA.boundingBox();
	cout << "," << size.width();
	cout << "," << size.height();
}

void layoutStressMin(Graph G, string file)
{
	GraphAttributes GA(G,
					   GraphAttributes::nodeGraphics | GraphAttributes::nodeType |
						   GraphAttributes::edgeGraphics | GraphAttributes::edgeType);
	StressMinimization layout;

	layout.setIterations(500);
	layout.call(GA);
	save(GA, file, "stress");
	analyse(GA);
}

void layoutOrthogonal(Graph G, string file)
{
	GraphAttributes GA(G,
					   GraphAttributes::nodeGraphics | GraphAttributes::nodeType |
						   GraphAttributes::edgeGraphics | GraphAttributes::edgeType);
	PlanarizationLayout pl;

	SubgraphPlanarizer crossMin;

	auto *ps = new PlanarSubgraphFast<int>;
	ps->runs(100);
	VariableEmbeddingInserter *ves = new VariableEmbeddingInserter;
	ves->removeReinsert(RemoveReinsertType::All);

	crossMin.setSubgraph(ps);
	crossMin.setInserter(ves);

	EmbedderMinDepthMaxFaceLayers *emb = new EmbedderMinDepthMaxFaceLayers;
	pl.setEmbedder(emb);

	OrthoLayout *ol = new OrthoLayout;
	ol->separation(20.0);
	ol->cOverhang(0.4);
	pl.setPlanarLayouter(ol);

	pl.call(GA);
	save(GA, file, "orth");
	analyse(GA);
}

int main()
{
	string files[20] = {
		"g.10.1",
		"g.10.22",
		"g.20.13",
		"g.20.14",
		"g.30.15",
		"g.30.17",
		"g.40.12",
		"g.40.8",
		"g.50.7",
		"g.50.8",
		"g.60.0",
		"g.60.1",
		"g.70.1",
		"g.71.2",
		"g.80.6",
		"g.81.9",
		"g.90.1",
		"g.90.2",
		"g.100.1",
		"g.100.3",
	};

	cout << "orth <-> stress" << endl;
	cout << "file, nodes, edges, xings, bends, width, height, time, xings, bends, width, height, time" << endl;

	for (string file : files)
	{
		Graph G;
		if (!GraphIO::read(G, string("./exercises/ex5/graphs/").append(file).append(".graphml")))
		{
			cerr << "Could not read file" << endl;
			return 1;
		}
		cout << file << "," << G.numberOfNodes() << "," << G.numberOfEdges();

		startTime();
		layoutOrthogonal(G, file);
		stopTime();

		startTime();
		layoutStressMin(G, file);
		stopTime();

		cout << endl;
	}

	return 0;
}
