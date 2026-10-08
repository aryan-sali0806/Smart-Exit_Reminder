from pydantic import BaseModel


class ItemCreate(BaseModel):
    epc: str
    name: str
    always_required: bool = True


class ItemResponse(BaseModel):
    epc: str
    name: str
    always_required: bool
