# API Reference

Base URL: `http://localhost:8000`

Interactive docs (Swagger UI): `http://localhost:8000/docs`

---

## GET /api/health

Backend health check.

**Response**
```json
{ "status": "ok" }
```

---

## POST /api/items

Register an RFID EPC with an item name.

**Request body**
```json
{
  "epc":             "EPC_A",
  "name":            "College ID",
  "always_required": true
}
```

**Response**
```json
{
  "message": "placeholder — item registration not yet implemented",
  "epc":     "EPC_A"
}
```

> Phase 7: will persist to MongoDB `items` collection.

---

## GET /api/items

List all registered RFID items.

**Response**
```json
{
  "items": []
}
```

> Phase 7: will return documents from MongoDB `items` collection.

---

## POST /api/exit

Called by the ESP32 after a PIR-triggered RFID scan completes.
Sends the detected EPC list; backend resolves missing items.

**Request body**
```json
{
  "detected_epcs": ["EPC_A", "EPC_B"]
}
```

**Response**
```json
{
  "message":       "placeholder — exit processing not yet implemented",
  "received_epcs": ["EPC_A", "EPC_B"]
}
```

> Phase 3+: will run rule engine and return `missing_items`.
> Phase 8: will also push event to dashboard via WebSocket.

---

## GET /api/exits

List previous exit events.

**Response**
```json
{
  "exits": []
}
```

> Phase 7: will return documents from MongoDB `exit_events` collection.
