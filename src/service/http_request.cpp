#include "http_request.h"
Http_Request http_request;
Http_Request::Http_Request(){
    
}
void Http_Request::init(){
    
}
int Http_Request::get(const String& api){
    if(connection.get_internet_status() != ConnectInternet::INTERNET_CONNECTED) {
        DBln("get fail because internet is disconnected");
        return -1;
    }
    WiFiClient client;
    HTTPClient http;
    http.begin(client, api.c_str());
    int httpResponseCode = http.GET();
    DB("HTTP get Response code: ");
    DBln(httpResponseCode);
    String pay_load = http.getString();
    DB("HTTP get payload: ");
    DBln(pay_load);
    pay_load.trim();
    this->data_response = pay_load;
    http.end();
    return httpResponseCode;
}

int Http_Request::post(const String& api, const String& data){
    if(connection.get_internet_status() != ConnectInternet::INTERNET_CONNECTED) {
        DBln("post fail because wifi disconnected");
        return -1;
    }
    WiFiClient client;
    HTTPClient http;
    http.begin(client, api);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(data);
    DB("HTTP POST Response code: ");
    DBln(httpResponseCode);

    String pay_load = http.getString();
    DB("HTTP POST payload: ");
    DBln(pay_load);
    http.end();
    return httpResponseCode;
}

int Http_Request::response(const String& api, const String& data){
    return 1;
}
void Http_Request::set_api_key(const String& api_key){
    this->api_key = api_key;
}
String Http_Request::get_api_key() const{
    return this->api_key;
}
String Http_Request::get_data_response(){
    return this->data_response;
}