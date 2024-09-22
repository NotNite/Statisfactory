# Statisfactory

HTTP API stats for Satisfactory.

## Setting up Grafana

If you've never used Grafana or Prometheus before, follow [this guide](https://github.com/NotNite/Statisfactory/blob/main/grafana/README.md) to set up a new Grafana instance on your server.

## Running the scraper

Run `server.GenerateAPIToken` in your server console, then create `scraper/.env`:

```text
GAME_ENDPOINT="https://localhost:7777/api/v1"
GAME_TOKEN="output of server.GenerateAPIToken"
PORT=8080
```

Then point a Prometheus node at `http://localhost:8080/metrics`.

## Credits

Statisfactory uses [Mutant Standard](https://mutant.tech/) emoji, licensed [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/).
