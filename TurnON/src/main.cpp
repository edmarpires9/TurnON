#include <Arduino.h>

void setup()
{
  // Inicializa a comunicação serial a 115200 bps
  Serial.begin(115200);
}

void loop()
{
  // Envia "Hello, World!" pela porta serial
  Serial.println("Hello, World!");
  // Aguarda 1 segundo antes de enviar novamente
  delay(1000);
}