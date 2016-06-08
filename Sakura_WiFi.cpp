/*  
  Sakura_WiFi.h - Library for Sakura board (EducationRobots.RU) or other Arduino boards and ESP8266.
*/
 
#include <Arduino.h>
#include <Sakura_WiFi.h>

int SakuraWiFi::SakuraWiFi(int led_ind_pin)
{
	ind_pin=led_ind_pin;
}

int wifi_reset(void)
{
  pinMode(ind_pin,OUTPUT);
  pinMode(WRST,OUTPUT);
  pinMode(WPRG,OUTPUT);
  digitalWrite(WPRG,HIGH);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,64);
  else if(ind_pin>0) digitalWrite(ind_pin,HIGH);
  digitalWrite(WRST,LOW);///WIFI HARD RESET
  delay(50);
  digitalWrite(WRST,HIGH);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,128);
  delay(1000);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,192);
  //This initializes the Wifi Module as a server 
  SendCommand("AT+RST", "Ready", true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,255);
  delay(3000);
  for (int x=1; x <= 2 ; x ++)
  {
    digitalWrite(ind_pin,LOW);
    delay(50);
    digitalWrite(ind_pin,HIGH);
    delay(50); 
 }
 digitalWrite(ind_pin,LOW);
}

int net_connect(String w_ssid, String w_password)
{
  pinMode(ind_pin,OUTPUT);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,32);
  SendCommand("AT+CWMODE=1", "OK", true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,64);
  delay(10000);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,96);
  SendCommand("AT+CWJAP=\"" + w_ssid + "\",\"" + w_password + "\"", "WIFI CONNECTED", true);//SSID, PWD
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,128);
  delay(16000);//default: 15000 ms
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,160);
  SendCommand("AT+CIFSR", "OK", true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,192);
  delay(1000);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,255);
  for (int x=1; x <= 3 ; x ++)
  {
    digitalWrite(ind_pin,LOW);
    delay(50);
    digitalWrite(ind_pin,HIGH);
    delay(50); 
 }
 digitalWrite(ind_pin,LOW);
}

int start_server(int w_port)
{
  pinMode(ind_pin,OUTPUT);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,176);
  SendCommand("AT+CIPMUX=1","OK",true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,192);
  delay(1000);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,208);
  SendCommand("AT+CIPSERVER=1,"+String(w_port),"OK",true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,255);
  for (int x=1; x <= 5 ; x ++)
  {
    digitalWrite(ind_pin,LOW);
    delay(50);
    digitalWrite(ind_pin,HIGH);
    delay(50); 
 }
 digitalWrite(ind_pin,LOW);
}

int get_req(String tcp_domain, String tcp_path, int tcp_port)
{
  String tcp_str="GET http://" + tcp_domain + tcp_path + " HTTP/1.0\r\n\r\n";
  String tcp_strlen=String(tcp_str.length());
  pinMode(ind_pin,OUTPUT);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,176);
  SendCommand("AT+CIPSTART=\"TCP\",\""+tcp_domain+"\","+String(tcp_port),"OK",true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,192);
  //delay(2000);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,208);
  SendCommand("AT+CIPSEND="+tcp_strlen,">",true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,255);
  delay(50);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,208);
  Serial.println(tcp_str);
  //Serial1.println(tcp_str);
  SendCommand(tcp_str,"OK",true);
  delay(20000);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,208);
  SendCommand("AT+CIPCLOSE","OK",true);
  if(digital_pin_to_timer_PGM[ind_pin]!=NOT_ON_TIMER) analogWrite(ind_pin,255);
  for (int x=1; x <= 7 ; x ++)
  {
    digitalWrite(ind_pin,LOW);
    delay(50);
    digitalWrite(ind_pin,HIGH);
    delay(50); 
 }
 digitalWrite(ind_pin,LOW);
}
