import time
import requests
import random

while True:
    # for _ in range(100):
    data = {
        "id": 1,
        "temperature": random.randint(1, 40),
        "volume": random.randint(1, 100),
        "humidity": random.randint(1, 100)
    }
    response = requests.post("http://127.0.0.1:8080//api/v1/collect_data", json=data)
    time.sleep(1)
