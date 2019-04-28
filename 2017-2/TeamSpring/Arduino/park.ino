#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "HX711.h"
#define RST 4
#define DOUT  3
#define CLK  2

#include <SPI.h>
#include <Ethernet.h>

#define COMM_LED_ON()     digitalWrite(13, HIGH)




#define COMM_LED_OFF()    digitalWrite(13, LOW)

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192,168,0,2);  // numeric IP for Google (no DNS)
IPAddress ip(192, 168, 0, 188);
EthernetClient client;

MPU6050 accelgyro;
HX711 scale(DOUT, CLK);

float calibration_factor = -2680.00; //-7050 worked for my 440lb max scale setup

float oldCal_factor;
float oldWeight;

 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
int accel_reading;
int accel_corrected;
int accel_offset = 200;
float accel_angle;
float accel_scale = 1;
float accel_angle2 =2;
 
int gyro_offset = 151;
double dgy_x,deg;
double angle;
double angle2;
float last_read_time;
float last_x_angle,last_y_angle,last_z_angle;

//int speakerpin = 12;
 
void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  //Get a baseline reading
  long zero_factor = scale.read_average();

  //This can be used to remove the need to tare the scale.
  // Useful in permanent scale projects.
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);

  // Reset pin (to rezero the weight not reset the board!)
  pinMode(RST, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  

  accelgyro.initialize();
}
 
void loop() {
  // 가속도 및 자이로 x,y,z 축에 대한 데이터 받아오기
  // 가속도 값은 -16800 ~ 16800 범위를 -90 ~ 90으로 바꿔줌
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  accel_reading = ay;
  accel_corrected = accel_reading - accel_offset;
  accel_corrected = map(accel_corrected, -16800, 16800, -90, 90);
  accel_corrected = constrain(accel_corrected, -90, 90);
  accel_angle = (float)(accel_corrected * accel_scale);
  accel_angle2 = accel_angle ;

 

    
  // 가속도만을 이용한 각도 출력
  Serial.print("Acc angle : ");
  Serial.print(accel_angle);
  Serial.print("\t");
  delay(1000);
  deg = atan2(ax, az) * 180 / PI;     // rad to deg
  
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  accel_reading = ay;
  accel_corrected = accel_reading - accel_offset;
  accel_corrected = map(accel_corrected, -16800, 16800, -90, 90);
  accel_corrected = constrain(accel_corrected, -90, 90);
  accel_angle = (float)(accel_corrected * accel_scale);
  
  // 자이로+가속도 조합한 각도
  dgy_x = gy / gyro_offset;
  angle = (0.95 * (angle + (dgy_x * 0.001))) + (0.05 * deg);

  // 자이로 가속도 둘 다 이용한 각도 출력
  //Serial.print("Filter angle : ");
  //Serial.println(angle) ;
  scale.set_scale(calibration_factor);

  // Read an average of X readings
  float weight = scale.get_units(10);

  // An intermediate weigth value that we round according to some rules
  int netWeight = 0 ;

  // Make scale more sensitive at lower end
  // Weight > X then just round to nearest integer
  if (weight >= 5.0) {
    netWeight = (weight * 10.0);
    weight = (int)(0.5 + (netWeight / 10.0));
  }
  // Weight < Y then call it zero
  else if (weight > -0.01 && weight <= 0.01) {
    weight = 0;
  }
  // Any other weight will have 1 dec. place of precision
  else {
    netWeight = (weight * 10.0);
    weight = (netWeight / 10.0);
  }

  // Only print something out if it has changed (weight or cal. factor)
  if (calibration_factor != oldCal_factor || weight != oldWeight) {
    oldCal_factor = calibration_factor;
    oldWeight = weight;

    Serial.print("Reading: ");
    Serial.print(weight, 2);
    Serial.print(" g");
    Serial.print(" calibration_factor: ");
    Serial.print(calibration_factor);
    Serial.println();
    delay(300);   

    if(weight >= 70.00){
       if(abs(accel_angle2-accel_angle)>0.5){
            Serial.print(" Trance degree  ");
             // if you get a connection, report back via serial:
            if (client.connect(server, 9000)) 
            {
              COMM_LED_ON();
              Serial.println("connected");
              // Make a HTTP request:
              client.println("GET /seaitc/index2.jsp?a=158 HTTP/1.1");
              client.println("Host:  192.168.0.2");
              client.println("Connection: close"); // 서버 에게 응답을 '다 보낸 후에' 연결을 종료하면 된다고 말해줌
              client.println();
 
              while (client.connected()) { //서버와 연결 되어 있는 동안 . 서버는 response가 끝나면 연결을 종료 시킴. client.connected 가 false
                while (client.available()) {
                  char c = client.read(); // 버퍼 제거
                  Serial.print(c);
                }
              }

              client.stop();
              COMM_LED_OFF();
            } 
            else 
            {
               // if you didn't get a connection to the server:
               Serial.println("connection failed");
               //while(client.available())
               //{
                   //digitalWrite(13,HIGH); //이거됨
               //}
            }//else
        }//abs
    }//weight
    else
    {
      //digitalWrite(13,LOW);
    }
  }// 큰틀 if

  // User entered +, -, a or z in the Serial Monitor window? Adjust cal. factor
  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 2;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 2;
  }

  // Has user requested a Zero Reset?
  //int rstRequest = digitalRead(RST);
  //if (rstRequest == LOW) {
    //Serial.println("Resetting ZERO value");
    //scale.set_scale();
    //scale.tare();  //Reset the scale to 0
  //}
}
