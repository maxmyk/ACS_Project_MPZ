from flask import Flask
from app.connection import ConnectionDB

app = Flask(__name__)

container = ConnectionDB()
