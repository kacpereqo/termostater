from db.db import DB
from fastapi import APIRouter, Depends, Response
from models.temperature import TemperatureReading, TemperatureReadingCreation

router = APIRouter(tags=["temperature"])

db = DB()


@router.post("/reading")
def postReading(reading: TemperatureReadingCreation = Depends()) -> Response:
    temp = TemperatureReading.model_validate(reading)
    db.insertReading(temp)

    return Response(status_code=201)


@router.get("/reading")
def getReading() -> list[TemperatureReading]:
    return db.getReadings()


@router.get("/reading/{serial_number}")
def getReadingBySerial(serial_number: str) -> TemperatureReading:
    return db.getReadingsBySerial(serial_number)
