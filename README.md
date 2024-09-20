# Statisfactory

HTTP API stats for Satisfactory.

## TODO

- Expose more data
- Proper authentication (there is currently no auth lmao)
- Make scraper use the certificates from the server
- Publish to SMR

## Building

- Set up [the Satisfactory 1.0 toolchain](https://docs-dev.ficsit.app/satisfactory-modding/latest/Development/BeginnersGuide/index.html)
- Manually add `friend class` into the headers because the access transformers are broken
  - Someone who actually knows what they're doing help me kthx
- Copy the built mod to `FactoryGame/Mods/Statisfactory` in your dedicated server
- Profit

## Running the scraper

Create `scraper/.env`:

```text
GAME_ENDPOINT="https://localhost:7777/api/v1"
PORT=8080
```

Then point a Prometheus node at `http://localhost:8080/metrics`.
