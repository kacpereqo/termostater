from db.db import DB
from fastapi import APIRouter, Depends
from models.config import SensorConfig

router = APIRouter(tags=["config"])
db = DB()


@router.get("/config/{serial_number}")
def getSensorConfig(serial_number: str) -> SensorConfig:
    return db.getSensorConfig(serial_number)


@router.post("/config/{serial_number}", status_code=201)
def postSensorConfig(serial_number: str, config: SensorConfig = Depends()):
    db.postSensorConfig(config)
