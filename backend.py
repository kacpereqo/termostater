import sqlite3

from fastapi import Depends, FastAPI, Response
from pydantic import BaseModel


def getApp() -> FastAPI:
    app = FastAPI()

    return app


app = getApp()


class Reading(BaseModel):
    serial_number: str
    temperature: float
    timestamp: str


@app.post("/reading")
def postReading(reading: Reading = Depends()) -> Response:
    conn = sqlite3.connect("readings.sqlite")
    c = conn.cursor()

    c.execute(
        """
        CREATE TABLE IF NOT EXISTS readings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            serial_number TEXT,
            temperature REAL,
            timestamp TEXT)
        
        """
    )

    c.execute(
        """
        INSERT INTO readings (serial_number, temperature, timestamp)
        VALUES (?, ?, ?)
        """,
        (reading.serial_number, reading.temperature, reading.timestamp),
    )

    conn.commit()

    return Response(status_code=201)


@app.get("/reading")
def getReading() -> list[Reading]:
    conn = sqlite3.connect("readings.sqlite")
    c = conn.cursor()

    c.execute(
        """
        SELECT * FROM readings
        """
    )

    readings = c.fetchall()

    result = [
        {
            "serial_number": reading[1],
            "temperature": reading[2],
            "timestamp": reading[3],
        }
        for reading in readings
    ]

    return result


@app.get("/reading/{serial_number}")
def getReadingBySerialNumber(serial_number: str) -> list[Reading]:
    conn = sqlite3.connect("readings.sqlite")
    c = conn.cursor()

    c.execute(
        """
        SELECT * FROM readings
        WHERE serial_number = ?
        """,
        (serial_number,),
    )

    readings = c.fetchall()

    return readings


if __name__ == "__main__":
    import uvicorn

    uvicorn.run("backend:app", reload=True)
