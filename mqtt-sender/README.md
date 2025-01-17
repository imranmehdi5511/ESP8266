# ESP8266 Sender with I2T Sensors Stack  -- MQTT Protocol

***ESP8266*** is one of the microcontrollers for IoT applications par excellence. Created and manufactured by Espressif, it was the first microcontroller of this company to become popular, it is widely used for both educational and industrial development due to its great versatility, reliability and very low cost. 

This Repository contains the source code and the steps to follow to be able to make ***ESP8266 Microcontroller*** *read sensor data and send it*, in an organized way, to the **[Tangle](https://www.youtube.com/watch?v=ESF8UZM70wU) (DLT)** of the **[IOTA Network](https://www.iota.org/)** through the **[Streams](https://www.iota.org/solutions/streams)** layer.


# Setting up your ESP8266 with the I2T Sensors Stack

This is the list of Sensors/Modules that you can connect and it will be recognized immediately.
- ***BME280*** (*Bosch*) - Temperature, Humidity and Pressure sensor. -> Connected by *I2C Bus* via: *GPIO4/SDA* and *GPIO5/SCL* --- Be careful with the supply of this sensor, the BM280 is powered with 3.3V, if your module does not have a voltage regulator (some modules do not have it) the sensor can be damaged if you supply 5V.
- ***MPU6050*** (*InvenSense-TDK*) - Acelerometer and Gyroscope 6-axis. -> Connected by *I2C Bus* via: *GPIO4/SDA* and *GPIO5/SCL*.
- ***BH1750*** (*ROHM*) - Ambient Light Sensor. -> Connected by *I2C Bus* via: *GPIO4/SDA* and *GPIO5/SCL*.
- ***Generic Adjustable Sound Sensor with digital output*** (like *KY038 Module*) - -> Digital Signal on *GPIO0*, *GPIO2* to GND (to enable sound data collection).
- Also, you can connect a ***Green LED*** in *GPIO16* that blink when the data is sent to the Tangle, and a ***Red LED*** in *GPIO15* that will Blink in a certain way when it detects certain errors (totally optional)

## Connecting the sensors

The following diagram explains how each sensor of our stack must be connected to the ESP8266 pins. The "NodeMCU v2 (or also v3)" development board has been used in this diagram, which contains the ESP32 microcontroller. However, any development board that contains the ESP32 microcontroller can be used.

![I2T Hardware Connections of ESP8266](https://i.postimg.cc/LXJpdFZw/ESP8266-sender.png)

**It is not necessary to have all the sensors listed here**, the code is able to detect which sensors were connected. In the case of not connecting any sensor, the only real data that will be displayed on the Tangle will be the Internal Voltage of *ESP8266*.

# Download Firmware on ESP8266
This repository uses the ***Iot2Tangle C Core devices*** adapted for ***ESP8266-FreeRTOS*** offered in the official *Espressif Toolchain ESP-IDF SDK*. Once the SDK is installed you will have all the tools to compile and download the program on your ESP8266.


## 1) Install ESP-IDF SDK:
### Windows:
The easiest way to install ESP-IDF and their prerequisites is to download the ESP-IDF Windows Environment and Toolchain installer from this URL:
<https://dl.espressif.com/dl/esp32_win32_msys2_environment_and_toolchain-20181001.zip>

Unzip the zip file to *C:\\* (or some other location, but this guide assumes *C:\\*) and it will create an *msys32 directory* with a pre-prepared environment.

Open a **MSYS2 MINGW32** terminal window by running ***C:\msys32\mingw32.exe***. The environment in this window is a bash shell. Create a directory named esp that is a default location to develop ESP8266 applications and then the ***ESP8266_RTOS_SDK*** will be cloned. To do so, run the following shell commands:
```
mkdir esp
cd esp
sudo git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git
```
Before continuing you must add some Python libraries that were not added in the ESP-IDF Windows Toolchain, probably because they were added later. So, run the following shell commands:
```
pip install click
pip install pyelftools
```
Now install the SDK, this may take a while:
```
cd ESP8266_RTOS_SDK
./install.sh
. ./export.sh
```
After doing this last step do not close the shell, as we will compile and flash from here. If you close the shell you will have to do the previous step again.

### Linux and macOS:
Prerequisites of ESP-IDF SDK:
```
sudo apt update
sudo apt install git wget flex bison gperf python2-minimal python2 dh-python 2to3 python-is-python3 python-pip python-setuptools cmake ninja-build ccache libffi-dev libssl-dev libncurses5-dev libncursesw5-dev

```
It is recommended to install the lastest version, you can download it from here:
```
sudo git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git
```
Now install the SDK, this may take a while:
```
cd ~/ESP8266_RTOS_SDK
./install.sh
. ./export.sh
```
After doing this last step do not close the shell, as we will compile and flash from here. If you close the shell you will have to do the previous step again.

## 2) Download the Iot2Tangle ESP8266 Repository and go to the 'mqtt-sender' folder:
You can download the repository directly from Github, or from shell or Command Prompt with the following commands:
```
cd ~
git clone https://github.com/iot2tangle/ESP8266.git
cd ESP8266/mqtt-sender
```
## 3) Edit the file config.h
The *config.h* file must be opened and modified, this file is in the directory *'ESP8266/mqtt-sender/main'* of the repository.

This step is very important if you want to make a connection to the gateway. Your *WiFi Credentials*, the *address* and *port* that will have the *I2T Streams MQTT Gateway* (It is also possible to configure *username* and *password* in case the *Broker* has it), the *Device Id*, and others configurations. The *Id Name Device* you define here must be between the devices you set in on the *Gateway configuration file*. 
```
/* Device */
const char* id_name = "ESP8266-MQTT";

/* Network Configuration */
const char* ssid_WiFi = "mySSID";
const char* pass_WiFi = "myPASS";

/* Broker Configuration */
const char* address = "mqtt.iot2tangle.link";  /* Broker address (MQTT), must NOT include 'http://xxx' or 'tcp://xxx' */
int port = 8883;
const char* topic = "iot2tangle";		/* MQTT topic */
const char* user = "mqtti2t";			/* MQTT user */
const char* password = "integrateeverything";	/* MQTT password */

/* Enable Sensors */
bool isEnable_TemperatureIntern = true;
bool isEnable_TemperatureExtern = true;	   /* true: Enable  --  false: Disable */
bool isEnable_Humidity = true;
...

/* Interval of time */
long interval = 30;    /* Time in seconds between */
```
In case of not using *Username* and *Password* in the *Broker*, leave these fields empty:
```
const char* user = "";      /* MQTT user */
const char* password = "";  /* MQTT password */
```
## 4) Compile and Download the Firmware:
Remembering to have the ***ESP-IDF Toolchain*** open, and you make sure you are at the root of the *http-sender* folder run the following command:
```
idf.py build
```
If the compilation was correct it should read: *Project build complete*.

Now make sure you have ESP8266 connected to your computer, and know what COM port it is connected to. (You can see this in 'Device Manager'). 

Then run the following command that will start flashing the firmware. (You will probably have to press the reset button on your ESP8266 development board, even several times for it to recognize the board.)
```
idf.py -p COM1 flash    # COM1 is an Windows port example, you must put your port. In Linux /dev/ttyUSB0 is an example, and in macOS: '/dev/cu' 
```

Upon completion, the firmware is downloaded to your ESP32. If the *I2T Streams HTTP Gateway* is configured correctly (we will explain this next), ***you will be sending data to Tangle via Streams***.

# Debugging
If configured correctly, *ESP8266* should be sending data to the gateway automatically. However, you may want to verify that it is running on *ESP8266*.

The code continuously sends information out the **serial port**, so it can read the serial port to see what is happening and detect errors.

You can use the 'Arduino Serial Monitor' for this, but we recommend using the following software:
## Windows:
Open *Command Prompt*.

Configure the Baud Rate of the port to 115200 bps:
```
mode COM1: baud=115200
```
Read the serial port:
```
copy COM1: con:
```
## Linux and macOS:
Install *cu Monitor*. It is an excellent shell monitor and very useful.
```
sudo apt install cu
```
Run *cu Monitor*:
```
cu -l /dev/ttyUSB0 -s 115200
```


The following screenshot is a reading of the *Serial Port*, you should see something like this:

![Raspberry with BME280 sending data to the Tangle](https://i.postimg.cc/cH6TWpXP/Screenshot-from-2020-10-16-11-33-05.png)


# Setting up the Streams HTTP Gateway

## Preparation

Install Rust if you don't have it already. More info about Rust here https://www.rust-lang.org/tools/install

```
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

Make sure you also have the build dependencies installed, if not run:  

```
sudo apt update
sudo apt install build-essential pkg-config libssl-dev  
```

## Installing the Streams Gateway
Get the Streams Gateway repository
https://github.com/iot2tangle/Streams-http-gateway

```
git clone https://github.com/iot2tangle/Streams-http-gateway
```

Navigate to the root of **Streams-http-gateway** directory and edit the **config.json** file to define yours *device names*, *endpoint*, *port*, you can also change the IOTA Full Node used, among others.

## Start the Streams Server

### Sending messages to the Tangle

Run the Streams Gateway:  

```
cargo run --release  
```
This will compile and start the *Streams HTTP Gateway*. Note that the compilation process may take from 3 to 25 minutes (Pi3 took us around 15/25 mins, Pi4 8 mins and VPS or desktop machines will generally compile under the 5 mins) depending on the device you are using as host.
You will only go through the compilation process once and any restart done later will take a few seconds to have the Gateway working.

Once started, the ***Channel Id*** will be displayed, and the gateway will be open waiting for data to send to the Tangle.

![Streams Gateway receiving data](https://i.postimg.cc/zfz0tbWz/Screenshot-from-2020-10-16-11-44-59.png)
*The Channel Id that will allow subscribers to access the channel data.*

### Reading messages from the Tangle

You can read the received messages directly from the **I2T Explorer**: https://explorer.iot2tangle.io/ using the Channel Id printed by the Gateway in shell.   

![I2T Explorer](https://i.postimg.cc/wTNf7dgp/Screenshot-from-2020-10-16-11-46-16.png)


*For inquiries, improvements or errors detected, please start an issue in this repository.*
