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

const char* Https_certificate= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIPADCCDeigAwIBAgIQMaF+AzZIr7UIAAAAAD6+AjANBgkqhkiG9w0BAQsFADBC\n" \
"MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZpY2VzMRMw\n" \
"EQYDVQQDEwpHVFMgQ0EgMU8xMB4XDTIwMDUwNTA4MjkyOVoXDTIwMDcyODA4Mjky\n" \
"OVowcTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcT\n" \
"DU1vdW50YWluIFZpZXcxEzARBgNVBAoTCkdvb2dsZSBMTEMxIDAeBgNVBAMMFyou\n" \
"Z29vZ2xldXNlcmNvbnRlbnQuY29tMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE\n" \
"XnlH+fpWPSWZlXKlpCfZUDR+rfbZZ59Y5THSU6mkw65vurZxI9jKC6D8oSL2Xp7I\n" \
"EE9cZTkHbLzoOuVdNd44aqOCDIwwggyIMA4GA1UdDwEB/wQEAwIHgDATBgNVHSUE\n" \
"DDAKBggrBgEFBQcDATAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBTcSj0qieO75aYl\n" \
"iCuEmuk7Y6UxMDAfBgNVHSMEGDAWgBSY0fhuEOvPm+xgnxiQG6DrfQn9KzBkBggr\n" \
"BgEFBQcBAQRYMFYwJwYIKwYBBQUHMAGGG2h0dHA6Ly9vY3NwLnBraS5nb29nL2d0\n" \
"czFvMTArBggrBgEFBQcwAoYfaHR0cDovL3BraS5nb29nL2dzcjIvR1RTMU8xLmNy\n" \
"dDCCCk4GA1UdEQSCCkUwggpBghcqLmdvb2dsZXVzZXJjb250ZW50LmNvbYIcKi5h\n" \
"cHBzLmdvb2dsZXVzZXJjb250ZW50LmNvbYIkKi5hcHBzcG90LmNvbS5zdG9yYWdl\n" \
"Lmdvb2dsZWFwaXMuY29tgj0qLmF1ZGlvYm9vay1hZGRpdGlvbmFsLW1hdGVyaWFs\n" \
"LXN0YWdpbmcuZ29vZ2xldXNlcmNvbnRlbnQuY29tgjUqLmF1ZGlvYm9vay1hZGRp\n" \
"dGlvbmFsLW1hdGVyaWFsLmdvb2dsZXVzZXJjb250ZW50LmNvbYIOKi5ibG9nc3Bv\n" \
"dC5jb22CESouYnAuYmxvZ3Nwb3QuY29tgiIqLmNvbW1vbmRhdGFzdG9yYWdlLmdv\n" \
"b2dsZWFwaXMuY29tgiQqLmNvbXBvc2VyLWRldi5nb29nbGV1c2VyY29udGVudC5j\n" \
"b22CIyouY29tcG9zZXItcWEuZ29vZ2xldXNlcmNvbnRlbnQuY29tgigqLmNvbXBv\n" \
"c2VyLXN0YWdpbmcuZ29vZ2xldXNlcmNvbnRlbnQuY29tgiAqLmNvbXBvc2VyLmdv\n" \
"b2dsZXVzZXJjb250ZW50LmNvbYIpKi5jb250ZW50LXN0b3JhZ2UtZG93bmxvYWQu\n" \
"Z29vZ2xlYXBpcy5jb22CJyouY29udGVudC1zdG9yYWdlLXVwbG9hZC5nb29nbGVh\n" \
"cGlzLmNvbYIgKi5jb250ZW50LXN0b3JhZ2UuZ29vZ2xlYXBpcy5jb22CKiouZGF0\n" \
"YWZ1c2lvbi1hcGktZGV2Lmdvb2dsZXVzZXJjb250ZW50LmNvbYIuKi5kYXRhZnVz\n" \
"aW9uLWFwaS1zdGFnaW5nLmdvb2dsZXVzZXJjb250ZW50LmNvbYImKi5kYXRhZnVz\n" \
"aW9uLWFwaS5nb29nbGV1c2VyY29udGVudC5jb22CJiouZGF0YWZ1c2lvbi1kZXYu\n" \
"Z29vZ2xldXNlcmNvbnRlbnQuY29tgioqLmRhdGFmdXNpb24tc3RhZ2luZy5nb29n\n" \
"bGV1c2VyY29udGVudC5jb22CIiouZGF0YWZ1c2lvbi5nb29nbGV1c2VyY29udGVu\n" \
"dC5jb22CKCouZGF0YXByb2Mtc3RhZ2luZy5nb29nbGV1c2VyY29udGVudC5jb22C\n" \
"JSouZGF0YXByb2MtdGVzdC5nb29nbGV1c2VyY29udGVudC5jb22CICouZGF0YXBy\n" \
"b2MuZ29vZ2xldXNlcmNvbnRlbnQuY29tgiQqLmRldi5hbXA0bWFpbC5nb29nbGV1\n" \
"c2VyY29udGVudC5jb22CHCouZG91YmxlY2xpY2t1c2VyY29udGVudC5jb22CNSou\n" \
"ZnVjaHNpYS11cGRhdGVzLWF1dG9wdXNoLXF1YWwuZ29vZ2xldXNlcmNvbnRlbnQu\n" \
"Y29tgjAqLmZ1Y2hzaWEtdXBkYXRlcy1hdXRvcHVzaC5nb29nbGV1c2VyY29udGVu\n" \
"dC5jb22CKyouZnVjaHNpYS11cGRhdGVzLWRldi5nb29nbGV1c2VyY29udGVudC5j\n" \
"b22CLyouZnVjaHNpYS11cGRhdGVzLXN0YWdpbmcuZ29vZ2xldXNlcmNvbnRlbnQu\n" \
"Y29tgicqLmZ1Y2hzaWEtdXBkYXRlcy5nb29nbGV1c2VyY29udGVudC5jb22CGyou\n" \
"Z2NjLmdvb2dsZXVzZXJjb250ZW50LmNvbYILKi5nZ3BodC5jb22CESouZ29vZ2xl\n" \
"ZHJpdmUuY29tghcqLmdvb2dsZXN5bmRpY2F0aW9uLmNvbYIUKi5nb29nbGV3ZWJs\n" \
"aWdodC5jb22CGyouZ3NjLmdvb2dsZXVzZXJjb250ZW50LmNvbYIhKi5ub3RlYm9v\n" \
"a3MuZ29vZ2xldXNlcmNvbnRlbnQuY29tgiEqLnBpcGVsaW5lcy5nb29nbGV1c2Vy\n" \
"Y29udGVudC5jb22CNCoucGxheWdyb3VuZC1pbnRlcm5hbC5hbXA0bWFpbC5nb29n\n" \
"bGV1c2VyY29udGVudC5jb22CKyoucGxheWdyb3VuZC5hbXA0bWFpbC5nb29nbGV1\n" \
"c2VyY29udGVudC5jb22CJSoucHJvZC5hbXA0bWFpbC5nb29nbGV1c2VyY29udGVu\n" \
"dC5jb22CISouc2FmZWZyYW1lLmdvb2dsZXN5bmRpY2F0aW9uLmNvbYIfKi5zYWZl\n" \
"bnVwLmdvb2dsZXVzZXJjb250ZW50LmNvbYIfKi5zYW5kYm94Lmdvb2dsZXVzZXJj\n" \
"b250ZW50LmNvbYIhKi5zdG9yYWdlLWRvd25sb2FkLmdvb2dsZWFwaXMuY29tgh8q\n" \
"LnN0b3JhZ2UtdXBsb2FkLmdvb2dsZWFwaXMuY29tghgqLnN0b3JhZ2UuZ29vZ2xl\n" \
"YXBpcy5jb22CHyouc3RvcmFnZS5zZWxlY3QuZ29vZ2xlYXBpcy5jb22CECoudHJh\n" \
"bnNsYXRlLmdvb2eCJCoudHVmLWF1dG9wdXNoLmdvb2dsZXVzZXJjb250ZW50LmNv\n" \
"bYIfKi50dWYtZGV2Lmdvb2dsZXVzZXJjb250ZW50LmNvbYIjKi50dWYtc3RhZ2lu\n" \
"Zy5nb29nbGV1c2VyY29udGVudC5jb22CGyoudHVmLmdvb2dsZXVzZXJjb250ZW50\n" \
"LmNvbYIMYmxvZ3Nwb3QuY29tgg9icC5ibG9nc3BvdC5jb22CIGNvbW1vbmRhdGFz\n" \
"dG9yYWdlLmdvb2dsZWFwaXMuY29tghpkb3VibGVjbGlja3VzZXJjb250ZW50LmNv\n" \
"bYIJZ2dwaHQuY29tgg9nb29nbGVkcml2ZS5jb22CFWdvb2dsZXVzZXJjb250ZW50\n" \
"LmNvbYISZ29vZ2xld2VibGlnaHQuY29tgiVtYW5pZmVzdC5jLm1haWwuZ29vZ2xl\n" \
"dXNlcmNvbnRlbnQuY29tgiVtYW5pZmVzdC5saDMtZGEuZ29vZ2xldXNlcmNvbnRl\n" \
"bnQuY29tgiVtYW5pZmVzdC5saDMtZGIuZ29vZ2xldXNlcmNvbnRlbnQuY29tgiVt\n" \
"YW5pZmVzdC5saDMtZGMuZ29vZ2xldXNlcmNvbnRlbnQuY29tgiVtYW5pZmVzdC5s\n" \
"aDMtZGQuZ29vZ2xldXNlcmNvbnRlbnQuY29tgiVtYW5pZmVzdC5saDMtZGUuZ29v\n" \
"Z2xldXNlcmNvbnRlbnQuY29tgiVtYW5pZmVzdC5saDMtZGYuZ29vZ2xldXNlcmNv\n" \
"bnRlbnQuY29tgiVtYW5pZmVzdC5saDMtZGcuZ29vZ2xldXNlcmNvbnRlbnQuY29t\n" \
"giVtYW5pZmVzdC5saDMtZHouZ29vZ2xldXNlcmNvbnRlbnQuY29tgiJtYW5pZmVz\n" \
"dC5saDMuZ29vZ2xldXNlcmNvbnRlbnQuY29tgh5tYW5pZmVzdC5saDMucGhvdG9z\n" \
"Lmdvb2dsZS5jb22CFnN0b3JhZ2UuZ29vZ2xlYXBpcy5jb22CHXN0b3JhZ2Uuc2Vs\n" \
"ZWN0Lmdvb2dsZWFwaXMuY29tgg50cmFuc2xhdGUuZ29vZ4IPdW5maWx0ZXJlZC5u\n" \
"ZXdzMCEGA1UdIAQaMBgwCAYGZ4EMAQICMAwGCisGAQQB1nkCBQMwLwYDVR0fBCgw\n" \
"JjAkoCKgIIYeaHR0cDovL2NybC5wa2kuZ29vZy9HVFMxTzEuY3JsMIIBBQYKKwYB\n" \
"BAHWeQIEAgSB9gSB8wDxAHYAsh4FzIuizYogTodm+Su5iiUgZ2va+nDnsklTLe+L\n" \
"kF4AAAFx5Cs8pQAABAMARzBFAiEA6NWPPmccTMmgGMYofN/9VX0m9vNPRA21bRsg\n" \
"YjHcGMUCIHzWszWoRkKBOkjxmby+DpWeQd2IGzivdBnsNY1V+UqMAHcAXqdz+d9W\n" \
"wOe1Nkh90EngMnqRmgyEoRIShBh1loFxRVgAAAFx5Cs8wwAABAMASDBGAiEAzfkB\n" \
"uZPo0DqWAozDDVsuYYCtNj7ul3/ISpgr/LaqpbsCIQCwCXQpX6YvFIchwiDw87eQ\n" \
"t+U5w4ciohbVfCTYYY2lozANBgkqhkiG9w0BAQsFAAOCAQEAWjDKAFRBYhNp9EE1\n" \
"wTp7o9yF7hTU7T0Pij11wZLd3u1fgm/Pw22So+SlCKZBSYJ9e7e3OmdR+KFOYbhd\n" \
"0IryWAOCaLZAb5hQ32LJ+kd5XP4UZuGKR4098X53pJ70vEwH00Jx4aYFbwlK+JJd\n" \
"zhtz0eAAgf2Z/ghcGLa3vzOiFK6tszhHTQPIEoISH/xSv50hNSg0Swx18R4m18B3\n" \
"IuSIG3cz/CvlWIl1eCRQbkMUH5WKViT6a4KjhY9FiDaEk3+MEw9sjJBUTJCqEDoZ\n" \
"3UudypCAmK9152l2JTF0PgWd8TtZcXVmO9gvynqty1VW8kOYf9gHRe57LKCfVe3t\n" \
"fmI/Og==\n" \
"-----END CERTIFICATE-----\n";

void loop() {

 if(WiFi.status()== WL_CONNECTED){   

   HTTPClient http;    
   http.addHeader("Content-Type", "text/plain");  
   int httpCode = http.POST("Message from ESP32");   
   String payload = http.getString();                  
   Serial.println(httpCode);   
   Serial.println(payload);    
   http.end();  

 }else{

    Serial.println("Error in WiFi connection");   

 }

  delay(30000);  

}