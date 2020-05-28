/* 
 ******************************************************************** 
  ESP Data to Google Sheets project
  Upload data to Google Sheets from Espressif Systems ESP32 & ESP8266
  by Walid Amriou
  Github : https://github.com/walidamriou/ESP_Data_to_Google_Sheets
 ******************************************************************** 
*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_ssid_wifi_here";
const char* password =  "your_password_wifi_here";


 /*
 we use this certificate to support Https but you need to Change it, to get new 
 certificate, use the url of the request, make a request and get it from your 
 browser. if you don't know how to get it, just go to google (or your search engine :p) 
 and search about "get certificate https from brower" :D
*/
const char* Https_certificate= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIJTzCCCDegAwIBAgIQGoaLDa+bxzQIAAAAAD69lzANBgkqhkiG9w0BAQsFADBC\n" \
"MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZpY2VzMRMw\n" \
"EQYDVQQDEwpHVFMgQ0EgMU8xMB4XDTIwMDUwNTA4MjIzNVoXDTIwMDcyODA4MjIz\n" \
"NVowZjELMAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcT\n" \
"DU1vdW50YWluIFZpZXcxEzARBgNVBAoTCkdvb2dsZSBMTEMxFTATBgNVBAMMDCou\n" \
"Z29vZ2xlLmNvbTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABMExBCpkvy8VuVVJ\n" \
"gyrY19Q/NvVPzb+yNS371xwzVriYLDhyEyGXNf45D/qj7qIe9EqkpOylAUvF5+4x\n" \
"NYr5INujggbmMIIG4jAOBgNVHQ8BAf8EBAMCB4AwEwYDVR0lBAwwCgYIKwYBBQUH\n" \
"AwEwDAYDVR0TAQH/BAIwADAdBgNVHQ4EFgQUn9s6xwZqJNPn2S7GBvgewUShDNcw\n" \
"HwYDVR0jBBgwFoAUmNH4bhDrz5vsYJ8YkBug630J/SswZAYIKwYBBQUHAQEEWDBW\n" \
"MCcGCCsGAQUFBzABhhtodHRwOi8vb2NzcC5wa2kuZ29vZy9ndHMxbzEwKwYIKwYB\n" \
"BQUHMAKGH2h0dHA6Ly9wa2kuZ29vZy9nc3IyL0dUUzFPMS5jcnQwggSoBgNVHREE\n" \
"ggSfMIIEm4IMKi5nb29nbGUuY29tgg0qLmFuZHJvaWQuY29tghYqLmFwcGVuZ2lu\n" \
"ZS5nb29nbGUuY29tggkqLmJkbi5kZXaCEiouY2xvdWQuZ29vZ2xlLmNvbYIYKi5j\n" \
"cm93ZHNvdXJjZS5nb29nbGUuY29tggYqLmcuY2+CDiouZ2NwLmd2dDIuY29tghEq\n" \
"LmdjcGNkbi5ndnQxLmNvbYIKKi5nZ3BodC5jboIOKi5na2VjbmFwcHMuY26CFiou\n" \
"Z29vZ2xlLWFuYWx5dGljcy5jb22CCyouZ29vZ2xlLmNhggsqLmdvb2dsZS5jbIIO\n" \
"Ki5nb29nbGUuY28uaW6CDiouZ29vZ2xlLmNvLmpwgg4qLmdvb2dsZS5jby51a4IP\n" \
"Ki5nb29nbGUuY29tLmFygg8qLmdvb2dsZS5jb20uYXWCDyouZ29vZ2xlLmNvbS5i\n" \
"coIPKi5nb29nbGUuY29tLmNvgg8qLmdvb2dsZS5jb20ubXiCDyouZ29vZ2xlLmNv\n" \
"bS50coIPKi5nb29nbGUuY29tLnZuggsqLmdvb2dsZS5kZYILKi5nb29nbGUuZXOC\n" \
"CyouZ29vZ2xlLmZyggsqLmdvb2dsZS5odYILKi5nb29nbGUuaXSCCyouZ29vZ2xl\n" \
"Lm5sggsqLmdvb2dsZS5wbIILKi5nb29nbGUucHSCEiouZ29vZ2xlYWRhcGlzLmNv\n" \
"bYIPKi5nb29nbGVhcGlzLmNughEqLmdvb2dsZWNuYXBwcy5jboIUKi5nb29nbGVj\n" \
"b21tZXJjZS5jb22CESouZ29vZ2xldmlkZW8uY29tggwqLmdzdGF0aWMuY26CDSou\n" \
"Z3N0YXRpYy5jb22CEiouZ3N0YXRpY2NuYXBwcy5jboIKKi5ndnQxLmNvbYIKKi5n\n" \
"dnQyLmNvbYIUKi5tZXRyaWMuZ3N0YXRpYy5jb22CDCoudXJjaGluLmNvbYIQKi51\n" \
"cmwuZ29vZ2xlLmNvbYITKi53ZWFyLmdrZWNuYXBwcy5jboIWKi55b3V0dWJlLW5v\n" \
"Y29va2llLmNvbYINKi55b3V0dWJlLmNvbYIWKi55b3V0dWJlZWR1Y2F0aW9uLmNv\n" \
"bYIRKi55b3V0dWJla2lkcy5jb22CByoueXQuYmWCCyoueXRpbWcuY29tghphbmRy\n" \
"b2lkLmNsaWVudHMuZ29vZ2xlLmNvbYILYW5kcm9pZC5jb22CG2RldmVsb3Blci5h\n" \
"bmRyb2lkLmdvb2dsZS5jboIcZGV2ZWxvcGVycy5hbmRyb2lkLmdvb2dsZS5jboIE\n" \
"Zy5jb4IIZ2dwaHQuY26CDGdrZWNuYXBwcy5jboIGZ29vLmdsghRnb29nbGUtYW5h\n" \
"bHl0aWNzLmNvbYIKZ29vZ2xlLmNvbYIPZ29vZ2xlY25hcHBzLmNughJnb29nbGVj\n" \
"b21tZXJjZS5jb22CGHNvdXJjZS5hbmRyb2lkLmdvb2dsZS5jboIKdXJjaGluLmNv\n" \
"bYIKd3d3Lmdvby5nbIIIeW91dHUuYmWCC3lvdXR1YmUuY29tghR5b3V0dWJlZWR1\n" \
"Y2F0aW9uLmNvbYIPeW91dHViZWtpZHMuY29tggV5dC5iZTAhBgNVHSAEGjAYMAgG\n" \
"BmeBDAECAjAMBgorBgEEAdZ5AgUDMC8GA1UdHwQoMCYwJKAioCCGHmh0dHA6Ly9j\n" \
"cmwucGtpLmdvb2cvR1RTMU8xLmNybDCCAQUGCisGAQQB1nkCBAIEgfYEgfMA8QB3\n" \
"ALIeBcyLos2KIE6HZvkruYolIGdr2vpw57JJUy3vi5BeAAABceQk7HEAAAQDAEgw\n" \
"RgIhAMeaPA4eH4PQ6P80cE7pV9+cA+JzHsfEHXybUpJYTUUqAiEAtt6UgO7o9Bo5\n" \
"T83b8KngOaFoAMEitVL5ckcpZHNtOaQAdgBep3P531bA57U2SH3QSeAyepGaDISh\n" \
"EhKEGHWWgXFFWAAAAXHkJOyPAAAEAwBHMEUCIQDLXewTtt5w1Pykw4iJLVEBNWsU\n" \
"8LazX+MIkUmuOpwJQwIgIXySwReiZv9FbIJ/73ytICnrPGNkD43+PVMge9cJ0gQw\n" \
"DQYJKoZIhvcNAQELBQADggEBAM/x3sGLTHpoan0gd9XdVCG6HsQynQEzLL25kTvN\n" \
"q14pRburIrsdFWhtEETqNJo7IG19PozR6IdJkQqEBYjw6D9rRniikWeski5MhcFD\n" \
"fU3ycQ2I2ISlAd3HelYNbVDJ8zJWerEGk7dyi2O/UmRreXHhi+dry8IgTiSssYNA\n" \
"fht9x4GVvFTT6gap4E1Qy5UFMBGMqXmhXNoH9bYX1oY6N+8xr5tkTSQfV0T1kXKJ\n" \
"WUhnDkwMUnvwuMUEP7elcvp7OgOslSQ5zwjnR3zSDozO072YR+L9SGMICCZz1ha1\n" \
"DMCTA95gzVKezFCaUidRU9UyHOFzltfYDt7HRlp7MwWoPLM=\n" \
"-----END CERTIFICATE-----\n";


void setup() {

  Serial.begin(9600);
  delay(1000);

 //Wifi part
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 //end wifi part

}

void loop() {

 if(WiFi.status()== WL_CONNECTED){   

   HTTPClient http;    
   http.begin("url_here"); 
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
   auto httpCode = http.POST("id=data_s_1&data1=10&data2=20&data3=30&data4=40"); 
   String payload = http.getString();                  
   Serial.println(httpCode);   
   Serial.println(payload);    
   http.end();  

 }else{

    Serial.println("Error in WiFi connection");   

 }

  delay(30000);  

}