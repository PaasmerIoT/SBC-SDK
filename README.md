# SBC-SDK
**Paasmer IoT SDK** for Single Board Computers Running Linux

## Overview

The **Paasmer SDK** for **Single Board Computers (SBC)** like Raspberry-PI, Intel Edison, Beagle Bone is a collection of source files that enables you to connect to the Paasmer IoT Platform. It includes the trasnport client for **MQTT** with **TLS** support.  It is distributed in source form and intended to be built into customer firmware along with application code, other libraries and RTOS.

## Featuers

The **SBC-SDK** simplifies access to the Pub/Sub functionality of the **Paasmer IoT** broker via **MQTT**. The SDK has been tested to work with the **Paasmer IoT Platform** and **Raspberrp Pi 3**. Support for Other SBC's running any flavors of Linux would be available shortly.

## MQTT Connection

The **SBC-SDK** provides functionality to create and maintain a mutually authenticated TLS connection over which it runs **MQTT**. This connection is used for any further publish operations and allow for subscribing to **MQTT** topics which will call a configurable callback function when these topics are received.

## Pre Requisites

Registration on the portal http://developer.paasmer.co is necessary to connect the device to the **Paasmer IoT Platfrom** .The SDK has been tested on the Raspberry PI 3 with Raspbian Jessie (https://downloads.raspberrypi.org/raspbian_latest)

# Installation

* Download the SDK or clone it using the command below.
```
$ git clone github.com/PaasmerIoT/SBC-SDK.git
$ cd SBC-SDK
$ cd external_libs/mbedTLS/
$ make
$ cd ../../
$ sudo ./install.sh
```

* Upon successful completion of the above command, a few commands which need to be executed are displayed.
```
$ sudo su
$ source ~/.bashrc
$ PAASMER
$ sed -i 's/alias PAASMER/#alias PAASMER/g' ~/.bashrc
$ exit
```

* Goto the diectory below.
```
$ cd samples/linux/subscribe_publish_sample/
```

* Edit the config.h file to include the user name(Email), device name and feed names and GPIO pins
```c
#define UserName "Email Address" //your user name used in developer.paasmer.co for registration
#define DeviceName "" //your device name
#define feedname1 "feed1" //feed name used for display in the developer.paasmer.co
#define sensorpin1 gpio-pin-no-for-sensor-1 //modify with the pin number which you connected the sensor, eg 6 or 7 or 22
#define feedname2 "feed2" //feed name used for display in the developer.paasmer.co
#define sensorpin2 gpio-pin-no-for-sensor-2 //modify with the pin number which you connected the sensor, eg 6 or 7 or 22
#define feedname3 "feed3" //feed name used for display in the developer.paasmer.co
#define sensorpin3 gpio-pin-no-for-sensor-3 //modify with the pin number which you connected the sensor, eg 6 or 7 or 22
#define feedname4 "feed4" //feed name used for display in the developer.paasmer.co
#define sensorpin4 gpio-pin-no-for-sensor-4 //modify with the pin number which you connected the sensor, eg 6 or 7 or 22
#define controlfeedname1 "controlfeed1" //feed name used for display in the developer.paasmer.co
#define controlpin1 3 //modify with the pin number which you connected the control device (eg.: motor)
#define controlfeedname2 "controlfeed2" //feed name used for display in the developer.paasmer.co
#define controlpin2 4 //modify with the pin number which you connected the control device (eg.: fan)
#define timePeriod 15000 //change the time delay as you required for sending sensor values to paasmer cloud
```
      
* Compile the code and generate output file.
```
$ sudo make
```

* Run the code using the command below.
```
$ sudo ./subscribe_publish_sample
```

* The device would now be connected to the Paasmer IoT Platfrom and publishing sensor values are regular intervals.

# Support

The support forum is hosted on the GitHub where issues can be identified and the Team from Paasmer would be taking up requstes and resolving them. You could also send a mail to support@paasmer.co with the issue details for resolution.

## Note

The Paasmer IoT SBC-SDK utilizes the features provided by AWS-IOT-SDK for C.
