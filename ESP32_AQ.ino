#include "Plantower_PMS7003.h"
#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <WiFi.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <WiFiManager.h>
#include <Adafruit_BME680.h>



#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
#define SD_CS 5

Adafruit_BME680 bme; // I2C

float temperature, humidity, pressure, gas, altitudeBme, val1, val2, val3; 
float latitude = 23.038126; 
float longitude = 72.552605;
char output[256];
Plantower_PMS7003 pms7003 = Plantower_PMS7003();

const char* WIFI_SSID = "Rishi_Laptop";
const char* WIFI_PASSWORD = "123456789R";

#define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "O1_V2GneSPSShWlBRoZEoY1nUmY8e-BeoAfIMr8XLlUFszDE6gxV1MIGmToiA3c9kN78Xq4QeRoFJ1BWl9H6sQ=="
#define INFLUXDB_ORG "55e78fd6907352a4"
#define INFLUXDB_BUCKET "AIR_Q018"
#define INFLUXDB_MEASUREMENT "atmosphere_data"

// Set timezone. You can refer here: http://bit.ly/3YKh66x
#define TZ_INFO "IST-5:30"

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
// Data point
Point sensor(INFLUXDB_MEASUREMENT);


TinyGPSPlus gps;
HardwareSerial GPS(1);

String dataMessage, lati, longi, atlt, noS;

void saveConfigCallback() {
  Serial.println("Saving WiFi configuration");
  // Add code here to save custom parameters, if needed
}

void connectToWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to the provided WiFi credentials.");

    // If failed to connect, start transmitting its own WiFi
    WiFiManager wifiManager;
    wifiManager.setConfigPortalTimeout(300); // Set Config Portal timeout to 5 minutes (300 seconds)
    wifiManager.setSaveParamsCallback(saveConfigCallback);

    Serial.println("Starting Config Portal for setting new WiFi credentials.");

    if (!wifiManager.startConfigPortal("AutoConnectAP", "AutoConnectPassword")) {
      Serial.println("Failed to connect or configure new WiFi credentials. Rebooting...");
      delay(3000);
      ESP.restart();
    }

    Serial.println("Connected to new WiFi. Updated credentials:");
    Serial.println("SSID: " + WiFi.SSID());
    Serial.println("Password: " + WiFi.psk());
  }

  Serial.println("Connected to WiFi");
}


void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  GPS.begin(9600, SERIAL_8N1, 26, 27);

  pms7003.init(&Serial2);
  //pms7003.debug = true;

  connectToWifi();

    if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

#ifndef ESP8266
  while (!Serial);
#endif

  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);



}
 
void loop()
{
  pms7003.updateFrame();

    if (GPS.available()) {
      if (gps.encode(GPS.read())) {
        String msg = GPS.readStringUntil('\r');
        Serial.println(msg);
        Serial.print("LAT=");
        Serial.println(gps.location.lat(), 6);
        Serial.print("LONG=");
        Serial.println(gps.location.lng(), 6);
        Serial.print("ALT=");
        Serial.println(gps.altitude.meters(), 6);
        Serial.print("Number satellites use= ");
        Serial.println(gps.satellites.value());

        latitude = gps.location.lat();
        lati = String(latitude, 6);
        longitude = gps.location.lng();
        longi = String(longitude, 6);
        atlt = gps.altitude.meters();
        noS = gps.satellites.value();
        delay(5000);
      }
  }


  if (pms7003.hasNewData()) {

    sprintf(output, "\nSensor Version: %d    Error Code: %d\n",
                  pms7003.getHWVersion(),
                  pms7003.getErrorCode());
    Serial.print(output);

    sprintf(output, "    PM1.0 (ug/m3): %2d     [atmos: %d]\n",
                  pms7003.getPM_1_0(),
                  pms7003.getPM_1_0_atmos());              
    Serial.print(output);
    sprintf(output, "    PM2.5 (ug/m3): %2d     [atmos: %d]\n",
                  pms7003.getPM_2_5(),
                  pms7003.getPM_2_5_atmos());
    Serial.print(output);
    sprintf(output, "    PM10  (ug/m3): %2d     [atmos: %d]\n",
                  pms7003.getPM_10_0(),
                  pms7003.getPM_10_0_atmos());              
    Serial.print(output);

    sprintf(output, "\n    RAW: %2d[>0.3] %2d[>0.5] %2d[>1.0] %2d[>2.5] %2d[>5.0] %2d[>10]\n",
                  pms7003.getRawGreaterThan_0_3(),
                  pms7003.getRawGreaterThan_0_5(),
                  pms7003.getRawGreaterThan_1_0(),
                  pms7003.getRawGreaterThan_2_5(),
                  pms7003.getRawGreaterThan_5_0(),
                  pms7003.getRawGreaterThan_10_0());
    Serial.print(output);

    val1 = pms7003.getPM_1_0();
    val2 = pms7003.getPM_2_5();
    val3 = pms7003.getPM_10_0();

    delay(5000);

      bme.performReading(); // Perform BME680 sensor reading

  temperature = bme.temperature;
  humidity = bme.humidity;
  pressure = bme.pressure / 100.0;
  gas = bme.gas_resistance / 1000.0;
  altitudeBme = bme.readAltitude(SEALEVELPRESSURE_HPA);
  lati = String(latitude, 6);
  longi = String(longitude, 6);
  

  gas = round(gas * 100) / 100;
  
    // Clear fields for reusing the point. Tags will remain untouched
    sensor.clearFields();

    // Store measured values into point
    sensor.addField("temperature", temperature);
    sensor.addField("humidity", humidity);
    sensor.addField("pressure", pressure);
    sensor.addField("gas", gas);
    sensor.addField("altitude", altitudeBme);

    // Store calculated values into point
    sensor.addField("pm1", val1);
    sensor.addField("pm2.5", val2);
    sensor.addField("pm10", val3);

    sensor.addField("lat", lati);
    sensor.addField("lng", longi);
    sensor.addField("altitude_gps_1", atlt);
    sensor.addField("Satellite_1", noS); 

    // Print what we are writing
    Serial.print("Writing: ");
    Serial.println(sensor.toLineProtocol());

    // Check WiFi connection and reconnect if needed
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi connection lost. Reconnecting...");
      connectToWifi();
    }

    // Write point to InfluxDB
    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB Cloud write failed: ");
      Serial.println(client.getLastErrorMessage());
    }



    Serial.println("Wait 30s");
    delay(20000); // Delay for 20 seconds
  }


}