#include <SPI.h> // Include SPI if you're using SPI
#include <HT_SSD1306.h> // Include the HT_SSD1306 library
#include <DHT.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>



#define DHT11Pin 4
#define DHTType DHT11
//OLED


//////////////////////////
// SSD1306 Definition //
//////////////////////////
#define PIN_RESET 9 // Connect RST to pin 9
#define PIN_DC 8 // Connect DC to pin 8
#define PIN_CS 7// Connect CS to pin 10
#define PIN_SCK 13 // Connect SCL/D0 to pin 13 v
#define PIN_MOSI 11// Connect SDA/D1 to pin 11
#define DHTPIN 4 //DHT11 sensor connection to PIN D4

//////////////////////////////////
// SSD1306 Object Declaration //
//////////////////////////////////
SSD1306 oled(PIN_RESET, PIN_DC, PIN_CS); // SPI 

 
char temperature[] = "00.0 C";
char humidity[]    = "00.0 %";
 
void setup(void) {
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
 
  dht.begin();                // Initialize the DHT library
 
  delay(1000);
 
  // Clear the display buffer.
  display.clearDisplay();
 
  display.drawFastHLine(0, 32, SSD1306_LCDWIDTH, WHITE);
 
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(10, 5);
  display.print("DHT11 TEMPERATURE:");
  display.setCursor(19, 37);
  display.print("DHT11 HUMIDITY:");
  display.display();
}
 
void loop() {
  // Read humidity
  byte RH = dht.readHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
 
  temperature[0] = Temp / 10 + 48;
  temperature[1] = Temp % 10 + 48;
  humidity[0]    = RH / 10 + 48;
  humidity[1]    = RH % 10 + 48;
 
  display.setCursor(46, 20);
  display.print(temperature);
  display.setCursor(46, 52);
  display.print(humidity);
  display.drawRect(71, 20, 3, 3, WHITE);     // Put degree symbol ( ° )
  display.display();
 
  delay(1000);
 
}
