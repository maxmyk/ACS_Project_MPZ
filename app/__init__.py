from flask import Flask
from app.container import Container

app = Flask(__name__)

container = Container()
