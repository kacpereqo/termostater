from datetime import datetime

from sqlmodel import Field, SQLModel


class BatteryReading(SQLModel, table=True):
    id: int = Field(default=None, primary_key=True)
    timestamp: int = Field(default_factory=lambda: datetime.now().timestamp())
    serial_number: str
    voltage: float
