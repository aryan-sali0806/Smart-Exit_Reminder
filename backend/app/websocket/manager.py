# TODO: Phase 8 — WebSocket connection manager
#
# Manages active WebSocket connections from the React dashboard.
# Broadcasts exit events in real time when ESP32 triggers a scan.
#
# class ConnectionManager:
#     def __init__(self):
#         self.active_connections: list[WebSocket] = []
#
#     async def connect(self, websocket: WebSocket):
#         await websocket.accept()
#         self.active_connections.append(websocket)
#
#     def disconnect(self, websocket: WebSocket):
#         self.active_connections.remove(websocket)
#
#     async def broadcast(self, message: dict):
#         for connection in self.active_connections:
#             await connection.send_json(message)
