#include "Arduino.h"
#ifndef HTTP_REQUEST
#define HTTP_REQUEST

/*DEFINE HERE*/

//************************************************************************************

class Http_Request {
private:
            
public:
    Http_Request();
    void init();
    void get(const String& api, const String& data);
    void post(const String& api, const String& data);
    int response(const String& api, const String& data);
};

#endif