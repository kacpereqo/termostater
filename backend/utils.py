from contextlib import asynccontextmanager

from fastapi import FastAPI


def include_routes(app: FastAPI):
    import routes.battery
    import routes.config
    import routes.temperature

    app.include_router(routes.temperature.router)
    app.include_router(routes.battery.router)
    app.include_router(routes.config.router)


@asynccontextmanager
async def lifespan(app: FastAPI):
    print("Application startup")
    yield
    print("Application shutdown")
