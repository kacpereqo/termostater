from db.db import DB
from fastapi import APIRouter, Depends, Response
from models.battery import BatteryReading

router = APIRouter(tags=["battery"])
db = DB()


@router.post("/battery/{serial_number}")
def postBatteryReading(reading: BatteryReading = Depends()) -> Response:
    db.insertBatteryReading(reading)
    return Response(status_code=201)


@router.get("/battery/{serial_number}")
def getBatteryReading(serial_number: str) -> BatteryReading:
    return db.getBatteryReading(serial_number)
