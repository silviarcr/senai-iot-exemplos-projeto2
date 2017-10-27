#include <utility/logging.h>
#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

const int portaLed = 8;
int statusLed = LOW;

//byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xF1, 0x35 };
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(topic);
  //colocar aqui codigo de comunicacao com MQTT
  int msg = atoi(payload);
 Serial.println(msg);
 Serial.println(topic);
 if (strcmp(topic, "Portao") == 0) {
   Serial.println("topic == Portao");
   if (msg == 1) {
     Serial.println("msg recebida = 1");
     //acende lampada
     acendeApagaLed(portaLed, HIGH);
   }
   else {
     //apaga lampada
     Serial.println("msg = 0 fecha portao");
     delay(2000);
     acendeApagaLed(portaLed, LOW);
   }

 }else{
   Serial.println("Nao entrou no IF");
   }
  
}

EthernetClient ethClient;
PubSubClient client("m10.cloudmqtt.com", 11356, callback, ethClient);

long lastReconnectAttempt = 0;

boolean reconnect() {
  Serial.println("reconectando...");
  if (client.connect("arduinoClient", "charles", "charles")) {
    Serial.println("conectado");
    // client.publish("vaga/1","hello world");
    client.subscribe("vaga/#");
  }
  return client.connected();
}

void setup()
{
  Serial.begin(9600);
  Serial.println("iniciando...");
  Ethernet.begin(mac);
  delay(1500);
  
  lastReconnectAttempt = 0;
}

void loop()
{
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      Serial.println("reconectando...");
      lastReconnectAttempt = now;
      
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    client.loop();
  }

}

void acendeApagaLed(int pino, int status) {
 digitalWrite(pino, status);
 statusLed = status;
}
