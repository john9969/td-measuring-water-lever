#ifndef HTTP_REQUEST
#define HTTP_REQUEST
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h"
#include "board/connect_internet.h"

/*DEFINE HERE*/

//************************************************************************************

class Http_Request {
private:
    WiFiClient client;
    HTTPClient http;
    String api_key;
public:
    Http_Request();
    void init();
    String get(const String& api);
    void post(const String& api, const String& data);
    int response(const String& api, const String& data);
public:
    void set_api_key(const String& api_key);
    String get_api_key() const;
};
extern Http_Request http_request;
#endif