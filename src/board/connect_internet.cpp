#include "connect_internet.h"
ConnectInternet connection;
ConnectInternet::ConnectInternet() {
  this->internet_status       = INTERNET_DISCONNECTED;
  this->timeout_connect_wifi  = TIME_OUT_CONNECT_WIFI;
  this->ssid                  = SSID;
  this->password              = PASS;
}

void ConnectInternet::wifi_init(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid, this->password);
    set_internet_status(INTERNET_CONNECTING);
    Serial.print("connect wifi: SSID:");
    Serial.print(this->ssid);
    Serial.print("PASS:");
    Serial.print(this->password);
}
/*****************************EXTERN FUNCTION************************************************************/
//loop to check connect per
bool is_disable = false;
void checking_connection() {
  if(is_disable) return;
  if(WiFi.status() == WL_CONNECTED){
    if(connection.get_internet_status() == ConnectInternet::INTERNET_CONNECTED ) return;
      connection.set_internet_status(ConnectInternet::INTERNET_CONNECTED);
      connection.set_local_ip(WiFi.localIP().toString());
      Serial.println("wifi connected successful");
      connection.set_timeout_connect_wifi(0); 
      return;
  }
  LED_TOGGLE
  int p_timeout_connect_wifi = connection.get_timeout_connect_wifi();
  if(p_timeout_connect_wifi == 0){
    p_timeout_connect_wifi = -1;
    connection.set_timeout_connect_wifi(p_timeout_connect_wifi);
    Serial.println("wifi connect fail, timeout");
    Serial.println("reset dcom off");
    DCOM_OFF
    return;
  }
  if(p_timeout_connect_wifi <= -1){
    p_timeout_connect_wifi = TIME_OUT_CONNECT_WIFI;
    connection.set_timeout_connect_wifi(p_timeout_connect_wifi);
    DCOM_ON
    Serial.println("dcom on");
    return;
  }
  if(p_timeout_connect_wifi > 0){
    p_timeout_connect_wifi--;
    connection.set_timeout_connect_wifi(p_timeout_connect_wifi);
    Serial.print("connecting to wifi: timeout ");
    Serial.println(p_timeout_connect_wifi);
  }
}
/************************************SET&GET FUNCTION*****************************************************/
ConnectInternet::internet_status_t ConnectInternet::get_internet_status() {
  return this->internet_status;
}
String ConnectInternet::get_local_ip() const{
  return this->local_ip;
}
void ConnectInternet::set_local_ip(const String& local_ip){
  this->local_ip = local_ip;
}
void ConnectInternet::set_pass(const String& pass){
  this->password = pass;
}
void ConnectInternet::set_ssid(const String& ssid){
  this->ssid = ssid;
}
void ConnectInternet::set_internet_status(const internet_status_t& internet_status){
  this->internet_status = internet_status;
}
void ConnectInternet::set_timeout_connect_wifi(const int& timeout_connect_wifi){
  this->timeout_connect_wifi = timeout_connect_wifi;
}
int ConnectInternet::get_timeout_connect_wifi() const{
  return this->timeout_connect_wifi;
}
//*****************************************************************************************************