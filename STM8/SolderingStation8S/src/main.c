#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SPI.h>

#define TEMP_MAX 450 //Maximum iron temperature
#define TEMP_MIN 100 //Minimum iron temperature
#define POT_DZ 16    //Deadzone at potentiometer edges

#define KP 50
#define KI 5
#define KD 300

#define LCD_RS PD4
#define LCD_RW PD3
#define LCD_EN PD2
#define LCD_D4 PC4
#define LCD_D5 PC3
#define LCD_D6 PB4
#define LCD_D7 PB5
#define MAX_SS PA3 //MAX6675 slave select
#define POT_IN PD5 //Analog input from potentiometer
#define FET_OU PA1 //MOSFET output
#define BUZZER PA2 //Buzzer
#define THERMOCOUPLE_J

LiquidCrystal(lcd, LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

uint8_t SPIRecvBuf[2];
int16_t error = 0;
int16_t ierror = 0;
int16_t derror;
int16_t lastError;

float readTemp(void)
{
  uint16_t buf;
  digitalWrite(MAX_SS, LOW);
  SPI_transfer_n(SPIRecvBuf, 2);
  digitalWrite(MAX_SS, HIGH);
  buf = SPIRecvBuf[1] + (SPIRecvBuf[0] << 8);
  if ((buf >> 2) & 1)
  {
    return -1;
  }
  else
  {
    return (float)(buf >> 3) / 4;
  }
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(POT_IN, INPUT);
  pinMode(FET_OU, OUTPUT);
  lcd_begin(16, 2);
  lcd_clear();
  lcd_print_s("Temp:");
  lcd_setCursor(0, 1);
  lcd_print_s("Set:");
  SPI_begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  float temperature = readTemp();
  #ifdef THERMOCOUPLE_J
  temperature = temperature*340/450;
  #endif
  uint16_t settemp = map(analogRead(POT_IN), POT_DZ, 1023 - POT_DZ, TEMP_MIN, TEMP_MAX);
  settemp = constrain(settemp, TEMP_MIN, TEMP_MAX);
  //lcd_clear();
  lcd_setCursor(7, 1);
  lcd_print_f(settemp);
  lcd_setCursor(7, 0);
  if (temperature < 0 || temperature > 500) //Temperature out of range
  {
    lcd_print_s("ERROR ");
    digitalWrite(FET_OU, LOW);
    delay(250);
  }
  else
  {
    if (temperature < 100.0)
    {
      lcd_print_s("0");
    }
    lcd_print_f(temperature);
    lastError = error;
    error = settemp - temperature;
    ierror += error;
    ierror = constrain(ierror, -250, 250);
    derror = error - lastError;
    int32_t pid = (KP*error + KI*ierror + KD*derror)/10;
    pid = constrain(pid, 0, 250);
    digitalWrite(FET_OU, HIGH);
    delay(pid);
    digitalWrite(FET_OU, LOW);
    delay(250 - pid);
    //End control
  }
}