#ifndef HTTP_REQUEST
#define HTTP_REQUEST
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h"
#include "board/connect_internet.h"

/*DEFINE HERE*/

//************************************************************************************

class Http_Request {

public:
    enum HTTP_OP_STATE{
    HTTP_OP_STATE_INIT,
    HTTP_OP_STATE_WAIT,
    HTTP_OP_STATE_DONE,
    HTTP_OP_ABORT
  };
    Http_Request();
    void init();
    int get(const String& api);
    int post(const String& api, const String& data);
    int response(const String& api, const String& data);
    void set_api_key(const String& api_key);
    String get_api_key() const;
    HTTP_OP_STATE get_http_op_state() const{
        return this->http_op_state;
    }
    void set_http_op_state(const HTTP_OP_STATE& http_op_state){

        this->http_op_state = http_op_state;
    } 
    String get_data_response ();
private:
    String api_key;
    String data_response;
    HTTP_OP_STATE http_op_state;
};
extern Http_Request http_request;
#endif