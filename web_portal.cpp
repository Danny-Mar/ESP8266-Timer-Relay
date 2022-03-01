#include "web_portal.h"

ESP8266WebServer server ( 80 );

struct CurrentTime Present;
bool outputStatus;


void start_server(){
    server.on ("/", handleRoot);
    server.on ("/set", handleSet);
    
    server.begin();
}


void handle_client(struct CurrentTime temptime, bool relayStatus){
Present = temptime;
outputStatus = relayStatus;
server.handleClient();
}


void handleRoot()
{

  String Timer1SetHTML;
  String Timer2SetHTML;
  String Timer3SetHTML; 
  String Timer4SetHTML;
  String Timer5SetHTML;
  String DayLtSaveSetHTML;
  String Page;
  char tempOnTime[6][6];
  char tempOffTime[6][6];  
  struct TimerDataStruct TimerSettings;

  EEPROM_readAnything(100,TimerSettings);


  for(int i = 0; i <6; i++)
  {
      if(TimerSettings.HourOn[i]<10 && TimerSettings.MinuteOn[i]<10)
      {
        sprintf(tempOnTime[i],"0%d:0%d", TimerSettings.HourOn[i],TimerSettings.MinuteOn[i]);
      }
      else if(TimerSettings.HourOn[i]<10)
      {
        sprintf(tempOnTime[i],"0%d:%d", TimerSettings.HourOn[i],TimerSettings.MinuteOn[i]);
      }
      else if(TimerSettings.MinuteOn[i]<10)
      {
        sprintf(tempOnTime[i],"%d:0%d", TimerSettings.HourOn[i],TimerSettings.MinuteOn[i]);
      }
      else
      {
        sprintf(tempOnTime[i],"%d:%d", TimerSettings.HourOn[i],TimerSettings.MinuteOn[i]);
      }
  }
  tempOnTime[6][0] = '\0';

  for(int i = 0; i <6; i++)
  {
      if(TimerSettings.HourOff[i]<10 && TimerSettings.MinuteOff[i]<10)
      {
        sprintf(tempOffTime[i],"0%d:0%d", TimerSettings.HourOff[i],TimerSettings.MinuteOff[i]);
      }
      else if(TimerSettings.HourOff[i]<10)
      {
        sprintf(tempOffTime[i],"0%d:%d", TimerSettings.HourOff[i],TimerSettings.MinuteOff[i]);
      }
      else if(TimerSettings.MinuteOff[i]<10)
      {
        sprintf(tempOffTime[i],"%d:0%d", TimerSettings.HourOff[i],TimerSettings.MinuteOff[i]);
      }
      else
      {
        sprintf(tempOffTime[i],"%d:%d", TimerSettings.HourOff[i],TimerSettings.MinuteOff[i]);
      }
  }
  tempOffTime[6][0] = '\0';

  
  if(TimerSettings.TimerOn[1]){
    Timer1SetHTML = "<input type=\"radio\" name=\"Timer1State\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"Timer1State\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer1OnValue\" id=\"Timer1OnValue\" value='";
    Timer1SetHTML += tempOnTime[1];
	Timer1SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer1OffValue\" id=\"Timer1OffValue\" value='";
    Timer1SetHTML += tempOffTime[1];
    Timer1SetHTML += "' size=2 autofocus>";    
                     
  }else{
    Timer1SetHTML = "<input type=\"radio\" name=\"Timer1State\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"Timer1State\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer1OnValue\" id=\"Timer1OnValue\" value='";
    Timer1SetHTML += tempOnTime[1];
	Timer1SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer1OffValue\" id=\"Timer1OffValue\" value='";
    Timer1SetHTML += tempOffTime[1];
    Timer1SetHTML += "' size=2 autofocus>";                           
  } 
  
  if(TimerSettings.TimerOn[2]){
    Timer2SetHTML = "<input type=\"radio\" name=\"Timer2State\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"Timer2State\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer2OnValue\" id=\"Timer2OnValue\" value='";
    Timer2SetHTML += tempOnTime[2];
	Timer2SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer2OffValue\" id=\"Timer2OffValue\" value='";
    Timer2SetHTML += tempOffTime[2];
    Timer2SetHTML += "' size=2 autofocus>";    
                     
  }else{
    Timer2SetHTML = "<input type=\"radio\" name=\"Timer2State\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"Timer2State\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer2OnValue\" id=\"Timer2OnValue\" value='";
    Timer2SetHTML += tempOnTime[2];
	Timer2SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer2OffValue\" id=\"Timer2OffValue\" value='";
    Timer2SetHTML += tempOffTime[2];
    Timer2SetHTML += "' size=2 autofocus>";                         
  } 
  

  if(TimerSettings.TimerOn[3]){
    Timer3SetHTML = "<input type=\"radio\" name=\"Timer3State\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"Timer3State\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer3OnValue\" id=\"Timer3OnValue\" value='";
    Timer3SetHTML += tempOnTime[3];
	Timer3SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer3OffValue\" id=\"Timer3OffValue\" value='";
    Timer3SetHTML += tempOffTime[3];
    Timer3SetHTML += "' size=2 autofocus>";    
                     
  }else{
    Timer3SetHTML = "<input type=\"radio\" name=\"Timer3State\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"Timer3State\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer3OnValue\" id=\"Timer3OnValue\" value='";
    Timer3SetHTML += tempOnTime[3];
	Timer3SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer3OffValue\" id=\"Timer3OffValue\" value='";
    Timer3SetHTML += tempOffTime[3];
    Timer3SetHTML += "' size=2 autofocus>";                          
  }

  if(TimerSettings.TimerOn[4]){
    Timer4SetHTML = "<input type=\"radio\" name=\"Timer4State\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"Timer4State\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer4OnValue\" id=\"Timer4OnValue\" value='";
    Timer4SetHTML += tempOnTime[4];
	Timer4SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer4OffValue\" id=\"Timer4OffValue\" value='";
    Timer4SetHTML += tempOffTime[4];
    Timer4SetHTML += "' size=2 autofocus>";    
                     
  }else{
    Timer4SetHTML = "<input type=\"radio\" name=\"Timer4State\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"Timer4State\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer4OnValue\" id=\"Timer4OnValue\" value='";
    Timer4SetHTML += tempOnTime[4];
	Timer4SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer4OffValue\" id=\"Timer4OffValue\" value='";
    Timer4SetHTML += tempOffTime[4];
    Timer4SetHTML += "' size=2 autofocus>";                        
  }

  if(TimerSettings.TimerOn[5]){
    Timer5SetHTML = "<input type=\"radio\" name=\"Timer5State\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"Timer5State\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer5OnValue\" id=\"Timer5OnValue\" value='";
    Timer5SetHTML += tempOnTime[5];
	Timer5SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer5OffValue\" id=\"Timer5OffValue\" value='";
    Timer5SetHTML += tempOffTime[5];
    Timer5SetHTML += "' size=2 autofocus>";    
                     
  }else{
    Timer5SetHTML = "<input type=\"radio\" name=\"Timer5State\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"Timer5State\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"Timer5OnValue\" id=\"Timer5OnValue\" value='";
    Timer5SetHTML += tempOnTime[5];
	Timer5SetHTML += "' size=2 autofocus> until <input type=\"text\" name=\"Timer5OffValue\" id=\"Timer5OffValue\" value='";
    Timer5SetHTML += tempOffTime[5];
    Timer5SetHTML += "' size=2 autofocus>";                        
  }

  if(TimerSettings.TimerOn[6]){
    DayLtSaveSetHTML = "<input type=\"radio\" name=\"DayLtSaveState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"DayLtSaveState\" value=\"O\"> OFF";
 
                     
  }else{
    DayLtSaveSetHTML = "<input type=\"radio\" name=\"DayLtSaveState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"DayLtSaveState\" value=\"O\" checked> OFF";
  }
  



Page =  "<!DOCTYPE html>";
Page += "<html lang=\"en\">";
Page += "<head>";
Page += "<TITLE>Relay Timer Server</TITLE>";
Page += "<meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
Page += "</head>";
Page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
Page += "<style> .button { background-color: #4CAF50; border: on; color: white; padding: 6px 25px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;}</style>";
Page += "<body>";
Page += "<h1>Daily Repeat Timer Relay</h1>";
Page += "<h2>The time is ";
char tempTime[6];
if(Present.Minute<10 && Present.Second<10)
{
  sprintf(tempTime,"0%d:0%d", Present.Minute,Present.Second);
}
else if(Present.Minute<10)
{
  sprintf(tempTime,"0%d:%d", Present.Minute,Present.Second);
}
else if(Present.Second<10)
{
  sprintf(tempTime,"%d:0%d", Present.Minute,Present.Second);
}
else
{
  sprintf(tempTime,"%d:%d", Present.Minute,Present.Second);
}
Page += Present.Hour;
Page += ":";
Page += tempTime;
Page += " and the relay output is ";
if(outputStatus)
{
  Page += "on</h2>";
}
else
{
  Page += "off</h2>";
}
Page += "<h3>Enter your timer on/off values in format (05:45)</h3>";
Page += "<form id=\"Timerform\">";
Page += "<fieldset>";
Page += "<legend>Timer 1</legend>";
Page +=   Timer1SetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Timer 2</legend>";
Page +=   Timer2SetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Timer 3</legend>";
Page +=   Timer3SetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Timer 4</legend>";
Page +=   Timer4SetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Timer 5</legend>";
Page +=   Timer5SetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Day Light Savings</legend>";
Page +=   DayLtSaveSetHTML;
Page += "</fieldset>";
Page += "<form>";
Page += "<fieldset>";
Page += "<legend>Actions</legend>";
Page += "<div>";
Page += "<br>";
Page += "<button id=\"set_button\" class=\"button\">Set</button>";
Page += "</div>";
Page += "</fieldset>";
Page += "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script><script>";
Page += "var Timer1State; var Timer1OnValue; var Timer1OffValue; var Timer2State; var Timer2OnValue; var Timer2OffValue; var Timer3State; var Timer3OnValue; var Timer3OffValue; var Timer4State; var Timer4OnValue; var Timer4OffValue; var Timer5State; var Timer5OnValue; var Timer5OffValue; $('#set_button').click(function(OnEvent){ OnEvent.preventDefault();";
Page += "Timer1State = $('input[name=Timer1State]:checked', '#Timerform').val(); Timer1OnValue = $('#Timer1OnValue').val(); Timer1OffValue = $('#Timer1OffValue').val(); Timer2State = $('input[name=Timer2State]:checked', '#Timerform').val(); Timer2OnValue = $('#Timer2OnValue').val(); Timer2OffValue = $('#Timer2OffValue').val();  Timer3State = $('input[name=Timer3State]:checked', '#Timerform').val(); Timer3OnValue = $('#Timer3OnValue').val(); Timer3OffValue = $('#Timer3OffValue').val(); Timer4State = $('input[name=Timer4State]:checked', '#Timerform').val();  Timer4OnValue = $('#Timer4OnValue').val(); Timer4OffValue = $('#Timer4OffValue').val(); Timer5State = $('input[name=Timer5State]:checked', '#Timerform').val();  Timer5OnValue = $('#Timer5OnValue').val(); Timer5OffValue = $('#Timer5OffValue').val(); DayLtSaveState = $('input[name=DayLtSaveState]:checked', '#Timerform').val();";
Page += "$.get('/set?Timer1State=' + Timer1State + '&Timer1OnValue=' + Timer1OnValue + '&Timer1OffValue=' + Timer1OffValue + '&Timer2State=' + Timer2State + '&Timer2OnValue=' + Timer2OnValue + '&Timer2OffValue=' + Timer2OffValue + '&Timer3State=' + Timer3State + '&Timer3OnValue=' + Timer3OnValue + '&Timer3OffValue=' + Timer3OffValue + '&Timer4State=' + Timer4State + '&Timer4OnValue=' + Timer4OnValue + '&Timer4OffValue=' + Timer4OffValue + '&Timer5State=' + Timer5State + '&Timer5OnValue=' + Timer5OnValue + '&Timer5OffValue=' + Timer5OffValue + '&DayLtSaveState=' + DayLtSaveState, function(TimerState){ console.log(TimerState); }); });";
Page += "</script>";
Page += "</body>";
Page += "</html>";

   server.send ( 200, "text/html", Page);  
}




