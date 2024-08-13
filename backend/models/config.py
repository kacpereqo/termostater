from sqlmodel import Field, SQLModel


class SensorConfig(SQLModel, table=True):
    serial_number: str = Field(primary_key=True)
    delay: int
    min_threshold_temperature: float | None
    max_threshold_temperature: float | None
    target_temperature: float | None = None
