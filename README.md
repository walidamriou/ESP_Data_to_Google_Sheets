# ESP Data to Google Sheets
Upload data to Google Sheets from  Espressif Systems ESP32 &amp; ESP8266 

### Google drive:  
__1- Create a Google Sheets file (https://docs.google.com/spreadsheets/?usp=mkt_sheets) or you can use data_from_esp32.ods file from /sheets by upload it to your Google drive.__  
__2- open the Google sheets file and go to Tools -> Script editor to use Google Apps Script.__
Google Apps Script is a rapid application development platform that makes it fast and easy to create business applications that integrate with G Suite. You write code in modern JavaScript and have access to built-in libraries for favorite G Suite applications like Gmail, Calendar, Drive, and more. There's nothing to install—we give you a code editor right in your browser, and your scripts run on Google's servers. 
more info here: https://developers.google.com/apps-script/    
__3- use the code from Google_apps_scripts/script1.gs , it is general code, and after that save the script and Go to Publish -> Deploy as web app, publish it as accessible to Anyone. Execute the app as Me. remember to assign a new version whenever you are making changes and deploying it again. Copy the link that is provided to you, at this step.__  

__4- if you use data_from_esp32.ods file you can test by put the link that get it after publish the app script with queries (?id=data_s_1&data1=10&data2=20&data3=30&data4=40) in your browser, you need to give the code permissions in first use__ 
https://script.google.com/macros/s/your_id_of_the_script_here/exec?id=data_s_1&data1=10&data2=20&data3=30&data4=40

### References:
[Reference 1](https://developers.google.com/apps-script/reference/spreadsheet/sheet "Reference 1")
[Reference 2](https://developers.google.com/apps-script/guides/projects "Reference 2")
[Reference 3](https://gist.github.com/mhawksey/1276293/eb4db55a7559d9ac4a2600acb60b0af5f9a347fc "Reference 3")
[Reference 4](https://medium.com/@shishir_dey/upload-data-to-google-sheet-with-an-esp32-and-some-scripting-2d8b0ccbc833 "Reference 4")
