# Change Log for Oink Brew Firmware

v0.1
----
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


