from flask import Flask, request
import numpy as np
import json
import logging
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)


app = Flask(__name__)

def multiply_matrix_vector(matrix, vector):
    return matrix@vector


@app.route('/send_matr',methods = ['POST'])
def send_matr():
   content = request.get_json()
   matrix = np.array(content['matr'])
   vector = np.array(content['vector'])
   return json.dumps((multiply_matrix_vector(matrix, vector)).tolist())


if __name__ == '__main__':
   app.run(debug = True)


