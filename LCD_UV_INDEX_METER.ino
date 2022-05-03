#include <LiquidCrystal_I2C.h>

#include <Adafruit_AHTX0.h>

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
//#include <Adafruit_SPIDevice.h>

#include <Wire.h>

#include <string.h>



Adafruit_AHTX0 aht;
LiquidCrystal_I2C lcd(0x27,16,2);
 
float UV_Index(int UV_Input);
float bat_percent(float charge);


float UV_Level;
float Temp;
int Hum;
float bat_charge;
float U_WY1;

void setup(){
    
    Serial.begin(115200);
    if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

//lcd.init();
lcd.begin(16,2);
lcd.backlight();


pinMode(LED_BUILTIN, OUTPUT);
pinMode(A7,INPUT);
pinMode(A1,INPUT);
}

void loop(){
    
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    Temp = temp.temperature;
    Hum = humidity.relative_humidity;
    U_WY1 = analogRead(A7)*0.004888;
    UV_Level = UV_Index(U_WY1);
    
    
    bat_charge = analogRead(A1);
    Serial.print(Temp);
    Serial.println("C");
    Serial.print(Hum);
    Serial.println("%\n");
    

//lcd.clear();
  lcd.setCursor(0,0);
lcd.print("UV=");
lcd.print(UV_Level,1);  

lcd.setCursor(11,0);
lcd.print("B=");  
lcd.print(bat_percent(bat_charge));  
lcd.print("%"); 

lcd.setCursor(0,1);
lcd.print("T=");  
lcd.print(Temp);
lcd.print("C");

lcd.setCursor(11,1);
lcd.print("H=");  
lcd.print(Hum);  
lcd.print("%"); 

  delay(300);
 

}
//zmienic i wyrzucic to *6 i potem przylutowa wyjscie wzmacniacza transkonduktacyjnego do SIG, lub oddzielnie
//lepiej beda pokazywac indeks


float UV_Index(float UV_Input){

  if(UV_Input>=0.8){
    return (UV_Input-0.8)*15/3.2;
  }else{
    return 0;
  }

}


float bat_percent(float charge){
  return ((charge-550)/290)*100;
}
