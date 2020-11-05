/*

void loop(void)
{
  int i;
  double j=0.01;

}
*/


#include <OneWire.h>  
#include <DallasTemperature.h>   
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8( U8X8_PIN_NONE);   
//DS18B20 온도 센서의 데이터선인 가운데 핀을 아두이노 3번
#define ONE_WIRE_BUS 3  
//1-wire 디바이스와 통신하기 위한 준비  
OneWire oneWire(ONE_WIRE_BUS);  
// oneWire선언한 것을 sensors 선언시 참조함.  
DallasTemperature sensors(&oneWire);  
//다비아스 주소를 저장할 배열 선언  
DeviceAddress insideThermometer;  
    
    
void setup(void)  
{  
  // OLED 초기화
  u8x8.begin();
  //시리얼 포트 초기화  
  Serial.begin(9600);  

  Serial.println("Dallas Temperature IC Control Library Demo");  
  //1-wire 버스 초기화  
  sensors.begin();  
  //발견한 디바이스 갯수  
  Serial.print("Found ");  
  Serial.print(sensors.getDeviceCount(), DEC);  
  Serial.println(" devices.");  
  // parasite power 모드일 때에는  2핀(GND와 DQ 핀)만 연결하면 됨.  
  // Serial.print("Parasite power is: ");   
  if (sensors.isParasitePowerMode()) Serial.println("ON");  
  else Serial.println("OFF");  
  //버스에서 첫번째 장치의 주소를 가져온다.  
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");   
  //데이터시트에서 확인결과 9~12비트까지 설정 가능  
  sensors.setResolution(insideThermometer, 10);  
  Serial.print("Device 0 Resolution: ");  
  Serial.print(sensors.getResolution(insideThermometer), DEC);   
  Serial.println();

}  
    
// 온도를 출력하는 함수  
void printTemperature(DeviceAddress deviceAddress)  
{  
  //섭씨 온도를 가져옴  
  float  tempC = sensors.getTempC(deviceAddress);  
      
  Serial.print("Temp C: ");  
  Serial.print(tempC);  
  Serial.print(" Temp F: ");  
      
  //화씨 온도로 변환  
  Serial.println(DallasTemperature::toFahrenheit(tempC));   
}  

// OLED 첫줄 세팅 함수
void pre(void)
{
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);    
  u8x8.clear();

  u8x8.inverse();
  u8x8.print(" Temp ");
  u8x8.setFont(u8x8_font_chroma48medium8_r);  
  u8x8.noInverse();
  u8x8.setCursor(0,1);
}

void loop(void)  
{   
  //sensors.requestTemperatures();   //연결되어 있는 전체 센서의 온도 값을 읽어옴  
  sensors.requestTemperaturesByIndex(0); //첫번째 센서의 온도값 읽어옴  
     
  //센서에서 읽어온 온도를 출력  
  //printTemperature(insideThermometer);  
  
  //섭씨 온도를 가져옴  
  float  tempC = sensors.getTempC(insideThermometer);  

  pre();
  u8x8.setFont(u8x8_font_inb33_3x6_n);
  u8x8.setCursor(0, 2);
  u8x8.print(tempC);    
  delay(2000);
}  

