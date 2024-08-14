from datetime import datetime

from pydantic import field_validator
from sqlmodel import Field, SQLModel


class TemperatureReading(SQLModel, table=True):
    id: int | None = Field(default=None, primary_key=True)
    timestamp: float = Field(default_factory=lambda: datetime.now().timestamp())
    serial_number: str
    temperature: float

    @field_validator("temperature")
    def validate_temperature(cls, value):
        THERMOMETER_MIN = -127
        THERMOMETER_MAX = 127
        if value < THERMOMETER_MIN or value > THERMOMETER_MAX:
            raise ValueError("temperature must be between -127 and 127")
        return value


class TemperatureReadingCreation(SQLModel):
    serial_number: str
    temperature: float
