/*  
  Sakura_WiFi.h - Library for Sakura board (EducationRobots.RU) or other Arduino boards and ESP8266.
*/
#ifndef Sakura_WiFi_h
#define Sakura_WiFi_h

#include <Arduino.h>

class SakuraWiFi
{
  public:
    int SakuraWiFi(int led_ind_pin);
    int reset(void);
    int net_connect(String w_ssid, String w_password);
	int start_server(int w_port);
	int get_req(String tcp_domain, String tcp_path, int tcp_port);
  private:
    int ind_pin;
};
 
#endif