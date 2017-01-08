import requests

def Main():
    while(1): 
        lr = input("Led Azul: ")
        lv = input("Led Verde: ")
        
        parametros = {'led_rojo': lr,'led_verde': lv,'ldr':'estado'}
        respuesta = requests.get('http://192.168.1.150/request?', params=parametros)
        print(respuesta.text)

     
if __name__ == '__main__':
    Main()
