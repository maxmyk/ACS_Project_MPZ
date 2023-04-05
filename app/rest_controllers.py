from flask import jsonify, make_response, request
from app import container
from app import app


@app.route('/api/v1/get_data/<int:hub_id>', methods=['GET'])
def get_data(hub_id):
    return make_response(jsonify(container.getLastValue(hub_id)), 200)


@app.route('/api/v1/collect_data', methods=['POST'])
def collect_data():
    container.addValue(request.json["id"], request.json)
    return make_response(jsonify({'status': 'processing'}), 202)


# async def add_to_container(data):
#     await asyncio.sleep(0)
#     container.addValue(data["id"], data)


# @app.route('/api/v1/update_data', methods=['PUT'])
# def update_data():
#     return make_response(jsonify({'status': 'updated'}), 200)


@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Wrong request format'}), 404)
