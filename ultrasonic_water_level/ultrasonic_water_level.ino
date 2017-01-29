#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define TRIGGER_PIN  11  // trigger pin (digital)
#define ECHO_PIN     12  // echo pin (digital)
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define TANK_HEIGHT  200 // высота бака в сантиметрах
#define TANK_RADIUS  80  // радиус бака в сантиметрах

//подключение дисплея A4 - SDA
//                    A5 - SCL

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
LiquidCrystal_I2C lcd(0x27,20,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(115200);             // Open serial monitor at 115200 baud to see ping results.
  lcd.init();                       // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
}

int getDistance(){
  int result = sonar.ping_cm();
  return result;
}

void loop()
{
  int distance = getDistance();
  int waterLevel = TANK_HEIGHT - distance;
  int waterVolume = PI; // расчет объема в см3 и перевод в литры
  delay(1000);             // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println(" cm");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Level: ");
  lcd.print(waterLevel);
  lcd.print(" cm");
  lcd.setCursor(0,1);
  lcd.print("Volume: ");
  lcd.print(waterVolume);
  lcd.print(" l");
}
