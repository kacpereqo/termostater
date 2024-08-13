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
        if value < -55 or value > 125:
            raise ValueError("temperature must be between -55 and 125")
        return value


class TemperatureReadingCreation(SQLModel):
    serial_number: str
    temperature: float
