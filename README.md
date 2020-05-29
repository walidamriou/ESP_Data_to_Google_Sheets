# Espressif Systems ESP32 or ESP8266 board Data to Google Sheets
Upload data to Google Sheets from  Espressif Systems ESP32 or ESP8266 board
<p align="center">
  <img width="50%" height="50%" src="https://github.com/walidamriou/ESP_Data_to_Google_Sheets/blob/master/Screenshots/post_googlesheet_esp.jpg">
</p>

--------------------  

Reasons to Use Google Sheets for IoT Sensor Data
- Logging sensor data from your embedded devices to Google Sheets is simple.
- Can mixte between data from your sensors and another source.
- Easy make a data visualization like a graph,... etc.
- Embed your graphed data on the web.
- Manipulate and analyze your data with default functions or by javascript functions (Apps Script).
- You can check in on your data in the mobile by google sheets app.
- You can make conditions actions with the incoming data (by Apps script or javascript). 

--------------------  


### POST vs GET method
__POST__ sumbits data (include in the body) to be processed to the indentified resource, the effect of this method is create a new resource or update existing resource or both.
__GET__ requests a representation of the specified resource.
In general, GET is used to retrieve remote data, and POST is used to insert/update remote data, because GET can used arvitrily by robots (secripts) or crawlers, and for our work can make a problem with our data in the sheet. But just because we learn, we use the two methods to send the data to Google sheets but __The security of the implementation is your work__.

--------------------  

### by GET method
##### Google drive:  
__1- Create a Google Sheets file (https://docs.google.com/spreadsheets/?usp=mkt_sheets) or you can use data_from_esp32.ods file from /sheets by upload it to your Google drive.__  
__2- open the Google sheets file and go to Tools -> Script editor to use Google Apps Script.__
Google Apps Script is a rapid application development platform that makes it fast and easy to create business applications that integrate with G Suite. You write code in modern JavaScript and have access to built-in libraries for favorite G Suite applications like Gmail, Calendar, Drive, and more. There's nothing to install—we give you a code editor right in your browser, and your scripts run on Google's servers. 
more info here: https://developers.google.com/apps-script/    
__3- use the code from Google_apps_scripts/script1.gs , it is general code, and after that save the script and Go to Publish -> Deploy as web app, publish it as accessible to Anyone. Execute the app as Me. remember to assign a new version whenever you are making changes and deploying it again. Copy the link that is provided to you, at this step.__  

__4- if you use data_from_esp32.ods file you can test by put the link that get it after publish the app script with queries (?id=data_s_1&data1=10&data2=20&data3=30&data4=40) in your browser, you need to give the code permissions in first use__ 
https://script.google.com/macros/s/your_id_of_the_script_here/exec?id=data_s_1&data1=10&data2=20&data3=30&data4=40

##### ESP board:  
##### -- Platfomio with Arduino: 
use the code in: [ESP_code/main_https_get_by_arduino_platformio.c](https://github.com/walidamriou/ESP_Data_to_Google_Sheets/blob/master/ESP_code/main_https_GET_by_arduino_platformio.c "code") the comments in the code will help you.  
##### -- ESP-IDF: 
It will be published later

--------------------  

### by POST method
##### Google drive:  
The same notes of "by GET method" but use [/Google_apps_scripts/Google_App_Scripts_POST_receive_for_project.gs](https://github.com/walidamriou/ESP_Data_to_Google_Sheets/blob/master/Google_apps_scripts/Google_App_Scripts_POST_receive_for_project.gs "code") 

##### ESP board:  
##### -- Platfomio with Arduino: 
use the code in: [ESP_code/main_https_POST_by_arduino_platformio.c](https://github.com/walidamriou/ESP_Data_to_Google_Sheets/blob/master/ESP_code/main_https_POST_by_arduino_platformio.c "code") the comments in the code will help you.  
##### -- ESP-IDF: 
It will be published later

--------------------  

### Tools used:
#### Software
- VScode  
- ESP-IDF  
- Platformio  
- https://requestcatcher.com Request Catcher will create a subdomain on which you can test an application. All requests sent to any path on the subdomain are forwarded to the browser in real time. I use it as Https server requests for test. 
- Postman 

#### Hardware
- ESP Lolin32    

--------------------  

### References:
[Reference 1](https://developers.google.com/apps-script/reference/spreadsheet/sheet "Reference 1") , 
[Reference 2](https://developers.google.com/apps-script/guides/projects "Reference 2") , 
[Reference 3](https://gist.github.com/mhawksey/1276293/eb4db55a7559d9ac4a2600acb60b0af5f9a347fc "Reference 3") , 
[Reference 4](https://medium.com/@shishir_dey/upload-data-to-google-sheet-with-an-esp32-and-some-scripting-2d8b0ccbc833 "Reference 4") , 
[Reference 5](https://stackoverflow.com/questions/3477333/what-is-the-difference-between-post-and-get "Reference 5") , 
[Reference 6](https://www.w3schools.com/tags/ref_httpmethods.asp "Reference 6") , 
[Reference 7](https://techtutorialsx.com/2017/11/18/esp32-arduino-https-get-request/ "Reference 7") ,
[Reference 8](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/protocols/esp_http_client.html "Reference 8") , 
[Reference 9](https://techtutorialsx.com/2016/07/21/esp8266-post-requests/ "Reference 9") , 
[Reference 10](https://dzone.com/articles/reasons-to-use-google-sheets-for-iot-sensor-data "Reference 10")



