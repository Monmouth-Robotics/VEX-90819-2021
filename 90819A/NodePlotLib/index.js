let plotlib = require('nodeplotlib');
let fs = require('fs');

let lines;
let values = [];
let graph1Data = [{ x: [], y: [], name: "Left Target" }, { x: [], y: [], name: "Left Actual" }];
let graph2Data = [{ x: [], y: [], name: "Right Target" }, { x: [], y: [], name: "Right Actual" }];
let counter = 0;

async function createGraph() {
    let data = await fs.readFileSync('../output.log', { encoding: 'utf16le', flag: 'r' });
    lines = await data.substring(2).split("\n");
    for (let i = 0; i < lines.length; i++) {
        await values.push(lines[i].split(","));
    }
    for (let i = 0; i < values.length; i++) {
        for (let j = 0; j < values.length; j++) {
            await graph1Data[0].x.push(counter);
            await graph2Data[0].x.push(counter);
            await graph1Data[1].x.push(counter);
            await graph2Data[1].x.push(counter);
            await graph1Data[0].y.push(parseFloat(values[i][0]));
            await graph2Data[0].y.push(parseFloat(values[i][1]));
            await graph1Data[1].y.push(parseFloat(values[i][2]));
            await graph2Data[1].y.push(parseFloat(values[i][3]));
            counter++;
        }
    }
    await plotlib.stack(graph1Data);
    await plotlib.stack(graph2Data);
    await plotlib.plot();
}

createGraph();

// prosv5 terminal | Out-File -FilePath C:\Users\vedag\Documents\GitHub\VEX-90819-2021\90819A\output.log