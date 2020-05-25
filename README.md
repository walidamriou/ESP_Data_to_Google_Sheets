# ESP Data to Google Sheets
Upload data to Google Sheets from  Espressif Systems ESP32 &amp; ESP8266 

### POST vs GET method
__POST__ sumbits data (include in the body) to be processed to the indentified resource, the effect of this method is create a new resource or update existing resource or both.
__GET__ requests a representation of the specified resource.
In general, GET is used to retrieve remote data, and POST is used to insert/update remote data, because GET can used arvitrily by robots (secripts) or crawlers, and for our work can make a problem with our data in the sheet. But just because we learn, we use the two methods to send the data to Google sheets but __The security of the implementation is your work__.

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
use the code in: ESP_code/main_https_get_by_arduino_platfomio.c


### References:
[Reference 1](https://developers.google.com/apps-script/reference/spreadsheet/sheet "Reference 1") , 
[Reference 2](https://developers.google.com/apps-script/guides/projects "Reference 2") , 
[Reference 3](https://gist.github.com/mhawksey/1276293/eb4db55a7559d9ac4a2600acb60b0af5f9a347fc "Reference 3") , 
[Reference 4](https://medium.com/@shishir_dey/upload-data-to-google-sheet-with-an-esp32-and-some-scripting-2d8b0ccbc833 "Reference 4") , 
[Reference 5](https://stackoverflow.com/questions/3477333/what-is-the-difference-between-post-and-get "Reference 5")
[Reference 6](https://www.w3schools.com/tags/ref_httpmethods.asp "Reference 6")

