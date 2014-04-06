/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 

#include <Servo.h>
Servo servo;
Servo servo2;

int servoPin = 6;
int servoPin2 = 5;

boolean servo2Moved = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
  
  servo.attach(servoPin); // attaches the servo on pin 6 to the servo object
  servo2.attach(servoPin2); // attaches the servo on pin 5 to the servo object
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A="); lcd.print(mlx.readAmbientTempC()); 
  lcd.print("\tO="); lcd.print(mlx.readObjectTempC()); lcd.println("C");
  lcd.setCursor(0, 1);
  lcd.print("A="); lcd.print(mlx.readAmbientTempF()); 
  lcd.print("\tO="); lcd.print(mlx.readObjectTempF()); lcd.println("F");

  
  if (mlx.readObjectTempF() > 71 && mlx.readObjectTempF() < 100) {
    servo.writeMicroseconds(1300); // Clockwise
    //servo2.writeMicroseconds(1500); // Stop
    servo.write(90);
  } else if (mlx.readObjectTempF() > 100) {
    servo.writeMicroseconds(1300); // Clockwise
    servo.write(80);
    if (servo2Moved == 0) {
      //servo2.writeMicroseconds(1300); // Clockwise
      servo2.write(100);
      servo2Moved = 1;
    } else {
      servo2.writeMicroseconds(1500); // Stop
    }
      
  } else {
    if (servo2Moved == 1) {
      servo2.writeMicroseconds(1700); // Stop
      servo2.write(80);
      servo2Moved = 0;
    } else {
      servo2.writeMicroseconds(1500); // Stop
    }
    servo.writeMicroseconds(1500); // Stop
  }
  
  delay(500);
}
