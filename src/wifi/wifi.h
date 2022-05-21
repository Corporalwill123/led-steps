#ifndef HEADER_I
#define HEADER_I

#include "main.h"

#include "functions/functions.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer librrgb
#include <string.h>

void wifiSetup();

void wifiLoop();

void handleRoot();

void handleRead();

void handleResponse();

void handleNotFound();

String getValue(String data, char separator, int index);

#endif