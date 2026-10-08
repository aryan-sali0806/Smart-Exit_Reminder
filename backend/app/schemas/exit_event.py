from pydantic import BaseModel
from typing import List


class ExitEventCreate(BaseModel):
    detected_epcs: List[str]


class ExitEventResponse(BaseModel):
    timestamp: str
    detected_epcs: List[str]
    required_items: List[str]
    missing_items: List[str]
    status: str
