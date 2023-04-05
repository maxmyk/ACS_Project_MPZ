from flask import render_template
from app import app


# @app.route('/')
# def login():
#     return render_template('login.html')

@app.route('/<int:hubId>')
def info(hubId):
    # return jsonify(container.getAllValues(hubId))
    return render_template('info.html', id=hubId)
