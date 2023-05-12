#include "http_request.h"
Http_Request http_request;
Http_Request::Http_Request(){
    
}
void Http_Request::init(){
    
}
String Http_Request::get(const String& api){
    if(connection.get_internet_status() != ConnectInternet::INTERNET_CONNECTED) {
        DBln("get fail because internet is disconnected");
        return "";
    }
    http.begin(this->client, api);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.GET();
    DB("HTTP POST Response code: ");
    DBln(httpResponseCode);
    String pay_load = http.getString();
    DB("HTTP POST payload: ");
    DBln(pay_load);
    return pay_load;
}

void Http_Request::post(const String& api, const String& data){
    if(connection.get_internet_status() != ConnectInternet::INTERNET_CONNECTED) {
        DBln("post fail because wifi disconnected");
        return;
    }
    http.begin(this->client, api);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(data);
    DB("HTTP POST Response code: ");
    DBln(httpResponseCode);
    String pay_load = http.getString();
    DB("HTTP POST payload: ");
    DBln(pay_load);
    http.end();
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