- receive RESET message to clear all configuration (except calibration)

- get connected devices
- send list of connected devices when requested via TCP
  (how do i detect Actuators? or are they just named)

- allow the configuration of device with alias

- if in AUTOMATIC or LOGGING mode send sensor data via TCP to OINKWEB
  sensor data should be sent as C (F will be converted for the front end/view)

- turn Actuator on/off based on TCP request received
