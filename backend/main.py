from datetime import datetime

from db.db import DB
from db.models import TemperatureReading
from fastapi import Depends, FastAPI, Response
from fastapi.middleware.cors import CORSMiddleware


def getApp() -> FastAPI:
    app = FastAPI()
    app.add_middleware(
        CORSMiddleware,
        allow_origins=["*"],
        allow_credentials=True,
        allow_methods=["*"],
        allow_headers=["*"],
    )

    return app


app = getApp()
db = DB()


temp = TemperatureReading(
    serial_number="1",
    temperature=25.0,
    timestamp=datetime.now().timestamp(),
)

db.insertReading(temp)


@app.post("/reading")
def postReading(reading: TemperatureReading = Depends()) -> Response:
    db.insertReading(reading)

    return Response(status_code=201)


# @app.get("/reading")
# def getReading() -> list[Reading]:
#     conn = sqlite3.connect("readings.sqlite")
#     c = conn.cursor()

#     c.execute(
#         """
#         SELECT * FROM readings
#         """
#     )

#     readings = c.fetchall()

#     result = [
#         {
#             "serial_number": reading[1],
#             "temperature": reading[2],
#             "timestamp": reading[3],
#         }
#         for reading in readings
#     ]

#     return result


# @app.get("/reading/{serial_number}")
# def getReadingBySerialNumber(serial_number: str) -> list[Reading]:
#     conn = sqlite3.connect("readings.sqlite")
#     c = conn.cursor()

#     c.execute(
#         """
#         SELECT * FROM readings
#         WHERE serial_number = ?
#         """,
#         (serial_number,),
#     )

#     readings = c.fetchall()

#     return readings
