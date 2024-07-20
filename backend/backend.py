import sqlite3
from datetime import datetime

from fastapi import Depends, FastAPI, Response
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from sqlmodel import Field, Session, SQLModel, create_engine


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


class Reading(BaseModel):
    serial_number: str
    temperature: float
    timestamp: str | None = None


@app.post("/reading")
def postReading(reading: Reading = Depends()) -> Response:
    conn = sqlite3.connect("readings.sqlite")
    c = conn.cursor()

    if not reading.timestamp:
        reading.timestamp = datetime.now().timestamp()

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
