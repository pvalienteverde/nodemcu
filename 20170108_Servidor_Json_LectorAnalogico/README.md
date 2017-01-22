# Servidor en NodeMcu v1.0 like Arduino. Features: Json, Lectura Analogica, 

En el siguiente proyecto se crea un servidor en nodemcu v1.0 programado como arduino en eclipse donde:

 * IP Estatica del servidor nodemcu: De esta manera se deja de forma clara la ip
 * Recencion como envio de las peticiones por json: Para ello utilizamos la libreria de ArduinoJson
 * Lectura analogica: Se lee el valor de una LDR apuntado a dos leds
 * Cliente Sencillo: Simple script en python para probar el servidor
 * Cliente en Flask: Siguiente paso para hacerlo amigable en web
 
## Instalacion para sistemas LINUX (FEDORA)

Se va a utilizar los siguientes programas:

 * **[platformio](http://docs.platformio.org/en/stable/installation.html)** Es una plataforma donde nos va a construir el proyecto de eclipse, pero tambein se podria utilizar para programar nodemcu en ArduinoIDE, Atom, ...
 * **[Eclipse con el pluin CDT (con la caracteristica GCC Cross Compiler Support)](http://www.eclipse.org/cdt/)** He elegido esta plataforma porque es la que utilizo para todos los lenguajes, aunque se puede utilizar cualquier otra que nos permita Platformio
 * **[ArduinoJson ](https://github.com/bblanchon/ArduinoJson)** Imprescindible para el envio de Json

Se entiende que ya tenemos eclipse con el CDT instalado, solo falta:

```bash
sudo pip2 install -U platformio 
mkdir ~/LibreriasArduinoExternas
cd ~/LibreriasArduinoExternas
git clone https://github.com/bblanchon/ArduinoJson.git
cd ~
git clone https://github.com/pvalienteverde/nodemcu/tree/master/20170108_Servidor_Json_LectorAnalogico
```

## Configuración
En rpoceso... hay que colgar capturas, etc
