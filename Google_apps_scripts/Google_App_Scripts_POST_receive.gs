function doPost(e) {
  Logger.log(e.parameter.name);
  return respond(JSON.stringify({result: e.parameter.name}));
}


function respond(response) {  
  return ContentService
  .createTextOutput(response)
  .setMimeType(ContentService.MimeType.JSON)
}