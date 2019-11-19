#include "multi.h"

// Introduction for Multilevelmixer:
//
// Multilevel layout computation is an iterative process that can
// be roughly divided in three phases: coarsening, placement, and
// single level layout. Starting with the smallest graph, the ﬁnal
// layout for the input graph is obtained by successively computing
// layouts for the graph sequence computed by the coarsening phase.
// At each level, the additional vertices need to be placed into the
// layout of the preceding level, optionally after a scaling to provide
// the necessary space.
// It helps to overcome some problems of single level energybased graph
// layouts (such as finding a local optimal solution) and it speeds up
// the computation.
//
// The Modular Multilevel Mixer is an abstract class that can be used
// to build energybased multilevel layouts. Since it is modular you can
// easily assemble different layouts by using different coarsening
// techniques (merger), placer and single level layouts.

using namespace ogdf;

template <class T>
static MultilevelBuilder *getDoubleFactoredZeroAdjustedMerger()
{
    T *merger = new T();
    merger->setFactor(2.0);
    merger->setEdgeLengthAdjustment(0);
    return merger;
}

static InitialPlacer *getBarycenterPlacer()
{
    BarycenterPlacer *placer = new BarycenterPlacer();
    placer->weightedPositionPriority(true);
    return placer;
}

static void configureFastLayout(ScalingLayout *sl, MultilevelBuilder *&merger, InitialPlacer *&placer)
{
    // The SolarMerger is used for the coarsening phase.
    merger = new SolarMerger(false, false);
    // The SolarPlacer is used for the placement.
    placer = new SolarPlacer();

    // Postprocessing is applied at each level after the single level layout.
    // It is turned off in this example.
    sl->setExtraScalingSteps(0);
    // In this example it is used to scale with fixed factor 2 relative to the graph drawing.
    sl->setScalingType(ScalingLayout::ScalingType::RelativeToDrawing);
    sl->setScaling(2.0, 2.0);
}

static void configureNiceLayout(ScalingLayout *sl, MultilevelBuilder *&merger, InitialPlacer *&placer)
{
    // The EdgeCoverMerger is used for the coarsening phase.
    merger = getDoubleFactoredZeroAdjustedMerger<EdgeCoverMerger>();
    // The BarycenterPlacer is used for the placement.
    placer = getBarycenterPlacer();

    // Postprocessing is applied at each level after the single level layout.
    // In this example a FastMultipoleEmbedder with zero iterations is used for postprocessing.
    sl->setExtraScalingSteps(0);
    // No scaling is done. It is fixed to factor 1.
    sl->setScalingType(ScalingLayout::ScalingType::RelativeToDrawing);
    sl->setScaling(1.0, 1.0);
}

static void configureNoTwistLayout(ScalingLayout *sl, MultilevelBuilder *&merger, InitialPlacer *&placer)
{
    // The LocalBiconnectedMerger is used for the coarsening phase.
    // It tries to keep biconnectivity to avoid twisted graph layouts.
    merger = getDoubleFactoredZeroAdjustedMerger<LocalBiconnectedMerger>();
    // The BarycenterPlacer is used for the placement.
    placer = getBarycenterPlacer();

    // Postprocessing is applied at each level after the single level layout.
    // It is turned off in this example.
    sl->setExtraScalingSteps(1);
    // The ScalingLayout is used to scale with a factor between 5 and 10
    // relative to the edge length.
    sl->setScalingType(ScalingLayout::ScalingType::RelativeToDesiredLength);
    sl->setScaling(5.0, 10.0);
}

void layoutMulti(string file)
{
    Graph g;
    GraphAttributes ga(g,
                       GraphAttributes::nodeGraphics |
                           GraphAttributes::edgeGraphics |
                           GraphAttributes::nodeLabel |
                           GraphAttributes::edgeStyle |
                           GraphAttributes::nodeStyle |
                           GraphAttributes::nodeTemplate);

    if (!GraphIO::read(g, string("./exercises/ex1/graph/").append(file)))
    {
        std::cerr << "Could not read gml file" << std::endl;
        return;
    }

    // We assign a width and height of 10.0 to each node.
    for (node v : g.nodes)
    {
        ga.width(v) = ga.height(v) = 10.0;
    }

    // Then we create a MultilevelGraph from the GraphAttributes.
    MultilevelGraph mlg(ga);

    // The FastMultipoleEmbedder is used for the single level layout.
    FastMultipoleEmbedder *fme = new FastMultipoleEmbedder();
    // It will use 1000 iterations at each level.
    fme->setNumIterations(1000);
    fme->setRandomize(false);

    // To minimize dispersion of the graph when more nodes are added, a
    // ScalingLayout can be used to scale up the graph on each level.
    ScalingLayout *sl = new ScalingLayout();
    sl->setLayoutRepeats(1);
    // The FastMultipoleEmbedder is nested into this ScalingLayout.
    sl->setSecondaryLayout(fme);

    // Set the merger and placer according to the wanted configuration.
    MultilevelBuilder *merger;
    InitialPlacer *placer;

    // configureFastLayout(sl, merger, placer);
    // configureNiceLayout(sl, merger, placer);
    configureNoTwistLayout(sl, merger, placer);

    // Then the ModularMultilevelMixer is created.
    ModularMultilevelMixer *mmm = new ModularMultilevelMixer;
    mmm->setLayoutRepeats(1);
    // The single level layout, the placer and the merger are set.
    // mmm->setLevelLayoutModule(sl);
    // mmm->setInitialPlacer(placer);
    mmm->setMultilevelBuilder(merger);

    // Since energybased algorithms are not doing well for disconnected
    // graphs, the ComponentSplitterLayout is used to split the graph and
    // computation is done separately for each connected component.
    ComponentSplitterLayout *csl = new ComponentSplitterLayout;
    // The TileToRowsPacker merges these connected components after computation.
    TileToRowsCCPacker *ttrccp = new TileToRowsCCPacker;
    csl->setPacker(ttrccp);
    csl->setLayoutModule(mmm);

    // At last the PreprocessorLayout removes double edges and loops.
    PreprocessorLayout ppl;
    ppl.setLayoutModule(csl);
    ppl.setRandomizePositions(true);

    ppl.call(mlg);

    // After the computation the MultilevelGraph is exported to the
    // GraphAttributes and written to disk.
    mlg.exportAttributes(ga);
    GraphIO::write(ga, string("./exercises/ex1/output/").append(file.substr(0, file.length() - 4).append("-Multi.svg")), GraphIO::drawSVG);
    std::cout << "Multi Layout of " << file << " done" << std::endl;
}
