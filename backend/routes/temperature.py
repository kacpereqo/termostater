from db.db import DB
from db.models import TemperatureReading
from fastapi import APIRouter, Depends, Response

router = APIRouter(tags=["temperature"])

db = DB()


@router.post("/reading")
def postReading(reading: TemperatureReading = Depends()) -> Response:
    TemperatureReading.model_validate(reading)
    db.insertReading(reading)

    return Response(status_code=201)


@router.get("/reading")
def getReading() -> list[TemperatureReading]:
    return db.getReadings()


@router.get("/reading/{serial_number}")
def getReadingBySerial(serial_number: str) -> TemperatureReading:
    return db.getReadingsBySerial(serial_number)
