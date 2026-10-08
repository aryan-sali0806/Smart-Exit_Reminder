# Architecture

## Overview

The Smart Exit Reminder System detects which RFID-tagged items are in range of a
UHF RFID reader when a user exits a room, then cross-references those detections
against a contextual rule engine to identify missing essentials and announce them
via a speaker.

---

## Component Diagram

```
┌──────────────────────────────────────────────────────────┐
│                     ESP32 Firmware                       │
│                                                          │
│  PIR Sensor  ──→  Trigger RFID scan                     │
│  YRM100      ──→  Read EPCs over UART                   │
│  Wi-Fi       ──→  POST /api/exit  to FastAPI backend    │
│  MAX98357A   ←──  Receive missing-item list, play audio │
└──────────────────────────────────────────────────────────┘
                           │
                     HTTP / Wi-Fi
                           │
┌──────────────────────────────────────────────────────────┐
│                   FastAPI Backend                        │
│                                                          │
│  POST /api/exit  ──→  Rule Engine                       │
│  Rule Engine     ──→  Weather Service (OpenWeatherMap)  │
│  Rule Engine     ──→  Calendar Service (Google Calendar)│
│  Rule Engine     ──→  Determine missing items           │
│  WebSocket       ──→  Push event to React dashboard     │
│  Motor (async)   ──→  MongoDB                           │
└──────────────────────────────────────────────────────────┘
          │                          │
  ┌───────┴──────┐          ┌────────┴────────┐
  │   MongoDB    │          │  React Dashboard │
  │  (port 27017)│          │  (port 5173)     │
  └──────────────┘          └─────────────────┘
```

---

## Technology Stack

| Layer      | Technology                              |
|------------|-----------------------------------------|
| Firmware   | C++, Arduino framework, PlatformIO      |
| Backend    | Python 3.11+, FastAPI, Pydantic v2      |
| Database   | MongoDB 7+, Motor (async driver)        |
| Dashboard  | React 18, Vite, TypeScript, Tailwind CSS|
| Ext. APIs  | OpenWeatherMap, Google Calendar         |

---

## Data Models

### Item (`items` collection)

```json
{
  "epc":            "string  — UHF RFID EPC tag identifier",
  "name":           "string  — human-readable item name",
  "always_required": true,
  "weather_rules":  {},
  "schedule_rules": {},
  "created_at":     "datetime"
}
```

### Exit Event (`exit_events` collection)

```json
{
  "timestamp":      "datetime",
  "detected_epcs":  ["string"],
  "required_items": ["string"],
  "missing_items":  ["string"],
  "status":         "string  — ok | warning | alert"
}
```

---

## Development Phases

| Phase | Feature                          |
|-------|----------------------------------|
| 1     | ESP32 + PIR sensor               |
| 2     | ESP32 + YRM100 RFID reader       |
| 3     | ESP32 Wi-Fi → FastAPI            |
| 4     | Backend rule engine              |
| 5     | Weather + Calendar integration   |
| 6     | MAX98357A I2S audio output       |
| 7     | MongoDB persistence              |
| 8     | React dashboard + WebSockets     |
