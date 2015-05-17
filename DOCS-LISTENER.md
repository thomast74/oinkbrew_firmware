Actions that the Tcp Listener supports
======================================


Updates
-------

Impl | Action | Description
-----|--------|------------
Y | a | Request to send for a specific actuator/sensor the details
Y | d | Request device infor or all connected actuators/sensors and store them in EEPROM
Y | e | Remove actuators/sensors
? | f | Receive new firmware and upgrade Spark 
Y | m | Set device mode to either [MANUAL,CALIBRATION,LOGGING,AUTOMATIC]
Y | o | Set offset for a temperatur sensor
Y | q | Remove a controller
Y | r | Resets device info to default values and store them in EEPROM
Y | s | Receive updated SparkInfo
Y | t | Toggle digital pin actuator or receive a PWM value for PWM actuator
Y | $ | Boot spark in Bootloader mode
Y | ! | Restart spark