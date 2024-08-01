#include <LiquidCrystal_I2C.h>

const int pinR = 15;
const int pinG = 11;
const int pinB = 8;

#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
const float BETA = 3950; // should match the Beta Coefficient of the thermistor

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize the RGB LED pins as output
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop() {
  int analogValue = analogRead(A0);
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;

  // Set the RGB LED color based on the temperature
  if (celsius < 15) {
    // Cold: Blue
    analogWrite(pinR, 255);
    analogWrite(pinG, 255);
    analogWrite(pinB, 0);
  } else if (celsius >= 15 && celsius <= 25) {
    // Moderate: Green
    analogWrite(pinR, 255);
    analogWrite(pinG, 0);
    analogWrite(pinB, 255);
  } else {
    // Hot: Red
    analogWrite(pinR, 0);
    analogWrite(pinG, 255);
    analogWrite(pinB, 255);
  }

  // Display the temperature on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(celsius);
  lcd.print(" C");
  lcd.print((char) 223);

  // Display different messages based on temperature
  lcd.setCursor(0, 1);
  if (celsius < 15) {
    lcd.print("It's so chilly!!!");
  } else if (celsius >= 15 && celsius <= 25) {
    lcd.print("This is nice!");
  } else {
    lcd.print("Damn, it's hot!");
  }

  delay(500);
}
