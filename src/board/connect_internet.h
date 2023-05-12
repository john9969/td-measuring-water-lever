
#ifndef CONNECT_INTERNET_H
#define CONNECT_INTERNET_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "config.h"
#include "dcom_olax.h"
class ConnectInternet {
public:
  typedef enum {
  INTERNET_DISCONNECTED,
  INTERNET_CONNECTING,
  INTERNET_CONNECTED,
  INTERNET_TIMEOUT,
} internet_status_t;

  private:
    String ssid;
    String password;
    int timeout_connect_wifi;
    String local_ip;
    internet_status_t internet_status;
    void connect_to_internet();
  public:
    ConnectInternet();
    void set_ssid(const String& ssid);
    void set_pass(const String& pass);
    String get_local_ip() const;
    void set_local_ip(const String& local_ip);
    void wifi_init();
    void set_timeout_connect_wifi(const int& timeout_connect_wifi);
    int get_timeout_connect_wifi() const;
    internet_status_t get_internet_status();
    void set_internet_status(const internet_status_t& internet_status);
};
extern void checking_connection();
extern ConnectInternet connection;
#endif