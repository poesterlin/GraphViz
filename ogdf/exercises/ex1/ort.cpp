#include "ort.h"

void layoutOrthogonal(string file)
{
	Graph G;
	GraphAttributes GA(G,
					   GraphAttributes::nodeGraphics | GraphAttributes::nodeType |
						   GraphAttributes::edgeGraphics | GraphAttributes::edgeType);

    if (!GraphIO::read(G, string("./exercises/ex1/graph/").append(file)))
	{
		std::cerr << "Could not read gml file" << std::endl;
		return;
	}

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

	GraphIO::write(GA, string("./exercises/ex1/output/").append(file.substr(0, file.length() - 4).append("-Orthogonal.svg")), GraphIO::drawSVG);
    std::cout << "Orthogonal Layout of " << file << " done" << std::endl;
}