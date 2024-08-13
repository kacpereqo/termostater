from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from utils import include_routes, lifespan


def getApp() -> FastAPI:
    app = FastAPI(lifespan=lifespan)
    app.add_middleware(
        CORSMiddleware,
        allow_origins=["*"],
        allow_credentials=True,
        allow_methods=["*"],
        allow_headers=["*"],
    )

    include_routes(app)

    return app


app = getApp()
