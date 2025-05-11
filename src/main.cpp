#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used
#define OLED_ADDRESS  0x3C

unsigned long lastUpdate1 = 0;
unsigned long lastUpdate2 = 0;
const unsigned long updateInterval = 500;  // 100 ms
const unsigned long switchInterval = 5000; // 1 second
uint8_t currentScreen = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displayTemps(int cpuT0, int cpuT1, int cpuT2, int cpuT3, int nvmeT, int ssdT, int tmp1T, int tmp2T);

void setup()
{
    delay(2000);
    Wire.begin(12, 14);
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
    {
        Serial.println("OLED init failed");
        while (true); // Halt
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("System Status: OK");
    display.setCursor(0, 16);
    display.println("Temperature: 25C");
    display.display();
}

void loop()
{
  if (millis() - lastUpdate1 >= updateInterval)
    {
        lastUpdate1 = millis();

        display.clearDisplay();
        if(currentScreen == 0)
        {
          displayTemps(40, 40, 40, 40, 40, 40, 40, 40);
        }
        
        display.display();
    }
    if (millis() - lastUpdate2 >= updateInterval)
    {
        lastUpdate2 = millis();
        currentScreen++;
        if (currentScreen > 1)
        {
            currentScreen = 0;
        }
    }
}

void displayTemps(int cpuT0, int cpuT1, int cpuT2, int cpuT3, int nvmeT, int ssdT, int tmp1T, int tmp2T)
{
  display.setCursor(0, 0);
  display.println("System Status: OK");

  display.setCursor(0, 16);
  display.print("CPU0: ");
  display.print(cpuT0);
  display.println("C");

  display.setCursor(0, 27);
  display.print("CPU1: ");
  display.print(cpuT1);
  display.println("C");

  display.setCursor(0, 38);
  display.print("CPU2: ");
  display.print(cpuT2);
  display.println("C");

  display.setCursor(0, 49);
  display.print("CPU3: ");
  display.print(cpuT3);
  display.println("C");
    /**************************************************/
  display.drawLine(60, 16, 60, 58, SSD1306_WHITE);
    /**************************************************/
  display.setCursor(68, 16);
  display.print("NVMe: ");
  display.print(nvmeT);
  display.println("C");

  display.setCursor(68, 27);
  display.print("SSD : ");
  display.print(ssdT);
  display.println("C");

  display.setCursor(68, 38);
  display.print("TMP1: ");
  display.print(tmp1T);
  display.println("C");

  display.setCursor(68, 49);
  display.print("TMP2: ");
  display.print(tmp2T);
  display.println("C");
}