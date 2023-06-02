from flask import render_template
from app import app


# @app.route('/')
# def login():
#     return render_template('login.html')

@app.route('/<int:hubId>/<int:sensorId>')
def info(hubId, sensorId):
    # return jsonify(container.getAllValues(hubId))
    return render_template('info.html', hubId=hubId, sensorId=sensorId)
