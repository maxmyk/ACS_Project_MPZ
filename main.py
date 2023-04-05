from app import app
from app import rest_controllers
from app import views

app.run(host='127.0.0.1', port=8080, debug=True)
