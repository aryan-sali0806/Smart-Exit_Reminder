# Development Setup

## Prerequisites

| Tool | Version |
|------|---------|
| PlatformIO Core | 6+ |
| Python | 3.11+ |
| Node.js | 20+ |
| MongoDB | 7+ (or Docker) |

---

## 1. ESP32 Firmware

The firmware project lives in `firmware/esp32/` and is managed by PlatformIO.

### Build

```bash
cd firmware/esp32
pio run
```

### Upload to ESP32

```bash
cd firmware/esp32
pio run --target upload
```

### Open Serial Monitor

```bash
cd firmware/esp32
pio device monitor --baud 115200
```

---

## 2. FastAPI Backend

### Install dependencies

```bash
cd backend
python -m venv .venv

# Windows
.venv\Scripts\activate

# macOS / Linux
source .venv/bin/activate

pip install -r requirements.txt
```

### Configure environment

```bash
cd backend
cp .env.example .env
# Open .env and fill in values as needed
```

### Start the development server

```bash
cd backend
uvicorn app.main:app --reload
```

- API base: `http://localhost:8000`
- Swagger UI: `http://localhost:8000/docs`
- ReDoc: `http://localhost:8000/redoc`

---

## 3. React Dashboard

### Install dependencies

```bash
cd dashboard
npm install
```

### Start the development server

```bash
cd dashboard
npm run dev
```

Dashboard runs at: `http://localhost:5173`

---

## 4. MongoDB

### Via Docker (recommended for development)

```bash
# From the project root
docker-compose up -d
```

MongoDB will be available at `mongodb://localhost:27017`.

### Via local installation

Install MongoDB Community Edition from https://www.mongodb.com/try/download/community
and start the `mongod` service.

---

## Communication Overview

```
ESP32 (Arduino/C++)
  └─→ HTTP POST /api/exit ──→ FastAPI (port 8000)
                                  ├─→ MongoDB (port 27017)  [Phase 7]
                                  └─→ WebSocket ──→ React Dashboard (port 5173)  [Phase 8]
```
