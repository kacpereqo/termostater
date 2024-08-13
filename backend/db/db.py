from models.battery import BatteryReading
from models.config import SensorConfig
from models.temperature import TemperatureReading
from sqlmodel import Session, SQLModel, create_engine


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
    def insertReading(self, session, reading: TemperatureReading) -> None:
        session.add(reading)
        session.commit()
        session.refresh(reading)

    @getSession
    def getReadings(self, session) -> TemperatureReading:
        return session.query(TemperatureReading).all()

    @getSession
    def getReadingsBySerial(self, session, serial_number: str) -> TemperatureReading:

        return (
            session.query(TemperatureReading)
            .filter(TemperatureReading.serial_number == serial_number)
            .all()
        )

    @getSession
    def insertBatteryReading(self, session, reading: BatteryReading) -> None:
        reading = BatteryReading(reading)
        session.add(reading)
        session.commit()
        session.refresh(reading)

    @getSession
    def getBatteryReadings(self, session) -> BatteryReading:
        return session.query(BatteryReading).all()

    @getSession
    def getLatestTemperatureReading(
        self, session, count: int = 1
    ) -> TemperatureReading:
        return (
            session.query(TemperatureReading)
            .order_by(TemperatureReading.timestamp.desc())
            .limit(count)
            .all()
        )

    @getSession
    def getSensorConfig(self, session, serial_number: str) -> SensorConfig:

        config = (
            session.query(SensorConfig)
            .filter(SensorConfig.serial_number == serial_number)
            .first()
        )

        if config is None:
            config = SensorConfig(
                serial_number=serial_number,
                min_threshold_temperature=None,
                max_threshold_temperature=None,
                target_temperature=None,
                delay=5 * 60,
            )
            session.add(config)
            session.commit()
            session.refresh(config)

        return config

    @getSession
    def postSensorConfig(self, session, config: SensorConfig) -> None:
        session.query(SensorConfig).filter(
            SensorConfig.serial_number == config.serial_number
        ).update(
            {
                SensorConfig.min_threshold_temperature: config.min_threshold_temperature,
                SensorConfig.max_threshold_temperature: config.max_threshold_temperature,
                SensorConfig.target_temperature: config.target_temperature,
                SensorConfig.delay: config.delay,
            }
        )
        session.commit()
