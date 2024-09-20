import "dotenv/config";
import express from "express";
import client, { register } from "prom-client";
import { CronJob } from "cron";

const app = express();
app.get("/metrics", async (_req, res) => {
  try {
    res.set("Content-Type", register.contentType);
    res.end(await register.metrics());
  } catch (err) {
    res.status(500).end(err);
  }
});
app.listen(process.env.PORT);

process.env.NODE_TLS_REJECT_UNAUTHORIZED = "0"; // :(

async function execute(command) {
  const req = await fetch(process.env.GAME_ENDPOINT, {
    method: "POST",
    body: JSON.stringify({ function: command }),
    headers: {
      "Content-Type": "application/json"
    }
  });
  const data = await req.json();
  if (!req.ok) {
    console.error(data);
    throw new Error(data);
  }
  return data.data.data;
}

const prefix = "Statisfactory";
const getPower = prefix + "_GetPower";
const getDepots = prefix + "_GetDepots";

const powerConsumed = new client.Gauge({
  name: "power_consumed",
  help: "Power consumed"
});
const powerProduced = new client.Gauge({
  name: "power_produced",
  help: "Power produced"
});
const powerProductionCapacity = new client.Gauge({
  name: "power_production_capacity",
  help: "Power production capacity"
});
const maximumPowerConsumption = new client.Gauge({
  name: "maximum_power_consumption",
  help: "Maximum power consumption"
});
const batteryPowerInput = new client.Gauge({
  name: "battery_power_input",
  help: "Battery power input"
});

const depotItem = new client.Gauge({
  name: "depot",
  help: "Depot items",
  labelNames: ["item"]
});

async function doPowerGrid() {
  const powerGrid = await execute(getPower);
  if (powerGrid.length < 1) return;

  // Pick the most active power grid
  const mainGrid = powerGrid.reduce((acc, cur) => {
    if (cur.powerProduced > acc.powerProduced) return cur;
    return acc;
  });

  powerConsumed.set(mainGrid.powerConsumed);
  powerProduced.set(mainGrid.powerProduced);
  powerProductionCapacity.set(mainGrid.powerProductionCapacity);
  maximumPowerConsumption.set(mainGrid.maximumPowerConsumption);
  batteryPowerInput.set(mainGrid.batteryPowerInput);
}

async function doDepots() {
  const depots = await execute(getDepots);
  for (const [item, count] of Object.entries(depots)) {
    depotItem.labels({ item }).set(count);
  }
}

async function run() {
  try {
    await doPowerGrid();
  } catch (e) {
    console.error(e);
  }

  try {
    await doDepots();
  } catch (e) {
    console.error(e);
  }
}

const job = new CronJob(
  // Every 5 seconds on the clock
  "*/5 * * * * *",
  async () => {
    try {
      await run();
    } catch (e) {
      console.error(e);
    }
  },
  null, // on complete
  false, // start instantly
  "America/New_York"
);
job.start();
