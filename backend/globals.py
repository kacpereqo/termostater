from backend.db.db import DB
from backend.sensor import Sensor

db: DB | None = None
sensors: list[Sensor] | None = None
