const fs = require("fs");
// var parseString = require('xml2js').parseString;

// load xml
// var xml = fs.readFileSync('string_interactions_prkaca.xml');

// parse xml
// parseString(xml, (_, result) => {
  const nodes = buildNodes();
  const edges = buildEdges();

  fs.writeFileSync("../../Exercise2/test.graphml", stringify(nodes, edges));
  console.log("file was converted");
// });

// pull node info from interactor list
function buildNodes() {
  return [
    { id: "P1", label: "Peter" },
    { id: "P2", label: "Sarah" },
    { id: "P3", label: "Lena" },
    { id: "P4", label: "Daniel" },
    { id: "P5", label: "Hanna" },
    { id: "P6", label: "Marc" },
    { id: "P7", label: "Alex" },
    { id: "P8", label: "Michael" },
    { id: "P9", label: "Laura" },
    { id: "P1", label: "Tess" }
  ];
}

// pull edge info from interaction list
function buildEdges(edges) {
  return [
    { from: "P1", to: "P4" },
    { from: "P2", to: "P1" },
    { from: "P2", to: "P4" },
    { from: "P3", to: "P2" },
    { from: "P4", to: "P10" },
    { from: "P5", to: "P4" },
    { from: "P5", to: "P1" },
    { from: "P6", to: "P7" },
    { from: "P6", to: "P8" },
    { from: "P6", to: "P9" },
    { from: "P7", to: "P8" },
    { from: "P10", to: "P4" },
    { from: "P10", to: "P6" },
    { from: "P10", to: "P9" }
  ];
}

// convert to graphml format
function stringify(nodes, edges) {
  const fileHeader = `<graphml>
<key attr.name="name" attr.type="string" for="node" id="name"/>
<graph edgedefault="directed" id="">`;

  const fileFooter = `</graph></graphml>`;

  let output = fileHeader;

  output += nodes
    .map(
      n => ` 
    <node id="${n.id}">
        <data key="name">${n.label}</data>
    </node>`
    )
    .join("");

  output += edges
    .map(e => `<edge source="${e.from}" target="${e.to}"/>`)
    .join("");

  output += fileFooter;

  return output;
}
