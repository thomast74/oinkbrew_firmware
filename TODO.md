* **Receive device delete request**  
  if device is part of a config return error  

* **receive configuration data**  
  update device with function received via configuration data  
  re-define hardware type for actuator if configuration data has different setting  
  if sensor or actuator is not curretnly configured on this device return error  
  only one brew configuration is possible  
  fermenation configuration can be 1 or more  

* **send every 10 seconds a log message to oinkweb app if device mode is LOGGING or AUTOMATIC**  

* **based on cofigration data received configure PID controllers and compute them every cycle**  
  PID controller needs to support phases of different temperatues  
  PID controller configuration needs to be stored in EEPROM  
  PID contoller needs to be configured during startup  
  PID actuator action will be done only if mode is AUTOMATIC  

* **update Brew Screen with sensor data based on device function**  

* **update Ferm Screen with sesor data based on device function and chamber**  
