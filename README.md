# ESP-32 and MQ-135

## Description

Project describe set up of `ESP-32` and `MQ-135` sensor. `MQ-135` sensor collect data about air quality. It measures variety of gases such as `CO2`, `NH3` and so on in the air and return value which describe `Air Quality Index`. `ESP-32` intercept this data and send via http client to [ESP-32 + BME280](https://github.com/wojciechszmelczerczyk/esp32-bme280-data-collection) structure every 15 minutes.

## Techstack

- `Arduino`
