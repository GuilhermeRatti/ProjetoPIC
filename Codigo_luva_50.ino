/*
   MPU-6050 Test

   This simple program reads and prints to the Serial Monitor window
   the raw X/Y/Z values for the accelerometer and the gyro
   It also calculates the pitch and roll values as well as the temperature
   in F and C.
    
   Connect VDD to 5V and GND to ground on the MCU
   Connect SCL to SCL on MCU and SDA to SDA on MCU

  Note that the correction values can be used to put in an offset to adjust the
  values toward 0 or in the case of the temperature to adjust it to match a
  reference temperature measurement device.
*/
/*  Edgard de Souza T.
 *  Guilherme Ratti
 *  Matheus Luciano
 */
#include<Wire.h>
#include <math.h>

const int MPU=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double pitch,roll;
int i=0;
int f = 0;
//===============================================================================
//  Wifi
//===============================================================================
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define LED_BUILTIN 2  //For node_MCU Lolin esp8266
// Update these with values suitable for your network.

const char* ssid = "id";
const char* password = "pass";
//Free mqtt server for testing
const char* mqtt_server = "test.mosquitto.org";
//Local MQTT server - Tested using mosquitto mqtt for windows and linux
//const char* mqtt_server = "192.168.137.1";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    //digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    digitalWrite(LED_BUILTIN, LOW);   // Change for nodeMCU Lolin
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    //digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    digitalWrite(LED_BUILTIN, HIGH);   // Change for nodeMCU Lolin
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("iot20212", "hello world");
      // ... and resubscribe
      client.subscribe("iot20212/led");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//===============================================================================
//  Initialization
//===============================================================================
void setup(){

Wire.begin();
Wire.beginTransmission(MPU);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}
//===============================================================================
//  Main
//===============================================================================
void loop(){
Wire.beginTransmission(MPU);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU,14,true);

int AcXoff,AcYoff,AcZoff,GyXoff,GyYoff,GyZoff;
int temp,toff;
double t,tx,tf;

////Acceleration data correction
AcXoff = 0;//-900;
AcYoff = 0;//50;
AcZoff = -17100;

////Temperature correction
toff = -1600;

//Gyro correction
GyXoff = 580;
GyYoff = 100;
GyZoff = -100;

//read accel data and apply correction
AcX=(Wire.read()<<8|Wire.read()) + AcXoff;
AcY=(Wire.read()<<8|Wire.read()) + AcYoff;
AcZ=(Wire.read()<<8|Wire.read()) + AcZoff;

//read temperature data & apply correction
temp=(Wire.read()<<8|Wire.read()) + toff;

//read gyro data & apply correction
GyX=(Wire.read()<<8|Wire.read()) + GyXoff;
GyY=(Wire.read()<<8|Wire.read()) + GyYoff;
GyZ=(Wire.read()<<8|Wire.read()) + GyZoff;

// Calculate and convert temperature
tx=temp;
t = tx/340 + 36.53;     // Formula from data sheet
tf = (t * 9/5) + 32;    // Standard C to F conversion

//get pitch/roll
getAngle(AcX,AcY,AcZ);

 Serial.print(AcX/100);
Serial.print(","); Serial.print(AcY/100);
Serial.print(","); Serial.print(AcZ/100);
Serial.print(";");
// // Verifica qual direcao que foi inclinado o sensor


Serial.print(GyX/100);
Serial.print(","); Serial.print(GyY/100);
Serial.print(","); Serial.println(GyZ/100);
Serial.println(" ");

if (!client.connected()) {
    reconnect();
  }
  client.loop();

snprintf (msg, 100, "%d,%d,%d;%d,%d,%d.", AcX/100, AcY/100, AcZ/100, GyX/1000, -GyY/1000, GyZ/1000);
client.publish("PIC2022/luva", msg);



delay(66);
}

void getAngle(int Vx,int Vy,int Vz) {
double x = Vx;
double y = Vy;
double z = Vz;
pitch = atan(x/sqrt((y*y) + (z*z)));
roll = atan(y/sqrt((x*x) + (z*z)));
//convert radians into degrees
pitch = pitch * (180.0/3.14);
roll = roll * (180.0/3.14) ;
}
