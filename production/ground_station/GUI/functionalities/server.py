from flask_cors import CORS

from flask import Flask
from flask import jsonify
import json

app = Flask(__name__)
CORS(app)

@app.route('/')
def send_data():
    with open('data.txt','r') as f:
        raw_data = f.read().splitlines()[-1]
        json_data = json.loads(raw_data)
        return jsonify(json_data)


app.run()