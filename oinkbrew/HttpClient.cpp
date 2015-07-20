#include "HttpClient.h"
#include "Helper.h"
#include "spark_wiring.h"
#include "spark_wiring_string.h"


/**
* Constructor.
*/
HttpClient::HttpClient()
{
}

/**
* Method to send a header, should only be called from within the class.
*/
void HttpClient::sendHeader(const char* aHeaderName, const char* aHeaderValue)
{
    client.print(aHeaderName);
    client.print(": ");
    client.println(aHeaderValue);
}

void HttpClient::sendHeader(const char* aHeaderName, const int aHeaderValue)
{
    client.print(aHeaderName);
    client.print(": ");
    client.println(aHeaderValue);
}

void HttpClient::sendHeader(const char* aHeaderName)
{
    client.println(aHeaderName);
}

/**
* Method to send an HTTP Request. Allocate variables in your application code
* in the aResponse struct and set the headers and the options in the aRequest
* struct.
*/
void HttpClient::request(http_request_t &aRequest, http_response_t &aResponse, http_header_t headers[], const char* aHttpMethod)
{
    // If a proper response code isn't received it will be set to -1.
    aResponse.status = -1;

    // NOTE: The default port tertiary statement is unpredictable if the request structure is not initialised
    // http_request_t request = {0} or memset(&request, 0, sizeof(http_request_t)) should be used
    // to ensure all fields are zero
    bool connected = false;
    if(aRequest.hostname!=NULL) {
        connected = client.connect(aRequest.hostname.c_str(), (aRequest.port) ? aRequest.port : 80 );
    }   else {
        connected = client.connect(aRequest.ip, aRequest.port);
    }

    if (!connected) {
        client.stop();
        delay(10);
        // If TCP Client can't connect to host, exit here.
        return;
    }

    //
    // Send HTTP Headers
    //
    // Send initial headers (only HTTP 1.0 is supported for now).
    String header(aHttpMethod);
    header.concat(" ");
    header.concat(aRequest.path);
    header.concat(" HTTP/1.0\r\n");

    // Send General and Request Headers.
    header.concat("Connection: close\r\n");
    header.concat("Content-Length: ");
    header.concat(aRequest.body.length());
    header.concat("\r\n");
    header.concat("Content-Type: application/json\r\n");
    header.concat("Accept: */*\r\n");
    header.concat("\r\n");

    client.write(header.c_str());

    //
    // Send HTTP Request Body
    //

    if (aRequest.body != NULL) {
    	client.write(aRequest.body.c_str());
    }

    delay(100);

    unsigned long startTime = millis();
    while (client.available() == 0 && (millis() - startTime) < 1000) { }

    startTime = millis();
    while (client.available() != 0 && (millis() - startTime) < 1000) {
    	client.read();
    	delay(25);
    }

    client.stop();
    delay(25);
}