void handleSet() {

  struct TimerDataStruct WebPortalTimerSet;
  String tempTime;
  String tempHourString;
  String tempMinuteString;
 

  
  if(server.arg("Timer1State") == "D")
  {
    WebPortalTimerSet.TimerOn[1] = true;
  }
  else if(server.arg("Timer1State") == "O")
  {
    WebPortalTimerSet.TimerOn[1] = false;
  }

  if(server.arg("Timer2State") == "D")
  {
    WebPortalTimerSet.TimerOn[2] = true;
  }
  else if(server.arg("Timer2State") == "O")
  {
    WebPortalTimerSet.TimerOn[2] = false;
  }

  if(server.arg("Timer3State") == "D")
  {
    WebPortalTimerSet.TimerOn[3] = true;
  }
  else if(server.arg("Timer3State") == "O")
  {
    WebPortalTimerSet.TimerOn[3] = false;
  }

  if(server.arg("Timer4State") == "D")
  {
    WebPortalTimerSet.TimerOn[4] = true;
  }
  else if(server.arg("Timer4State") == "O")
  {
    WebPortalTimerSet.TimerOn[4] = false;
  }

  if(server.arg("Timer5State") == "D")
  {
    WebPortalTimerSet.TimerOn[5] = true;
  }
  else if(server.arg("Timer5State") == "O")
  {
    WebPortalTimerSet.TimerOn[5] = false;
  }

  if(server.arg("DayLtSaveState") == "D")
  {
    WebPortalTimerSet.TimerOn[6] = true;
  }
  else if(server.arg("DayLtSaveState") == "O")
  {
    WebPortalTimerSet.TimerOn[6] = false;
  }

  if(server.arg("Timer1OnValue").toInt() && server.arg("Timer1OffValue").toInt()) {   
    tempTime = server.arg("Timer1OnValue"); 
    Serial.print("Timer 1 on value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOn and MinuteOn form
    WebPortalTimerSet.HourOn[1] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOn[1] = tempMinuteString.toInt();
	tempTime = server.arg("Timer1OffValue"); 
    Serial.print("Timer 1 off value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOff and MinuteOff form
    WebPortalTimerSet.HourOff[1] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOff[1] = tempMinuteString.toInt();
    }

  if(server.arg("Timer2OnValue").toInt() && server.arg("Timer2OffValue").toInt()) { 
    tempTime = server.arg("Timer2OnValue"); 
    Serial.print("Timer 2 on value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOn and MinuteOn form
    WebPortalTimerSet.HourOn[2] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOn[2] = tempMinuteString.toInt();
	tempTime = server.arg("Timer2OffValue"); 
    Serial.print("Timer 2 off value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOff and MinuteOff form
    WebPortalTimerSet.HourOff[2] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOff[2] = tempMinuteString.toInt();
    }

  if(server.arg("Timer3OnValue").toInt() && server.arg("Timer3OffValue").toInt()) { 
    tempTime = server.arg("Timer3OnValue"); 
    Serial.print("Timer 3 on value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOn and MinuteOn form
    WebPortalTimerSet.HourOn[3] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOn[3] = tempMinuteString.toInt();
	tempTime = server.arg("Timer3OffValue"); 
    Serial.print("Timer 3 off value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOff and MinuteOff form
    WebPortalTimerSet.HourOff[3] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOff[3] = tempMinuteString.toInt();
    }

  if(server.arg("Timer4OnValue").toInt() && server.arg("Timer4OffValue").toInt()) { 
    tempTime = server.arg("Timer4OnValue"); 
    Serial.print("Timer 4 on value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOn and MinuteOn form
    WebPortalTimerSet.HourOn[4] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOn[4] = tempMinuteString.toInt();
	tempTime = server.arg("Timer4OffValue"); 
    Serial.print("Timer 4 off value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOff and MinuteOff form
    WebPortalTimerSet.HourOff[4] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOff[4] = tempMinuteString.toInt();
    } 

    if(server.arg("Timer5OnValue").toInt() && server.arg("Timer5OffValue").toInt()) { 
    tempTime = server.arg("Timer5OnValue"); 
    Serial.print("Timer 5 on value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOn and MinuteOn form
    WebPortalTimerSet.HourOn[5] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOn[5] = tempMinuteString.toInt();
	tempTime = server.arg("Timer5OffValue"); 
    Serial.print("Timer 5 off value Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in HourOff and MinuteOff form
    WebPortalTimerSet.HourOff[5] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalTimerSet.MinuteOff[5] = tempMinuteString.toInt();
    }

  
   EEPROM_writeAnything(100, WebPortalTimerSet);
   ESP.restart(); 
}
