# Change Log for Oink Brew Firmware

##v0.2

### Story
OB-45 	Temperature sensor read should automatically adjust the reading with the offset  
OB-44 	Receive a device offset value and store it in ActiveDevice and EEPROM  
  
### Improvement
OB-55 	Resetting Spark should remove all devices from EEPROM and empty ActiveDevices  
  
### BUG
OB-56 	Disconnecting a device does not clear ActiveDevices and EEPROM in the correct way and causes array overflow  
OB-58 	One misreading can cause a Device Disconnect, this should be prevented  
OB-34 	Newly connected devices should be detected automatically and added to the active devices  
OB-53 	When a device was disconnected the Oink Brew Web App should be notified  
OB-33 	Sensor disconnect should be detected and device removed from active devices  
OB-35 	When a newly detected device is added to active devices a message to Oink Brew Web App should be sent  
OB-60 	Loading SparkInfo after reset, does not set device mode correctly to M  
  
## v0.1
- startup check if WiFi connection and changes to listen mode if not
- udp broadcast status message to make itself known to the Oink Brew web application
- Application start shows startup screen with progress information
- Application start will show a calibration screen if no calibration settings found in EEPROM
- Implemented Information Screen with device information shown to user
- Implemented Brew Screen that can show all temp sensors and also which temp sensor is the acting one
- Load Device Information from EEPROM during startup
- Receive Device Information via TCP, stored in EEPROM and refresh screen with active information
- Receive Reset via TCP, reset all Device Info to default values and update EEPROM
- Receive new device mode [MANUAL,LOGGING,AUTOMATIC] to let device act with different behaviour
- Send by request all connected devices (OneWire Sensors and Actuators) in Json format
- Send current date time as part of the status broadcast messages
- Receive and set the oink web server date time as part of the Spark Info message
- Toggle a specific actuator on a specific Spark
- Send one sensor/actuator information by request
- Request device list will look for existing device information and update them and stores all found devices in EEPROM
- Request a single device information catches information from EEPROM and updates before returning to web app
- Toggle Actuator checks the type of hardware and for Digital turns off/on for PWM sets the provided value

- During startup load devices from EEPROM and initialise actuators and sensors
- Read sensor values every second
- Remove a device from Active Devices and EEPROM, onl a rescan will add his device again

- Receive $ message to restart Spark in bootloader
- Receive ! message to restart Spark

- Send connected devices (actuator/sensor) data every 15 seconds to oink brew web app