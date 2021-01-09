let plotlib = require("nodeplotlib");
let fs = require("fs");
const puppeteer = require("puppeteer");
const setTZ = require("set-tz");

let lines;
let values = [];
let graph1Data = [
    { x: [], y: [], name: "Left Target" },
    { x: [], y: [], name: "Left Actual" },
];
let graph2Data = [
    { x: [], y: [], name: "Right Target" },
    { x: [], y: [], name: "Right Actual" },
];
let graph3Data = [
    { x: [], y: [], name: "Target Velocity" },
    { x: [], y: [], name: "Previous Velocity" },
];
let graph4Data = [{ x: [], y: [], name: "Closest Point" }];
let graph5Data = [{ x: [], y: [], name: "Curvature" }];
let counter = 0;

async function createGraph() {
    await setTZ("America/New_York");
    let data = await fs.readFileSync("../output.log", {
        encoding: "utf16le",
        flag: "r",
    });
    let time = await new Date().toLocaleString("en-US", {
        timeZone: "America/New_York",
    });
    console.log(time);
    time = time.replace(/:/g, "-");
    time = time.replace(/\//g, "-");
    console.log(time);
    await fs.mkdir(`./logs/${time}`, (err) => {
        if (err) {
            console.log(err);
        }
    });
    await fs.writeFile(`./logs/${time}/output.log`, data, function (err) {
        if (err) {
            console.log(err);
        }
    });
    lines = await data.substring(2).split("\n");
    for (let i = 0; i < lines.length; i++) {
        if (!lines[i].startsWith(".")) {
            await values.push(lines[i].split(","));
        }
    }
    for (let i = 0; i < values.length; i++) {
        if (values[i].length == 5) {
            await graph1Data[0].x.push(counter);
            await graph2Data[0].x.push(counter);
            await graph1Data[1].x.push(counter);
            await graph2Data[1].x.push(counter);
            await graph4Data[0].x.push(counter);
            await graph1Data[0].y.push(parseFloat(values[i][0]));
            await graph2Data[0].y.push(parseFloat(values[i][1]));
            await graph1Data[1].y.push(parseFloat(values[i][2]));
            await graph2Data[1].y.push(parseFloat(values[i][3]));
            await graph4Data[0].y.push(parseFloat(values[i][4]));
            counter += 10;
        } else if (values[i].length == 3) {
            await graph3Data[0].x.push(counter);
            await graph3Data[1].x.push(counter);
            await graph5Data[0].x.push(counter);
            await graph3Data[0].y.push(parseFloat(values[i][0]));
            await graph3Data[1].y.push(parseFloat(values[i][1]));
            await graph5Data[0].y.push(parseFloat(values[i][2]));
        }
    }
    await plotlib.stack(graph1Data);
    await plotlib.stack(graph2Data);
    await plotlib.stack(graph3Data);
    await plotlib.stack(graph4Data);
    await plotlib.stack(graph5Data);
    plotlib.plot();
    const browser = await puppeteer.launch();
    const page = await browser.newPage();
    page.emulate({
        userAgent:
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4196.0 Safari/537.36 Edg/86.0.573.0",
        viewport: { width: 1400, height: 610, isLandscape: true },
    });
    await page.goto("http://localhost:8080/plots/0/index.html", {
        waitUntil: "networkidle2",
    });
    await page.pdf({
        path: `./logs/${time}/index.pdf`,
        format: "Letter",
        landscape: true,
        margin: { top: 70, bottom: 70, right: 10, left: 10 },
    });
    await browser.close();
}

createGraph();

// prosv5 terminal | Out-File -FilePath C:\Users\vedag\Documents\GitHub\VEX-90819-2021\90819A\output.log
