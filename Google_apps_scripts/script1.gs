/* 
 ******************************************************************** 
  ESP Data to Google Sheets project
  Upload data to Google Sheets from Espressif Systems ESP32 & ESP8266

  by Walid Amriou
  Github : https://github.com/walidamriou/ESP_Data_to_Google_Sheets

 ******************************************************************** 
*/

/*
 About doGet(e) function
 When a user visits an app or a program sends the app an HTTP GET request, Apps Script
 runs the function doGet(e). When a program sends the app an  HTTP POST request, Apps Script runs
 doPost(e) instead. In both cases, the e argument represents an event parameter that can contain 
 information about any request parameters.
 more info here: https://developers.google.com/apps-script/guides/web
*/

function doGet(e){
  // open the sheets file
  let sheets_file = SpreadsheetApp.getActive();
  
  // use the 'id' parameter to differentiate between sheets
  // if you use Sheets/data_from_esp32.ods file the id here is data_s_1 or data_s_2
  // for me "data_s_1" mean data from sensor 1 
  let sheet_from_sheets_file = sheets_file.getSheetByName(e.parameter["id"]);
  
  /*  
   In general, we use getRange(row, column, numRows, numColumns) to Returns 
   the range with the top left cell at the given coordinates with the given
   number of rows and columns. In our code, we use it to get the number of 
   the headers. getLastColumn returns the position of the last column that 
   has content.
  */
  let numbers_sheet_headers = sheet_from_sheets_file.getRange(1, 1, 1, sheet_from_sheets_file.getLastColumn()).getValues()[0];
  
  // get the position of the last row to lastRow valure
  let last_Row = sheet_from_sheets_file.getLastRow();
  
  /*
   get cell A1 from the first sheet. In other, getRange return object type Range, so we can 
   say that we just make a cell as a object Range to can play with it by the functions of
   the class Range.

   Why make object range? to Access and modify spreadsheet ranges. A range can be a single 
   cell in a sheet or a group of adjacent cells in a sheet.

   more about class Range: https://developers.google.com/apps-script/reference/spreadsheet/range
  */ 
  let cell = sheet_from_sheets_file.getRange('a1');
  
  //to start from column 0 :D 
  let column = 0;
  
  // to know the date of the data, when the data send or collect
  let current_date = new Date();
  
  //just var to use in next
  let valure_apprend

  // loop in the headers number and if a parameter name matches the header name insert the value
  for (i in numbers_sheet_headers){
    // if the parameter name= timestamp, we can use other method when i === 0 
    if (numbers_sheet_headers[i] === "Timestamp")
    {
      // date day , local time exmple: Sun May 24 2020, 10:15:03 PM
      valure_apprend = current_date.toDateString() + ", " + current_date.toLocaleTimeString();
    }

    //other data type, in the example I just add data1, data2 .. 
    else
    {
      valure_apprend = e.parameter[numbers_sheet_headers[i]]; 
    }
    
    // append the data to the last row
    cell.offset(last_Row, column).setValue(valure_apprend);

    column++;
  }
  //when complete the operations :D just print success
  return ContentService.createTextOutput('success');
}