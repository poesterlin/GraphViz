// @ts-check
const path = require("path");
const fs = require("fs");
const _ = require("lodash");

const base = "./twitter";

const ids = new Map();

_.uniq(
  getDirectories(base).map(file => file.substr(0, file.indexOf(".")))
).forEach(id => ids.set(id, []));

let counter = Array.from(ids.keys()).length;

getDirectories(base)
  .filter(f => f.includes("edges"))
  .forEach(file => {
    const f = fs
      .readFileSync(path.join(base, file))
      .toString()
      .split("\n");

    f.forEach(line => {
      const [id, to] = line.split(" ");

      if (!id || !to || id === to) {
        return;
      }

      if (counter < 2000) {
        if (!ids.has(id)) {
          ids.set(id, []);
          counter++;
        }
        if (!ids.has(to)) {
          ids.set(to, []);
          counter++;
        }
      }

      if (ids.has(id) && ids.has(to)) {
        ids.set(id, ids.get(id).concat([{ from: id, to }]));
      }
    });
  });

fs.writeFileSync("test.graphml", stringify(ids));
console.log("file was converted");

function getDirectories(source) {
  return fs
    .readdirSync(source, { withFileTypes: true })
    .filter(dirent => !dirent.isDirectory())
    .map(dirent => dirent.name);
}

/**
 *
 * @param {Map<string, {from:string, to:string}[]>} map
 */
function stringify(map) {
    // <key attr.name="name" attr.type="string" for="node" id="name"/>
  let output = `<graphml>
  <key attr.type="string" for="node" id="name"/>
  <graph edgedefault="directed" id="">`;

  const nodes = Array.from(map.keys()).filter(id => map.get(id).length > 0);
  const edges = _.flatMap(nodes, id => ids.get(id)).filter(e => e.from && e.to);

  console.log(nodes.length, edges.length);

  output += nodes
    .map(
      n => `
      <node id="${n}"></node>`
      )
    //   <data key="name">${n}</data>
    .join("");

  output += edges
    .map(e => `<edge source="${e.from}" target="${e.to}"/>`)
    .join("\n");

  return output + `</graph></graphml>`;
}
