from flask import jsonify, make_response, request
from app import app, container


@app.route('/api/v1/get_data/<int:hub_id>/<int:sensor_id>', methods=['GET'])
def get_data(hub_id, sensor_id):
    data = container.getLastValue(hub_id, sensor_id)
    print(data)
    return make_response(jsonify(data), 200)


@app.route('/api/v1/collect_data', methods=['POST'])
def collect_data():
    data = request.json
    container.addValue(data["hub_id"], data["id"], data)
    print(data)
    return make_response(jsonify({'status': 'processing'}), 202)


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Wrong request format'}), 404)
