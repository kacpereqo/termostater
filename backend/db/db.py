from operator import ge

import db.models
from sqlmodel import Session, SQLModel, create_engine, select


class DB:
    instance = None

    def __new__(cls):
        if cls.instance is None:
            cls.instance = super().__new__(cls)
            cls.instance.engine = create_engine("sqlite:///database.sqlite")
            SQLModel.metadata.create_all(cls.instance.engine)
        return cls.instance

    def getSession(func):
        def inner(self, *args, **kwargs):
            with Session(self.engine) as session:
                return func(self, session, *args, **kwargs)

        return inner

    @getSession
    def insertReading(self, session, reading: db.models.TemperatureReading) -> None:
        session.add(reading)
        session.commit()
        session.refresh(reading)

    @getSession
    def getReadings(self, session) -> db.models.TemperatureReading:
        return session.query(db.models.TemperatureReading).all()

    @getSession
    def getReadingsBySerial(
        self, session, serial_number: str
    ) -> db.models.TemperatureReading:

        return (
            session.query(db.models.TemperatureReading)
            .filter(db.models.TemperatureReading.serial_number == serial_number)
            .all()
        )

    @getSession
    def insertBatteryReading(self, session, reading: db.models.BatteryReading) -> None:
        reading = db.models.BatteryReading(reading)
        session.add(reading)
        session.commit()
        session.refresh(reading)

    @getSession
    def getBatteryReadings(self, session) -> db.models.BatteryReading:
        return session.query(db.models.BatteryReading).all()

    @getSession
    def getLatestTemperatureReading(
        self, session, count: int = 1
    ) -> db.models.TemperatureReading:
        return (
            session.query(db.models.TemperatureReading)
            .order_by(db.models.TemperatureReading.timestamp.desc())
            .limit(count)
            .all()
        )
