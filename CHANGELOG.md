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