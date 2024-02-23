# Real-Time-Air-Quality-Dashboard
Hands on Esp32 DEVKIT-V1, NEO-6M GPS Sensor, BME688 Sensor, PMS Sensor.
Coding using Arduino-IDE.
Received the developed code for BME and PMS, were tasked to incorporate NEO-6M, database and render it on a dashboard.
![EESP32 DEVKIT-V1](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/3a0daa16-3cda-4ab0-bf21-a011db64e10c)

# SENSORS AND MICROCONTROLLERS USED:
1) Esp32 DEVKIT-V1;
ESP32 is a series of low-cost, low-power system on a chip microcontrollers with integrated Wi-Fi.

   ![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/7f3b5931-bb9d-4041-a505-02c2f6a1f3f7)
3) BME688;
The BME688 has temperature, barometric pressure, air humidity, altitude and gas sensor elements inside. All sensor information can be used either as single values or combined in the AI software to recognize certain conditions or states.

   ![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/43c4a492-0a7a-4cc6-86c4-e6742b880dfb)
4) PMS(Particulate Matter Sensor);
A particulate matter (PM) sensor measures the concentration of floating particles in the air. PM sensors can be laser-based, and work by using a laser to illuminate a particle and then collecting the light that scatters. The sensor can then count the particles in the air, and provide real-time information  on air pollution.

   ![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/2298fce9-a2fd-40af-9acb-97d4fe3d142b)
5) NEO-6M
With its low power consumption, compact size, and high accuracy, the NEO-6M GPS module is a popular choice for GPS applications in various fields, such as navigation, location tracking, and autonomous vehicles. The module has four pins: VCC, GND, RX, and TX.

   ![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/f74ffc54-c975-4794-8a04-39172f6e65ae)

# UML DIAGRAM WHICH DEPICTS THE FLOW OF DATA:

![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/850b696a-be5b-447d-a9b8-204bf9856ddd)

# DATABASE USED: INFLUX DB
Influx DB is the platform purpose-built to collect, store, process and visualize time series data(TSDB).
The Influx DB data model organizes time series data into buckets and measurements. A bucket can contain multiple measurements.
Bucket: Named location where time series data is stored. A bucket can contain multiple measurements .
Measurement: Logical grouping for time series data. All points in a given measurement should have the same tags.
![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/92ef314e-d1f3-4df4-a82c-4dcb84c30e0e)

# VISUALIZATION TOOL: GRAFANA
Grafana open source software enables you to query, visualize, alert on, and explore your metrics, logs, and traces wherever they are stored.
Popular among IOT based projects.
Whole configuration is already explained. Please refer this document. 
https://docs.google.com/document/d/1KFV7ZiS242wdmRd_CY4sNDocOYhhpRAVSYkmDPeuvKo/edit 

# RESULTS:
![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/befd0388-d536-4b43-bbe2-cd0d633db55b)
![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/72b1cf0e-b17b-461e-b04a-0064368dc41d)
![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/1cff3981-8b5e-431f-a78b-861aefbcf60b)
![](https://github.com/DarshilShukla26/Real-Time-Air-Quality-Dashboard/assets/97797056/60e23394-4b25-4947-a5e2-30e8982edaf9)


