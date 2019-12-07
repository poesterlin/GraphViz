// @ts-check
const sizeOf = require("image-size");
const path = require("path");

const files = [
  "g.10.1",
  "g.10.22",
  "g.20.13",
  "g.20.14",
  "g.30.15",
  "g.30.17",
  "g.40.12",
  "g.40.8",
  "g.50.8",
  "g.50.7",
  "g.60.1",
  "g.60.0",
  "g.70.1",
  "g.71.2",
  "g.80.6",
  "g.81.9",
  "g.90.1",
  "g.90.2",
  "g.100.1",
  "g.100.3"
];

const endings = [
  "-Optimal-Median.png",
  "-Optimal-GreedyInsert.png",
  "-LongestPath-Median.png",
  "-LongestPath-GreedyInsert.png"
];

endings.forEach(e => {
  console.log(e);
  files
    .forEach(f => {
      const out = sizeOf(path.join("output", "png", f + e));
      console.log(`${f},${out.height * out.width}`)
    })
});
