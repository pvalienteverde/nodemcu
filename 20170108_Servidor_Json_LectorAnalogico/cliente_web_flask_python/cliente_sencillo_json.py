from flask import Flask, redirect, url_for, request,render_template, jsonify
import requests
from flask_oauth import OAuth
app = Flask(__name__)

GOOGLE_CLIENT_ID = '1053354725313-jah129a5g9ke3vbo65tqopq1q4n5amld.apps.googleusercontent.com'
GOOGLE_CLIENT_SECRET = 'f56CReMEIyjHthJV5RTwx3k2'
REDIRECT_URI = '/authorized'  # one of the Redirect URIs from Google APIs console

SECRET_KEY = 'development key'

oauth = OAuth()
google = oauth.remote_app('google',
                          base_url='https://www.google.com/accounts/',
                          authorize_url='https://accounts.google.com/o/oauth2/auth',
                          request_token_url=None,
                          request_token_params={'scope': 'https://www.googleapis.com/auth/userinfo.email',
                                                'response_type': 'code'},
                          access_token_url='https://accounts.google.com/o/oauth2/token',
                          access_token_method='POST',
                          access_token_params={'grant_type': 'authorization_code'},
                          consumer_key=GOOGLE_CLIENT_ID,
                          consumer_secret=GOOGLE_CLIENT_SECRET)
    
def Enviar(rele):
    parametros = {'rele': rele,'ldr':'estado'}
    respuesta = requests.get('http://192.168.0.150/request?', params=parametros)
    valores=respuesta.json()
    return ('Valor de LDR: ' + valores['ldr'])

@app.route('/habitacion_principal/rele<rele>')
def habitacion_principal(rele):
    mensaje_esp=Enviar(rele)
    return '%s' % mensaje_esp

@app.route('/panel',methods = ['POST', 'GET'])
def panel():
    if request.method == 'POST':
        print ("Post")
        rele = request.form['rele']
        return redirect(url_for('habitacion_principal',rele = rele))
    else:
        rele = request.form['rele']
        return redirect(url_for('habitacion_principal',rele = rele))
        #return render_template('panel.html',name = user)

@app.route('/_refrescar', methods= ['GET'])
def refrescar():
    parametros = {'ldr':'estado'}
    respuesta = requests.get('http://192.168.0.150/request?', params=parametros)
    valores=respuesta.json()
    return jsonify(ldr=valores['ldr'])

@app.route('/_orden_refrescar', methods= ['GET'])
def orden_refrescar():
    rele = request.args.get('rele', "off")
    parametros = {'rele':rele, 'ldr':'estado'}
    respuesta = requests.get('http://192.168.0.150/request?', params=parametros)
    valores=respuesta.json()
    return jsonify(ldr=valores['ldr'])

@app.route('/',methods = ['POST', 'GET'])
def index():
    return render_template('panel.html')

if __name__ == '__main__':
    app.run(host='192.168.0.133',port='8000')
#     app.run(host='localhost',port='8000')
