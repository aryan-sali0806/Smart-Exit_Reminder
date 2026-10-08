from fastapi import APIRouter

from app.schemas.item import ItemCreate

router = APIRouter(tags=["items"])


@router.post("/items")
async def create_item(item: ItemCreate):
    # TODO: Phase 7 — persist to MongoDB via items repository
    return {"message": "placeholder — item registration not yet implemented", "epc": item.epc}


@router.get("/items")
async def list_items():
    # TODO: Phase 7 — query items collection from MongoDB
    return {"items": []}
