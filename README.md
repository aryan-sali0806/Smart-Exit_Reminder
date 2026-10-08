# Smart Exit Reminder System

**Context-Aware Smart Exit Reminder System Using Long-Range Passive UHF RFID**

An IoT system that detects which RFID-tagged items you are carrying when leaving
a room and reminds you of missing essentials based on current context: weather
conditions and your academic schedule.

---

## System Architecture

```
PIR Sensor
    ↓
ESP32
    ↓
YRM100 UHF RFID Reader
    ↓
Detected EPCs
    ↓ Wi-Fi
FastAPI Backend
    ↓
Contextual Rule Engine
    ├── Base Required Items
    ├── Weather (OpenWeatherMap)
    └── Academic Calendar (Google Calendar)
    ↓
Missing Items
    ↓
ESP32 → MAX98357A I2S Amplifier → Speaker
```

The backend also communicates with:
- **MongoDB** — items and exit event storage
- **React Dashboard** — real-time exit events via WebSocket

---

## Repository Structure

```
Smart-Exit-Reminder/
├── firmware/esp32/          # PlatformIO — ESP32 (C++, Arduino)
├── backend/                 # FastAPI — Python backend
│   ├── app/
│   │   ├── api/             # Route handlers
│   │   ├── core/            # Config / settings
│   │   ├── schemas/         # Pydantic request/response models
│   │   ├── services/        # Weather & Calendar integrations
│   │   ├── rules/           # Contextual rule engine
│   │   ├── database/        # MongoDB connection & repositories
│   │   └── websocket/       # WebSocket connection manager
│   ├── tests/
│   ├── requirements.txt
│   └── .env.example
├── dashboard/               # React + Vite + TypeScript + Tailwind CSS
├── docs/                    # Architecture, API, and development docs
├── docker-compose.yml       # MongoDB service
└── README.md
```

---

## Quick Start

See [docs/development.md](docs/development.md) for full setup instructions.

```bash
# 1. Start MongoDB
docker-compose up -d

# 2. Start backend
cd backend && uvicorn app.main:app --reload

# 3. Start dashboard
cd dashboard && npm run dev

# 4. Build/upload firmware (requires PlatformIO)
cd firmware/esp32 && pio run --target upload
```

---

## Development Phases

| Phase | Feature                          | Status      |
|-------|----------------------------------|-------------|
| 1     | ESP32 + PIR sensor               | Pending     |
| 2     | ESP32 + YRM100 RFID reader       | Pending     |
| 3     | ESP32 Wi-Fi → FastAPI            | Pending     |
| 4     | Backend rule engine              | Pending     |
| 5     | Weather + Calendar integration   | Pending     |
| 6     | MAX98357A I2S audio output       | Pending     |
| 7     | MongoDB persistence              | Pending     |
| 8     | React dashboard + WebSockets     | Pending     |

---

## Documentation

- [Architecture](docs/architecture.md)
- [API Reference](docs/api.md)
- [Development Setup](docs/development.md)
