#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Defina o SSID e a senha da rede Wi-Fi
const char *ssid = "EDMA_2Ghz";
const char *password = "casa2211";

// Defina o pino onde o LED está conectado
const int ledPin = 2; // O pino 2 é o LED embutido na maioria dos ESP32

// Crie um objeto AsyncWebServer na porta 80
AsyncWebServer server(80);

void setup()
{
  // Inicialize a comunicação serial
  Serial.begin(115200);

  // Configurar o pino do LED como saída
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // LED apagado inicialmente

  // Conecte-se à rede Wi-Fi
  WiFi.begin(ssid, password);

  // Aguarde até estar conectado
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Conectando à rede Wi-Fi...");
  }

  // Imprima o endereço IP
  Serial.println("Conectado à rede Wi-Fi");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Configurar a rota para a página web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", "<html><body><style>body{background-color: black; color: white; font-family: rosemary;} button{ border: none; font-family: rosemary; padding: 10px; font-weight: bold; margin: 15px;} button:hover{background-color: grey;} h1{margin: 5px 0px 0px 15px}</style><h1>Yamaha Lander 2020 ABS</h1><button onclick=\"fetch('/led/on')\">LIGAR MOTO</button><button onclick=\"fetch('/led/off')\">DESLIGAR MOTO</button></body></html>"); });

  // Configurar a rota para ligar o LED
  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    digitalWrite(ledPin, HIGH);
    request->send(200, "text/plain", "MOTO LIGADA"); });

  // Configurar a rota para desligar o LED
  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    digitalWrite(ledPin, LOW);
    request->send(200, "text/plain", "MOTO DESLIGADA"); });

  // Inicie o servidor
  server.begin();
}

void loop()
{
  // Não é necessário código no loop para o AsyncWebServer
}
