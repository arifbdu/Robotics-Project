#include<SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SimpleTimer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

SoftwareSerial B(10,11);    //10-RX,  11-TX
SimpleTimer timer;

int pH_Value;
float Voltage;
float vol;
const int turbidityPin = A1;
int turbidityValue;
float turbidity;
String waterType;

#define ONE_WIRE_BUS 2

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OneWire oneWire(ONE_WIRE_BUS);


DallasTemperature sensors(&oneWire);

void setup()
{
  B.begin(9600);
  Wire.begin();
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  pinMode(pH_Value, INPUT);
 
//timer.setInterval(500L, display_pHValue);
}

void loop() {
  timer.run(); // Initiates SimpleTimer
  pH_Value = analogRead(A0);
  Voltage = pH_Value * (5.0 / 1023.0);
  vol=(Voltage +4.3);
  Serial.print("pH:");
  Serial.println(vol);
  delay(500);

  sensors.requestTemperatures();
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" C");

  turbidityValue = analogRead(turbidityPin); // Read the analog value from the turbidity sensor
  turbidity = map(turbidityValue, 0, 1023, 10, 20); // Convert the analog value to a value between 10 and 20
  Serial.println("Turbidity: " + String(turbidity) + " NTU"); // Print the turbidity value to the serial monitor
   
  delay(5000);
   delay(2000);

  // Read humidity
  //float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  //float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);
  float t = sensors.getTempCByIndex(0);
  float T = t+157 ;
  B.print(vol);
  B.print(",");

  B.print(turbidity);
  B.print(",");

  B.print(T);
  B.print(";");

  delay(20);
 }