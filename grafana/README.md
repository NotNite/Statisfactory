# Statisfactory + Grafana

This Docker Compose stack sets up a Grafana instance automatically. It uses my personal config, but you're free to change it if you like.

## How it works

Think of it as a chain of servers talking to each other:

- Your Satisfactory game server exposes the relevant stats
- The Statisfactory scraper node periodically fetches data from the game server
- Prometheus (metric software) periodically fetches data from the scraper node
- Grafana (graphing software) periodically fetches data from Prometheus

## Requirements

- A running Satisfactory server with Statisfactory installed
- A server to run Grafana on with [Docker](https://docs.docker.com/engine/install) installed
- Git (to clone this repository)
- Some knowledge of the command line (moving around and editing files)

## Setup

- In Server Manager > (your server) > Console, run the command `server.GenerateAPIToken`
  - Save this for later, it should start with `ew`
- Clone this repository: `git clone https://github.com/NotNite/Statisfactory.git`
- Go into this folder: `cd Statisfactory/grafana`
- Create your own environment variable: `cp .env.example .env`
- Edit the `.env` file
  - Enter your API key for the server
  - Change your [time zone](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones)
  - Change the server IP if required
- (Optional) If port 3000 is taken on your machine, edit the port for the Grafana server in `compose.yaml`
- Bring up the stack: `docker compose up --build -d`
- Go to `http://<your server ip>:3000/`
  - If your server has a firewall, open the port
- Change the admin password on Grafana (default login is username `admin` password `admin`)
- (Optional, for advanced users) [Set up a reverse proxy for your Grafana instance](https://grafana.com/tutorials/run-grafana-behind-a-proxy/)

Have fun!
