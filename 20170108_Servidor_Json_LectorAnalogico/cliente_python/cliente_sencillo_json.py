import requests

def Main():
    while(1): 
        rele = input("Rele on/off: ")
        
        parametros = {'rele': rele,'ldr':'estado'}
        respuesta = requests.get('http://192.168.0.150/request?', params=parametros)
        print(respuesta.text)

     
if __name__ == '__main__':
    Main()
