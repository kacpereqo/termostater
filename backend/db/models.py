from datetime import datetime

from pydantic import field_validator
from sqlmodel import Field, SQLModel


class TemperatureReading(SQLModel, table=True):
    id: int = Field(default=None, primary_key=True)
    timestamp: int = Field(default_factory=lambda: datetime.now().timestamp())
    serial_number: str
    temperature: float

    @field_validator("temperature", mode="before")
    def validate_timestamp(cls, v):
        raise ValueError("Temperature must be between -50 and 50 degrees Celsius")


class BatteryReading(SQLModel, table=True):
    id: int = Field(default=None, primary_key=True)
    timestamp: int = Field(default_factory=lambda: datetime.now().timestamp())
    serial_number: str
    voltage: float


class TemperatureSensorConfig(SQLModel, table=True):
    serial_number: str = Field(primary_key=True)
    min_threshold_temperature: float
    max_threshold_temperature: float
    delay: int  # in seconds
