
const fs = require('fs');
var parseString = require('xml2js').parseString;

// load xml
var xml = fs.readFileSync('string_interactions_prkaca.xml');


// parse xml
parseString(xml, (_, result) => {
    const nodes = buildNodes(result.set.interactorList[0].interactor);
    const edges = buildEdges(result.set.interactionList[0].interaction)

    fs.writeFileSync('string_interactions_prkaca.graphml', stringify(nodes, edges));
    console.log("file was converted")
});

// pull node info from interactor list
function buildNodes(nodes) {
    return nodes.map(n => {
        return { label: n.names[0].shortLabel[0], id: n.$.id };
    });
}

// pull edge info from interaction list
function buildEdges(edges) {
    const map = new Map();

    return edges.map((e) => {
        return {
            from: e.participantList[0].participant[0].interactorRef[0],
            to: e.participantList[0].participant[1].interactorRef[0]
        }
    }).filter(e => {
        // only allow unique connections
        const set = !map.has(JSON.stringify(e));
        map.set(JSON.stringify(e), true);
        return set;
    });
}


// convert to graphml format
function stringify(nodes, edges) {
    const fileHeader = `<graphml>
<key attr.name="name" attr.type="string" for="node" id="name"/>
<graph edgedefault="directed" id="">`

    const fileFooter = `</graph></graphml>`

    let output = fileHeader;

    output += nodes.map((n) => ` 
    <node id="${n.id}">
        <data key="name">${n.label}</data>
    </node>`
    ).join("");

    output += edges.map((e) => `<edge source="${e.from}" target="${e.to}"/>`).join("");

    output += fileFooter;

    return output;
}