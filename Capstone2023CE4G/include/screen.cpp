#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

namespace screen{
    void init_screen()
    {
        // turn on backlite
        pinMode(TFT_BACKLITE, OUTPUT);
        digitalWrite(TFT_BACKLITE, HIGH);

        // turn on the TFT / I2C power supply
        pinMode(TFT_I2C_POWER, OUTPUT);
        digitalWrite(TFT_I2C_POWER, HIGH);
        delay(500);

        // initialize TFT

        tft.init(135, 240); // Init ST7789 240x135
        tft.setRotation(3);
    }

    void detected(){
        tft.fillScreen(ST77XX_MAGENTA);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(4);
        tft.setTextWrap(true);

        tft.setCursor(18, 45);
        tft.println("DETECTED");
    }

    void seizure_alert()
    {
        tft.fillScreen(ST77XX_RED);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(3);
        tft.setTextWrap(true);

        tft.setCursor(5, 15);
        tft.println("SEIZURE ALERT");
        tft.setTextSize(2);
        tft.setCursor(13, 50);
        tft.setTextColor(ST77XX_CYAN);
        tft.println("press top & bottom");
        tft.setCursor(75, 65);
        tft.println("to reset");

        tft.fillTriangle(40, 120, 65, 85, 90, 120, ST77XX_YELLOW);
        tft.fillTriangle(150, 120, 175, 85, 200, 120, ST77XX_YELLOW);

        tft.setCursor(56, 92);
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(4);
        tft.println("!");

        tft.setCursor(166, 92);
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(4);
        tft.println("!");
    }

    void cleared()
    {
        tft.fillScreen(ST77XX_MAGENTA);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(5);
        tft.setTextWrap(true);

        tft.setCursor(18, 45);
        tft.println("CLEARED");
    }

    void clear(){
        tft.fillScreen(ST77XX_BLACK);
        tft.setCursor(0,0);
    }

    void home(){
        tft.fillScreen(ST77XX_BLACK);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(5);
        tft.setTextWrap(true);

        tft.setCursor(18, 45);
        tft.println("Tremor Tec");   
    }

}