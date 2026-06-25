# 🌊 IoT-Based Maritime Communication and Monitoring System using LoRa

An IoT-enabled maritime communication and monitoring system that leverages **ESP32**, **LoRa**, and **GPS** technologies to provide reliable long-range communication and real-time monitoring in marine environments where conventional internet connectivity is unavailable or unreliable.

---

## Overview

Maritime environments present significant challenges for communication and monitoring due to their vast coverage, harsh conditions, and limited network infrastructure. This project addresses these challenges by implementing a **low-power, long-range IoT communication system** using LoRa technology.

The system enables real-time collection and transmission of GPS location data from remote maritime nodes to a land-based monitoring station. By combining **ESP32 microcontrollers**, **GPS modules**, **LoRa communication**, and **Wi-Fi connectivity**, the project demonstrates a scalable and energy-efficient solution for monitoring assets in remote marine environments.

The receiver node further forwards the received data to a backend server, enabling storage, visualization, and future integration with cloud-based monitoring platforms.

---

## Objectives

* Develop a reliable long-range communication system for maritime environments.
* Enable real-time monitoring of remote maritime assets.
* Reduce dependence on internet connectivity in offshore regions.
* Demonstrate a low-power and scalable IoT communication architecture.
* Improve maritime safety through continuous location monitoring.

---

## Key Features

* 🌊 Long-range LoRa communication
* 📍 Real-time GPS location tracking
* 📡 Low-power wireless communication
* 🌐 Wi-Fi integration for backend connectivity
* 📊 Local monitoring dashboard on the transmitter
* 📈 Signal quality monitoring using RSSI and SNR
* 🔄 Automatic transmission of location data to a server via HTTP
* ⚙️ Modular and scalable system architecture

---

## System Architecture

![image alt](https://github.com/JinuSaju/marine_lora_comms/blob/main/images/transmitter_node.jpeg?raw=true)
![image alt](https://github.com/JinuSaju/marine_lora_comms/blob/main/images/receiver_node.jpg?raw=true)
```text
          GPS Module
               │
               ▼
      ESP32 Transmitter
               │
         LoRa (866 MHz)
               │
               ▼
       ESP32 Receiver
               │
        Wi-Fi (HTTP POST)
               │
               ▼
      Backend Server/API
               │
               ▼
 Database / Dashboard / Analytics
```

---

## Hardware Components

<img width="657" height="599" alt="image" src="https://github.com/user-attachments/assets/0b091410-da34-4067-bf7d-671017c08271" />

### Transmitter Node

* ESP32 Development Board
* SX1278 LoRa Module (866 MHz)
* GPS Module (NEO-6M or compatible)
* LoRa Antenna

### Receiver Node

* ESP32 Development Board
* SX1278 LoRa Module (866 MHz)
* LoRa Antenna
* Wi-Fi Network Access

---

## Software Stack

### Embedded

* Arduino IDE
* ESP32 Board Package

### Libraries

* TinyGPS++
* LoRa
* WiFi
* WebServer
* HTTPClient
* SPI

### Backend

* Node.js
* Express.js
* REST API

---

## Working Principle

### Transmitter

* Reads live GPS coordinates from the GPS module.
* Displays GPS status through a local web interface.
* Packages latitude and longitude into a LoRa packet.
* Transmits the packet over long-range LoRa communication.

### Receiver

* Continuously listens for incoming LoRa packets.
* Extracts GPS coordinates.
* Measures signal quality (RSSI and SNR).
* Sends the received data to a backend server through an HTTP POST request over Wi-Fi.

---

## Data Flow

```text
GPS Data
     │
     ▼
ESP32 Transmitter
     │
     ▼
LoRa Transmission
     │
     ▼
ESP32 Receiver
     │
     ▼
HTTP POST Request
     │
     ▼
Backend API
     │
     ▼
Database / Monitoring Dashboard
```

---

## Applications

This project can be adapted for various maritime and remote monitoring applications, including:

* Fishing vessel tracking
* Maritime communication systems
* Coastal surveillance
* Disaster and emergency response
* Search and rescue operations
* Environmental and oceanographic monitoring
* Marine research
* Offshore asset monitoring
* Harbor and port management

---

## Challenges Addressed

The project is designed while considering common challenges in maritime environments:

* Limited internet connectivity
* Long-distance communication requirements
* Low power consumption
* Wide-area coverage
* Reliable wireless communication
* Scalable IoT deployment

Potential limitations include:

* Signal attenuation due to environmental conditions
* Communication range affected by obstacles and antenna placement
* Energy constraints for long-term autonomous deployments

---

## Future Enhancements

* Bidirectional LoRa communication with acknowledgments
* SOS and emergency alert functionality
* Multi-node maritime network
* Sensor integration (temperature, humidity, wave height, water quality)
* OLED display for node status
* Solar-powered deployment
* MQTT and cloud integration
* Interactive GIS-based monitoring dashboard
* Data encryption and secure communication
* LoRaWAN compatibility

---

## Project Structure

```text
.
├── LoRa_Transmitter_GPS/
│   └── wireless_code.ino
├── Lora_Reciver_DB/
│   └── post_rec_final.ino
├── docs/
│   └── mini_project_report_final.pdf
├── images/
│   └── components.png
│   └── receiver_node.jpg
│   └── transmitter_node.jpeg
└── README.md
```

---

## Future Scope

The proposed architecture serves as a foundation for building intelligent maritime IoT networks capable of supporting autonomous vessels, smart ports, marine conservation initiatives, and emergency communication systems. With additional sensors and cloud integration, the system can evolve into a comprehensive maritime monitoring platform for both research and industrial applications.

---

## Authors

**Jinu J Saju , Elza Sabu , S Sabarinath , Anavadhya Rajesh**

B.Tech Computer Science and Engineering
Mar Baselios College of Engineering and Technology

---

## License

This project is released under the **MIT License**.

---

## Acknowledgements

This project was developed as part of a seminar on **IoT-Based Maritime Communication and Monitoring**, exploring the use of long-range IoT technologies to enhance communication, safety, and situational awareness in maritime environments while supporting sustainable marine operations.

⭐ If you found this project interesting or useful, consider giving it a star on GitHub!
