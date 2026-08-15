# Smart Temperature & Humidity Monitor

An adaptive embedded system that monitors temperature and humidity, and intelligently decides when to activate cooling — simulated using Wokwi.

## Overview
Unlike a simple fixed-threshold system, this project uses:
- **Heat index** ("feels like" temperature) instead of raw temperature, factoring in humidity
- An **adaptive rolling average** of recent readings, so the "trigger point" adjusts to recent conditions rather than using one fixed number

This mirrors how real smart thermostats make decisions, rather than relying on a static if-statement.

## Components
- Arduino Uno
- DHT22 temperature & humidity sensor
- I2C 16x2 LCD display
- LED (representing a cooling fan/relay)

## How it works
1. Reads temperature and humidity every 2 seconds
2. Computes the heat index ("feels like" temperature)
3. Maintains a rolling average of the last 5 heat index readings
4. Turns on the fan (LED) if the current heat index exceeds the rolling average by more than 2°C
5. Displays live readings on the LCD

## Try it live
[Wokwi Simulation Link](https://wokwi.com/projects/472446171920627713)

## Tech Stack
Arduino C++, DHT22 sensor, I2C LCD, Wokwi simulation## Try it live
[Wokwi Simulation Link](https://wokwi.com/projects/472446171920627713)
