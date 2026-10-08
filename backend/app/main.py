from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from app.api import health, items, exits

app = FastAPI(
    title="Smart Exit Reminder API",
    version="0.1.0",
    description="Context-Aware Smart Exit Reminder System Using Long-Range Passive UHF RFID",
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(health.router, prefix="/api")
app.include_router(items.router, prefix="/api")
app.include_router(exits.router, prefix="/api")
