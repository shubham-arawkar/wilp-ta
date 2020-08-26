#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication
#include <LiquidCrystal.h>    //Library for using LCD display

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;  
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  //Define LCD display pins RS,E,D4,D5,D6,D7 
                                           
struct can_frame canMsg; 
MCP2515 mcp2515(10);                        // SPI CS Pin 10 
 
void setup() {
  lcd.begin(16,2);                          //Sets LCD as 16x2 type
  lcd.setCursor(0,0);                       //Display Welcome Message
  lcd.print("BITS-PILANI");
  lcd.setCursor(0,1);
  lcd.print("CAN ARDUINO");
  delay(3000);
  lcd.clear();
  
  SPI.begin();                              //Begins SPI communication
  Serial.begin(9600);                       //Begins Serial Communication at 9600 baudrate 
  mcp2515.reset();     
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz                   
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) { // To receive data (Poll Read)
    int x = canMsg.data[0];
    int y = canMsg.data[1];
      
    lcd.setCursor(0,0);//Display Temp & Humidity value received at 16x2 LCD
    lcd.print("Humidity : ");
    lcd.print(x);
    lcd.setCursor(0,1);
    lcd.print("Temp : ");
    lcd.print(y);
    delay(1000);
    lcd.clear();
  }
} 
