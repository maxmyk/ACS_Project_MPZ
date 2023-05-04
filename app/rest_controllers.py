from flask import jsonify, make_response, request
from app import container, app


@app.route('/api/v1/get_data/<int:hub_id>', methods=['GET'])
async def get_data(hub_id):
    data = await container.get_last_value(hub_id)
    return make_response(jsonify(data), 200)


@app.route('/api/v1/collect_data', methods=['POST'])
async def collect_data():
    data = request.json
    await container.add_value(data["id"], data)
    return make_response(jsonify({'status': 'processing'}), 202)


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Wrong request format'}), 404)
