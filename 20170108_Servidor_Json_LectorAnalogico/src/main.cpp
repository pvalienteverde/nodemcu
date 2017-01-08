#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Arduino.h"
#include "ArduinoJson.h"
#include "AccesoWifi.h"

ESP8266WebServer server(80);

auto pin_azul = Pins_Arduino_h::D1;
auto pin_verde = Pins_Arduino_h::D2;

/**
 * Funcion que pasea los argumentos http://ip?argumento1=valor1&argumento2=valor2...
 */
void ArgumentosGenericos();
/**
 * Realiza las acciones
 * @param servidor Objeto ESP8266WebServer
 * @param valor    String del arguemnto accion
 * @return
 */
String LedRojo(ESP8266WebServer &servidor, const String &valor);
String LedVerde(ESP8266WebServer &servidor, const String &valor);
String LDR(ESP8266WebServer &servidor, const String &valor);
/**
 * Se realiza la configuracion del dispositivo
 */
void setup(void) {
	// Pin de entrada a 0
	pinMode(pin_azul, OUTPUT);
	digitalWrite(pin_azul, LOW);
	pinMode(pin_verde, OUTPUT);
	digitalWrite(pin_verde, LOW);

	// Configuracion a wifi a una ip fija para poder conectar
	// mas dispositivos similares
	IPAddress ip(192, 168, 1, 150);
	IPAddress gateway(192, 168, 1, 1);
	IPAddress subnet(255, 255, 255, 0);
	WiFi.config(ip, gateway, subnet);
	WiFi.begin(AccesiWifi::SSID, AccesiWifi::PASSWORD);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}

	server.on("/request", ArgumentosGenericos);
	server.begin();

}

/**
 * Se ejecuta las sentencias ciclicamente
 */
void loop(void) {
	server.handleClient(); // Espera solicitudes de los navegadores
}

void ArgumentosGenericos() { //Handler

	StaticJsonBuffer<500> jsonBuffer;
	JsonObject& json = jsonBuffer.createObject();

	for (int i = 0; i < server.args(); i++) {
		auto parametro = server.argName(i);
		auto valor = server.arg(i);
		if (parametro == "led_rojo") {
			json[parametro] = LedRojo(server, valor);
		} else if (parametro == "led_verde") {
			json[parametro] = LedVerde(server, valor);
		}
	}

	if (server.hasArg("ldr")) {
		delay(200); // Tiempo para que se encienda los leds
		json["ldr"] = LDR(server, server.arg("ldr"));
	}

	String json_serializado;
	json.printTo(json_serializado);

	server.send(200, "text / plain", json_serializado); //Response to the HTTP request

}

String LedRojo(ESP8266WebServer &servidor, const String &valor) {
	String mensaje("");
	if (valor == "0") {
		digitalWrite(pin_azul, LOW);
		mensaje += "0";
	} else if (valor == "1") {
		digitalWrite(pin_azul, HIGH);
		mensaje += "1";
	} else {
		mensaje += "NaN";

	}
	return mensaje.c_str();
}

String LedVerde(ESP8266WebServer &servidor, const String &valor) {
	String mensaje("");
	if (valor == "0") {
		digitalWrite(pin_verde, LOW);
		mensaje += "0";
	} else if (valor == "1") {
		digitalWrite(pin_verde, HIGH);
		mensaje += "1";
	} else {
		mensaje += "NaN";

	}
	return mensaje.c_str();
}

String LDR(ESP8266WebServer &servidor, const String &valor) {
	int valor_sensor = analogRead(A0);
	// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
	float voltaje = valor_sensor * (5.0 / 1023.0);
	String mensaje(voltaje);
	return mensaje;
}
