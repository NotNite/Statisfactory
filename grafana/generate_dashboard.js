const fs = require("fs");
const template = JSON.parse(
  fs.readFileSync("./data/dashboard_template.json", "utf8")
);
const max = JSON.parse(fs.readFileSync("./data/max.json", "utf8"));
const out = "./cfg/grafana/dashboards/statisfactory.json";

const panel = template.panels.find((p) => p.title === "Dimensional Depots");
panel.fieldConfig.defaults.overrides = Object.entries(max).map(
  ([key, value]) => ({
    matcher: {
      id: "byName",
      options: key
    },
    properties: [
      {
        id: "max",
        value: value
      }
    ]
  })
);

fs.writeFileSync(out, JSON.stringify(template, null, 2));
