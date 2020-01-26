//@ts-check

const readline = require("readline");

const point1 = [0.92, 0.8, 0.7, 0.6, 0.61];
const points = [
  "0.12 0.23 0.18 0.30 0.25",
  "0.92 0.80 0.70 0.60 0.61",
  "0.10 0.16 0.15 0.28 0.31",
  "0.91 0.83 0.81 0.55 0.46",
  "0.51 0.29 0.37 0.54 0.69",
  "0.50 0.21 0.34 0.61 0.61",
  "0.90 0.85 0.75 0.60 0.63",
  "0.18 0.23 0.12 0.25 0.26",
  "0.44 0.25 0.35 0.59 0.64",
  "0.58 0.26 0.38 0.60 0.65"
];

// --

points.forEach((p, i) => {
  const point2 = p.split(" ").map(parseFloat);
  const dist = Math.sqrt(
    point2
      .map((v, i) => v - point1[i])
      .map(s => s ** 2)
      .reduce((prev, curr) => prev + curr, 0)
  );
  console.log(i + 1, ":  ", ~~(dist * 1000) / 1000, "          ", dist);
});

//  --

// const f = [1,3,8];

// const p = points
//   .filter((_, i) => !f.includes(i + 1))
//   .map(l => l.split(" ").map(parseFloat));

// let mean = [];

// for (let i = 0; i < 5; i++) {
//   mean[i] = p.map(arr => arr[i]).reduce((prev, curr) => prev + curr, 0);
// }

// console.log(mean.map(m => m / 5).map(dist => ~~(dist * 1000) / 1000));
