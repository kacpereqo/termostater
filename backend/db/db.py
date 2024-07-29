import db.models
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
                func(self, session, *args, **kwargs)

        return inner

    @getSession
    def insertReading(self, session, reading: db.models.TemperatureReading) -> None:
        session.add(reading)
        session.commit()
        session.refresh(reading)
