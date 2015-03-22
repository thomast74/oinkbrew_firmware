# oinkbrew_firmware for Brewpi Spark hardware


Pre-Requisites for compilation
------------------------------
1. sudo apt-get remove binutils-arm-none-eabi gcc-arm-none-eabi
2. sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded
3. sudo apt-get update
4. sudo apt-get install gcc-arm-none-eabi=4.9.3.2015q1-0trusty13
   or
   sudo apt-get install gcc-arm-none-eabi=4.9.3.2015q1-0utopic14


5. sudo apt-get remove dfu-util
6. wget http://dfu-util.gnumonks.org/releases/dfu-util-0.7.tar.gz
7. tar -zxvf dfu-util-0.7.tar.gz dfu-util-0.7
8. cd dfu-util-0.7/
9. ./autogen.sh
10. ./configure
11. make
12 sudo make install

You might need to install autoconf and libusb-1.0-0-dev packages



Build
-----


Deploy
------


First Steps
-----------

