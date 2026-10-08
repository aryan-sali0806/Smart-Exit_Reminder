from fastapi import APIRouter

from app.schemas.exit_event import ExitEventCreate

router = APIRouter(tags=["exits"])


@router.post("/exit")
async def process_exit(event: ExitEventCreate):
    # TODO: Phase 3+ — resolve EPCs, run rule engine, return missing items
    return {
        "message": "placeholder — exit processing not yet implemented",
        "received_epcs": event.detected_epcs,
    }


@router.get("/exits")
async def list_exits():
    # TODO: Phase 7 — query exit_events collection from MongoDB
    return {"exits": []}
