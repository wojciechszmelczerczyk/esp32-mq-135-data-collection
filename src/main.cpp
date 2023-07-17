#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>

// Wi-Fi credentials
const char* ssid = "";
const char* password = "";

// IP address and port of the receiver (Controller 1)
const char* receiverIP = "";
const int receiverPort = 80;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  delay(2000);

  Serial.println("Connected with WiFi!");
  Serial.print("IP adress: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  long MQ135_data = analogRead(GPIO_NUM_32);

  // Send POST request to the receiver (Controller 1)
  WiFiClient client;
  Serial.println("sdadsdsa");
  if (client.connect(receiverIP, receiverPort)) {
    String data = "mq_data=" + String(MQ135_data);
    String request = String("POST / HTTP/1.1\r\n");
    request.concat("Host: ");
    request.concat(receiverIP);
    request.concat("\r\n");
    request.concat("Content-Type: application/x-www-form-urlencoded\r\n");
    request.concat("Content-Length: ");
    request.concat(String(data.length()));
    request.concat("\r\n");
    request.concat("Connection: close\r\n\r\n");
    request.concat(data);
    request.concat("\r\n");
    
    client.print(request);
    delay(100);
  }
  

  delay(60000); // Wait for 1 minute before the next reading
}
