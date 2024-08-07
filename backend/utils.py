import routes.battery
import routes.temperature
from fastapi import FastAPI


def include_routes(app: FastAPI):
    app.include_router(routes.temperature.router)
    app.include_router(routes.battery.router)
