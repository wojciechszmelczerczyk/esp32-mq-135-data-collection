#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
 
// Influxdb cloud config data
#define INFLUXDB_URL ""
#define INFLUXDB_TOKEN ""
#define INFLUXDB_ORG ""
#define INFLUXDB_BUCKET ""

// Time zone info
#define TZ_INFO "UTC2"

// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Declare Data point
Point sensor("environment");

// Wi-Fi credentials
const char* ssid = "";
const char* password = "";

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

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // // Check server connection
  if(client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void loop() {
  int MQ135_data = analogRead(GPIO_NUM_32);
  Serial.println(MQ135_data);
  sensor.addField("air_index", MQ135_data);

  Serial.println(sensor.toLineProtocol());

  // Write data point to InfluxDB
  if (client.writePoint(sensor)) {
    Serial.println("Data point sent to InfluxDB successfully");
  } else {
    Serial.print("Error sending data point to InfluxDB: ");
    Serial.println(client.getLastErrorMessage());
  }

  // Print the sensor readings
  Serial.print("Air index: ");
  Serial.print(MQ135_data);


  delay(60000); // Wait for 1 minute before the next reading
}
