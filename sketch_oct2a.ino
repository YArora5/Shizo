/*



\============================================================



 SHIZO ESP8266 V2.0



 HOME WIFI + AI READY



\============================================================







BOARD:



NodeMCU 1.0 (ESP-12E Module)







OLED:



SDA -> D2



SCL -> D1



VCC -> 3V3



GND -> GND







BUTTON:



D3 -> BUTTON -> GND







LED:



D4 -> 220R -> LED -> GND







RFID RC522:



SDA/SS -> D8

SCK -> D5

MOSI -> D7

MISO -> D6

RST -> D0

3V3 -> 3V3

GND -> GND

IRQ -> NOT CONNECTED







\============================================================



*/







#include <Wire.h>



#include <Adafruit_GFX.h>



#include <Adafruit_SSD1306.h>







#include <ESP8266WiFi.h>



#include <ESP8266WebServer.h>

#include <SPI.h>

#include <MFRC522.h>











// ============================================================



// HOME WIFI - CHANGE ONLY THESE TWO



// ============================================================







const char* WIFI_SSID = "JioFiber-Eiz0i";



const char* WIFI_PASSWORD = "JKA@176222";











// ============================================================



// OLED



// ============================================================







#define SCREEN_WIDTH 128



#define SCREEN_HEIGHT 64



#define OLED_RESET -1



#define OLED_ADDRESS 0x3C







Adafruit_SSD1306 display(



 SCREEN_WIDTH,



 SCREEN_HEIGHT,



 &Wire,



 OLED_RESET



);











// ============================================================



// PINS



// ============================================================







#define OLED_SDA D2



#define OLED_SCL D1







#define BUTTON_PIN D3



#define LED_PIN D4



#define RFID_SS_PIN D8

#define RFID_RST_PIN D0

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);











// ============================================================



// WEB SERVER



// ============================================================







ESP8266WebServer server(80);











// ============================================================



// STATES



// ============================================================







enum ShizoState {



 NORMAL,



 HAPPY,



 LOVE,



 CURIOUS,



 ANGRY,



 SAD,



 SURPRISE,



 LISTENING,



 THINKING,



 NOTIFICATION,



 SLEEPING



};







ShizoState currentState = NORMAL;
String displayMessage = "";











// ============================================================



// VARIABLES



// ============================================================







bool ledState = false;







unsigned long lastActivity = 0;



unsigned long lastBlink = 0;



unsigned long lastButton = 0;







const unsigned long AUTO_SLEEP_TIME = 30000;



const unsigned long BUTTON_DEBOUNCE = 250;



bool rfidReady = false;

unsigned long lastRFID = 0;

const unsigned long RFID_DEBOUNCE = 1500;







bool previousButton = HIGH;











// ============================================================



// BOOT MESSAGES



// ============================================================







const char* funnyMessages[] = {







 "Checking my brain...",



 "Loading chaos...",



 "Initializing cuteness...",



 "Scanning the universe...",



 "Pretending to be intelligent...",



 "Looking for my brain...",



 "Preparing bad decisions...",



 "Who turned me on?",



 "Please don't unplug me...",



 "Today I choose chaos.",



 "System awake... probably.",



 "My brain is loading..."







};







const int funnyCount =



 sizeof(funnyMessages) / sizeof(funnyMessages[0]);











// ============================================================



// LED



// ============================================================







void ledOn() {







 digitalWrite(LED_PIN, HIGH);



 ledState = true;







}











void ledOff() {







 digitalWrite(LED_PIN, LOW);



 ledState = false;







}











void ledBlink() {







 for (int i = 0; i < 3; i++) {







 digitalWrite(LED_PIN, HIGH);



 delay(120);







 digitalWrite(LED_PIN, LOW);



 delay(120);







 yield();







 }







 ledState = false;







}











// ============================================================



// EYES



// ============================================================







void drawEyes(



 int leftX,



 int rightX,



 int y,



 int eyeWidth,



 int eyeHeight



) {







 display.fillRoundRect(



 leftX,



 y,



 eyeWidth,



 eyeHeight,



 4,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 rightX,



 y,



 eyeWidth,



 eyeHeight,



 4,



 SSD1306_WHITE



 );







}











// ============================================================



// MOUTHS



// ============================================================







void drawMouthHappy() {







 display.fillRoundRect(



 50,



 47,



 28,



 7,



 3,



 SSD1306_WHITE



 );







}











void drawMouthSad() {







 display.drawLine(



 50, 53,



 58, 48,



 SSD1306_WHITE



 );







 display.drawLine(



 58, 48,



 70, 48,



 SSD1306_WHITE



 );







 display.drawLine(



 70, 48,



 78, 53,



 SSD1306_WHITE



 );







}











void drawMouthNormal() {







 display.drawLine(



 52,



 51,



 76,



 51,



 SSD1306_WHITE



 );







}











void drawMouthSurprise() {







 display.fillCircle(



 64,



 50,



 6,



 SSD1306_WHITE



 );







}











void drawMouthAngry() {







 display.drawLine(



 52,



 49,



 76,



 49,



 SSD1306_WHITE



 );







}











// ============================================================



// HEART



// ============================================================







void drawHeart(int x, int y) {







 display.fillCircle(



 x + 5,



 y + 5,



 5,



 SSD1306_WHITE



 );







 display.fillCircle(



 x + 13,



 y + 5,



 5,



 SSD1306_WHITE



 );







 display.fillTriangle(



 x,



 y + 7,



 x + 18,



 y + 7,



 x + 9,



 y + 18,



 SSD1306_WHITE



 );







}











// ============================================================



// NORMAL FACE



// ============================================================







void drawNormalFace() {







 display.clearDisplay();







 drawEyes(



 27,



 77,



 20,



 24,



 20



 );







 drawMouthNormal();







 display.display();







}











// ============================================================



// HAPPY FACE



// ============================================================







void drawHappyFace() {







 display.clearDisplay();







 display.drawLine(



 27, 32,



 39, 23,



 SSD1306_WHITE



 );







 display.drawLine(



 39, 23,



 51, 32,



 SSD1306_WHITE



 );







 display.drawLine(



 77, 32,



 89, 23,



 SSD1306_WHITE



 );







 display.drawLine(



 89, 23,



 101, 32,



 SSD1306_WHITE



 );







 drawMouthHappy();







 display.display();







}











// ============================================================



// LOVE FACE



// ============================================================







void drawLoveFace() {







 display.clearDisplay();







 drawHeart(28, 21);



 drawHeart(78, 21);







 drawMouthHappy();







 display.display();







}











// ============================================================



// CURIOUS FACE



// ============================================================







void drawCuriousFace() {







 display.clearDisplay();







 display.fillRoundRect(



 25, 19,



 28, 24,



 5,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 78, 15,



 28, 28,



 5,



 SSD1306_WHITE



 );







 drawMouthNormal();







 display.display();







}











// ============================================================



// ANGRY FACE



// ============================================================







void drawAngryFace() {







 display.clearDisplay();







 display.drawLine(



 24, 20,



 52, 29,



 SSD1306_WHITE



 );







 display.drawLine(



 76, 29,



 104, 20,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 28, 28,



 22, 13,



 3,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 78, 28,



 22, 13,



 3,



 SSD1306_WHITE



 );







 drawMouthAngry();







 display.display();







}











// ============================================================



// SAD FACE



// ============================================================







void drawSadFace() {







 display.clearDisplay();







 display.fillRoundRect(



 27, 23,



 24, 18,



 4,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 77, 23,



 24, 18,



 4,



 SSD1306_WHITE



 );







 drawMouthSad();







 display.display();







}











// ============================================================



// SURPRISE FACE



// ============================================================







void drawSurpriseFace() {







 display.clearDisplay();







 display.fillCircle(



 39,



 31,



 13,



 SSD1306_WHITE



 );







 display.fillCircle(



 89,



 31,



 13,



 SSD1306_WHITE



 );







 drawMouthSurprise();







 display.display();







}











// ============================================================



// LISTENING FACE



// ============================================================







void drawListeningFace() {







 display.clearDisplay();







 drawEyes(



 25,



 77,



 21,



 25,



 19



 );







 display.drawCircle(



 112,



 31,



 5,



 SSD1306_WHITE



 );







 display.drawCircle(



 112,



 31,



 9,



 SSD1306_WHITE



 );







 drawMouthNormal();







 display.display();







}











// ============================================================



// THINKING FACE



// ============================================================







void drawThinkingFace() {







 display.clearDisplay();







 display.fillRoundRect(



 25, 22,



 24, 18,



 4,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 79, 22,



 24, 18,



 4,



 SSD1306_WHITE



 );







 display.setTextSize(1);



 display.setTextColor(SSD1306_WHITE);







 display.setCursor(108, 10);



 display.print("...");







 drawMouthNormal();







 display.display();







}











// ============================================================



// NOTIFICATION FACE



// ============================================================







void drawNotificationFace() {







 display.clearDisplay();







 drawEyes(



 27,



 77,



 20,



 24,



 20



 );







 display.fillCircle(



 113,



 12,



 7,



 SSD1306_WHITE



 );







 display.setTextColor(SSD1306_BLACK);



 display.setTextSize(1);







 display.setCursor(111, 8);



 display.print("!");







 drawMouthHappy();







 display.display();







}











// ============================================================



// SLEEP FACE



// ============================================================







void drawSleepFace() {







 display.clearDisplay();







 display.drawLine(



 25, 31,



 47, 31,



 SSD1306_WHITE



 );







 display.drawLine(



 81, 31,



 103, 31,



 SSD1306_WHITE



 );







 display.setTextSize(1);



 display.setTextColor(SSD1306_WHITE);







 display.setCursor(94, 8);



 display.print("Z");







 display.setCursor(103, 2);



 display.print("Z");







 display.setCursor(112, 0);



 display.print("Z");







 display.display();







}











// ============================================================



// DRAW CURRENT FACE



// ============================================================







void drawMessage() {

 // Reserve the bottom 8 pixels of the 128x64 OLED for text.
 display.fillRect(
 0,
 56,
 SCREEN_WIDTH,
 8,
 SSD1306_BLACK
 );

 display.setTextSize(1);
 display.setTextColor(SSD1306_WHITE);
 display.setCursor(0, 56);

 String msg = displayMessage;

 if (msg.length() > 21) {
 msg = msg.substring(0, 21);
 }

 display.print(msg);
 display.display();
}


void drawCurrentFace() {







 switch (currentState) {







 case NORMAL:



 drawNormalFace();



 break;







 case HAPPY:



 drawHappyFace();



 break;







 case LOVE:



 drawLoveFace();



 break;







 case CURIOUS:



 drawCuriousFace();



 break;







 case ANGRY:



 drawAngryFace();



 break;







 case SAD:



 drawSadFace();



 break;







 case SURPRISE:



 drawSurpriseFace();



 break;







 case LISTENING:



 drawListeningFace();



 break;







 case THINKING:



 drawThinkingFace();



 break;







 case NOTIFICATION:



 drawNotificationFace();



 break;







 case SLEEPING:



 drawSleepFace();



 break;







 }








  drawMessage();
}











// ============================================================



// SET STATE



// ============================================================







void wakeAnimation() {



 display.clearDisplay();

 display.drawLine(27, 31, 51, 31, SSD1306_WHITE);

 display.drawLine(77, 31, 101, 31, SSD1306_WHITE);

 display.display();

 delay(120);



 for (int h = 4; h <= 20; h += 4) {

 display.clearDisplay();

 int y = 30 - h / 2;

 drawEyes(27, 77, y, 24, h);

 display.display();

 delay(45);

 yield();

 }



 delay(120);

}





void setState(ShizoState newState) {



 if (newState == SLEEPING) {

 currentState = SLEEPING;

 lastActivity = millis();

 ledOff();

 drawSleepFace();

 return;

 }



 // Any interaction while sleeping wakes SHIZO first.

 if (currentState == SLEEPING) {

 wakeAnimation();

 }



 currentState = newState;

 lastActivity = millis();



 switch (currentState) {



 case HAPPY:

 ledOn();

 delay(120);

 ledOff();

 break;



 case LOVE:

 ledOn();

 break;



 case ANGRY:

 ledBlink();

 break;



 case SURPRISE:

 ledBlink();

 break;



 case NOTIFICATION:

 ledBlink();

 break;



 default:

 break;

 }



 drawCurrentFace();

}







// BLINK



// ============================================================







void blinkAnimation() {







 if (currentState == SLEEPING) {



 return;



 }







 display.clearDisplay();







 display.drawLine(



 27, 30,



 51, 30,



 SSD1306_WHITE



 );







 display.drawLine(



 77, 30,



 101, 30,



 SSD1306_WHITE



 );







 display.display();







 delay(80);







 drawCurrentFace();







}











// ============================================================



// STARTUP EYES



// ============================================================







void startupEyes() {







 display.clearDisplay();



 display.display();







 delay(250);







 for (



 int h = 2;



 h <= 20;



 h += 2



 ) {







 display.clearDisplay();







 int y = 30 - h / 2;







 drawEyes(



 27,



 77,



 y,



 24,



 h



 );







 display.display();







 delay(35);







 yield();







 }







 delay(300);







 // Blink 1







 display.clearDisplay();







 display.drawLine(



 27, 30,



 51, 30,



 SSD1306_WHITE



 );







 display.drawLine(



 77, 30,



 101, 30,



 SSD1306_WHITE



 );







 display.display();







 delay(100);







 drawNormalFace();







 delay(250);







 // Blink 2







 display.clearDisplay();







 display.drawLine(



 27, 30,



 51, 30,



 SSD1306_WHITE



 );







 display.drawLine(



 77, 30,



 101, 30,



 SSD1306_WHITE



 );







 display.display();







 delay(100);







 drawNormalFace();







 delay(300);







}











// ============================================================



// LOOK LEFT / RIGHT



// ============================================================







void lookAnimation() {







 // LEFT







 display.clearDisplay();







 display.fillRoundRect(



 20, 20,



 24, 20,



 4,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 70, 20,



 24, 20,



 4,



 SSD1306_WHITE



 );







 display.display();







 delay(400);











 // RIGHT







 display.clearDisplay();







 display.fillRoundRect(



 34, 20,



 24, 20,



 4,



 SSD1306_WHITE



 );







 display.fillRoundRect(



 84, 20,



 24, 20,



 4,



 SSD1306_WHITE



 );







 display.display();







 delay(400);











 // CENTER







 drawNormalFace();







 delay(300);







}











// ============================================================



// CENTER TEXT



// ============================================================







void showCenteredText(



 const String &text,



 int y,



 int size = 1



) {







 display.setTextSize(size);



 display.setTextColor(SSD1306_WHITE);







 int16_t x1;



 int16_t y1;







 uint16_t w;



 uint16_t h;







 display.getTextBounds(



 text,



 0,



 y,



 &x1,



 &y1,



 &w,



 &h



 );







 int x =



 (SCREEN_WIDTH - w) / 2;







 display.setCursor(x, y);







 display.print(text);







}











// ============================================================



// TYPE TEXT



// ============================================================







void typeText(



 const String &text,



 int y,



 int size = 1,



 int speed = 100



) {







 display.clearDisplay();







 display.setTextSize(size);



 display.setTextColor(SSD1306_WHITE);







 int16_t x1;



 int16_t y1;







 uint16_t w;



 uint16_t h;







 display.getTextBounds(



 text,



 0,



 y,



 &x1,



 &y1,



 &w,



 &h



 );







 int x =



 (SCREEN_WIDTH - w) / 2;







 String current = "";







 for (



 unsigned int i = 0;



 i < text.length();



 i++



 ) {







 current += text[i];







 display.clearDisplay();







 display.setCursor(



 x,



 y



 );







 display.print(current);







 display.display();







 delay(speed);







 yield();







 }







}











// ============================================================



// LOADING



// ============================================================







void loadingAnimation() {







 display.clearDisplay();







 showCenteredText(



 "Starting systems",



 15,



 1



 );







 display.display();







 delay(300);







 for (



 int i = 0;



 i < 12;



 i++



 ) {







 display.fillCircle(



 34 + i * 5,



 40,



 2,



 SSD1306_WHITE



 );







 display.display();







 delay(80);







 yield();







 }







 delay(250);







}











// ============================================================



// STARTUP ANIMATION



// ============================================================







void startupAnimation() {







 display.clearDisplay();



 display.display();







 delay(400);







 startupEyes();







 lookAnimation();











 typeText(



 "S",



 25,



 2,



 180



 );







 delay(120);







 typeText(



 "SH",



 25,



 2,



 180



 );







 delay(120);







 typeText(



 "SHI",



 25,



 2,



 180



 );







 delay(120);







 typeText(



 "SHIZ",



 25,



 2,



 180



 );







 delay(120);







 typeText(



 "SHIZO",



 25,



 2,



 180



 );







 delay(350);











 display.clearDisplay();







 showCenteredText(



 "Hi! I'm",



 12,



 1



 );







 showCenteredText(



 "SHIZO!",



 28,



 2



 );







 display.display();







 delay(1200);











 int randomMessage =



 random(



 0,



 funnyCount



 );







 display.clearDisplay();







 showCenteredText(



 funnyMessages[randomMessage],



 25,



 1



 );







 display.display();







 delay(1200);











 loadingAnimation();











 display.clearDisplay();







 showCenteredText(



 "READY!",



 22,



 2



 );







 display.display();







 delay(900);











 currentState = HAPPY;







 drawHappyFace();







 delay(900);











 currentState = NORMAL;







 drawNormalFace();







}











// ============================================================



// WIFI HTML



// ============================================================







const char MAIN_PAGE[] PROGMEM = R"rawliteral(







<!DOCTYPE html>







<html>







<head>







<meta name="viewport"



content="width=device-width, initial-scale=1">







<title>SHIZO Control</title>







<style>







body {



 margin: 0;



 padding: 20px;



 background: #111;



 color: white;



 font-family: Arial;



 text-align: center;



}







h1 {



 font-size: 34px;



 margin-bottom: 5px;



}







p {



 color: #aaa;



}







.grid {



 display: grid;



 grid-template-columns: repeat(2, 1fr);



 gap: 10px;



 max-width: 500px;



 margin: auto;



}







button {



 border: none;



 border-radius: 14px;



 padding: 16px 8px;



 font-size: 15px;



 font-weight: bold;



 background: #222;



 color: white;



}







button:active {



 transform: scale(0.95);



 background: #555;



}







.special {



 background: #333;



}







</style>







</head>







<body>







<h1>🤖 SHIZO</h1>







<p>AI Robot Control Panel</p>







<div class="grid">







<button onclick="cmd('HAPPY')">



😊 HAPPY



</button>







<button onclick="cmd('LOVE')">



❤️ LOVE



</button>







<button onclick="cmd('CURIOUS')">



🤔 CURIOUS



</button>







<button onclick="cmd('NORMAL')">



😐 NORMAL



</button>







<button onclick="cmd('ANGRY')">



😡 ANGRY



</button>







<button onclick="cmd('SAD')">



😢 SAD



</button>







<button onclick="cmd('SURPRISE')">



😲 SURPRISE



</button>







<button onclick="cmd('LISTEN')">



👂 LISTEN



</button>







<button onclick="cmd('THINK')">



🧠 THINK



</button>







<button onclick="cmd('NOTIFICATION')">



🔔 NOTIFY



</button>







<button onclick="cmd('SLEEP')">



😴 SLEEP



</button>







<button onclick="cmd('WAKE')">



☀️ WAKE



</button>







<button class="special"



onclick="cmd('RANDOM')">



🎲 RANDOM



</button>







<button class="special"



onclick="cmd('BLINK')">



👀 BLINK



</button>







<button onclick="cmd('LEDON')">



💡 LED ON



</button>







<button onclick="cmd('LEDOFF')">



⚫ LED OFF



</button>







</div>







<script>







function cmd(c) {







 fetch('/cmd?c=' + c)







 .then(r => r.text())







 .then(data => {







 console.log(data);







 });







}







</script>







</body>







</html>







)rawliteral";











// ============================================================



// WIFI COMMAND



// ============================================================







void handleCommand() {







 if (!server.hasArg("c")) {







 server.send(



 400,



 "text/plain",



 "Missing command"



 );







 return;







 }











 String cmd =



 server.arg("c");







 cmd.toUpperCase();

 if (server.hasArg("m")) {
 displayMessage = server.arg("m");
 } else {
 displayMessage = "";
 }












 Serial.print("COMMAND RECEIVED: ");



 Serial.println(cmd);











 if (cmd == "HAPPY") {







 setState(HAPPY);







 }







 else if (cmd == "LOVE") {







 setState(LOVE);







 }







 else if (cmd == "CURIOUS") {







 setState(CURIOUS);







 }







 else if (cmd == "NORMAL") {







 setState(NORMAL);







 }







 else if (cmd == "ANGRY") {







 setState(ANGRY);







 }







 else if (cmd == "SAD") {







 setState(SAD);







 }







 else if (cmd == "SURPRISE") {







 setState(SURPRISE);







 }







 else if (cmd == "LISTEN") {







 setState(LISTENING);







 }







 else if (cmd == "THINK") {







 setState(THINKING);







 }







 else if (cmd == "NOTIFICATION") {







 setState(NOTIFICATION);







 }







 else if (cmd == "SLEEP") {







 setState(SLEEPING);







 }







 else if (cmd == "WAKE") {



 // WAKE uses the same wake animation when sleeping.

 setState(NORMAL);







 }







 else if (cmd == "RANDOM") {







 int r = random(0, 8);







 switch (r) {







 case 0:



 setState(HAPPY);



 break;







 case 1:



 setState(LOVE);



 break;







 case 2:



 setState(CURIOUS);



 break;







 case 3:



 setState(SURPRISE);



 break;







 case 4:



 setState(THINKING);



 break;







 case 5:



 setState(NORMAL);



 break;







 case 6:



 setState(LISTENING);



 break;







 case 7:



 setState(NOTIFICATION);



 break;







 }







 }







 else if (cmd == "LEDON") {







 ledOn();







 }







 else if (cmd == "LEDOFF") {







 ledOff();







 }







 else if (cmd == "BLINK") {







 blinkAnimation();







 }







 else {







 server.send(



 400,



 "text/plain",



 "Unknown command"



 );







 return;







 }











 lastActivity = millis();











 server.send(



 200,



 "text/plain",



 "SHIZO: " + cmd



 );







}











// ============================================================



// ROOT PAGE



// ============================================================







void handleRoot() {







 server.send_P(



 200,



 "text/html",



 MAIN_PAGE



 );







}











// ============================================================



// STATUS



// ============================================================







void handleStatus() {







 String stateName;







 switch (currentState) {







 case NORMAL:



 stateName = "NORMAL";



 break;







 case HAPPY:



 stateName = "HAPPY";



 break;







 case LOVE:



 stateName = "LOVE";



 break;







 case CURIOUS:



 stateName = "CURIOUS";



 break;







 case ANGRY:



 stateName = "ANGRY";



 break;







 case SAD:



 stateName = "SAD";



 break;







 case SURPRISE:



 stateName = "SURPRISE";



 break;







 case LISTENING:



 stateName = "LISTENING";



 break;







 case THINKING:



 stateName = "THINKING";



 break;







 case NOTIFICATION:



 stateName = "NOTIFICATION";



 break;







 case SLEEPING:



 stateName = "SLEEPING";



 break;







 }











 server.send(



 200,



 "text/plain",



 "SHIZO STATE: " + stateName



 );







}











// ============================================================



// BUTTON



// ============================================================







void checkButton() {







 bool buttonState =



 digitalRead(BUTTON_PIN);











 if (



 buttonState == LOW &&



 previousButton == HIGH &&



 millis() - lastButton >



 BUTTON_DEBOUNCE



 ) {







 lastButton = millis();











 if (currentState == SLEEPING) {







 setState(NORMAL);







 }







 else {







 setState(SURPRISE);







 delay(600);







 setState(NORMAL);







 }







 }











 previousButton =



 buttonState;







}











// ============================================================



// AUTO SLEEP



// ============================================================







void checkAutoSleep() {



 if (

 currentState != SLEEPING &&

 millis() - lastActivity >= AUTO_SLEEP_TIME

 ) {



 setState(SLEEPING);

 }

}







// AUTO BLINK



// ============================================================







void checkBlink() {







 if (



 currentState == SLEEPING



 ) {







 return;







 }











 if (



 millis() - lastBlink > 6000



 ) {







 lastBlink = millis();







 blinkAnimation();







 }







}











// ============================================================



// SETUP



// ============================================================







// ============================================================

// RFID

// ============================================================



void showRFIDReaction() {

 lastActivity = millis();



 // Wake SHIZO first if it is sleeping.

 if (currentState == SLEEPING) {

 wakeAnimation();

 }



 // 9 different RFID reactions.

 // The same reaction will not repeat twice in a row.

 static int lastReaction = -1;

 int reaction;



 do {

 reaction = random(0, 9);

 } while (reaction == lastReaction);



 lastReaction = reaction;



 switch (reaction) {

 case 0:

 Serial.println("RFID REACTION: HAPPY");

 setState(HAPPY);

 delay(1000);

 break;



 case 1:

 Serial.println("RFID REACTION: LOVE");

 setState(LOVE);

 delay(1000);

 break;



 case 2:

 Serial.println("RFID REACTION: CURIOUS");

 setState(CURIOUS);

 delay(1000);

 break;



 case 3:

 Serial.println("RFID REACTION: ANGRY");

 setState(ANGRY);

 delay(1000);

 break;



 case 4:

 Serial.println("RFID REACTION: SAD");

 setState(SAD);

 delay(1000);

 break;



 case 5:

 Serial.println("RFID REACTION: SURPRISE");

 setState(SURPRISE);

 delay(1000);

 break;



 case 6:

 Serial.println("RFID REACTION: LISTENING");

 setState(LISTENING);

 delay(1000);

 break;



 case 7:

 Serial.println("RFID REACTION: THINKING");

 setState(THINKING);

 delay(1000);

 break;



 case 8:

 Serial.println("RFID REACTION: NOTIFICATION");

 setState(NOTIFICATION);

 delay(1000);

 break;

 }



 setState(NORMAL);

 lastActivity = millis();

}



void checkRFID() {

 if (!rfidReady) return;

 if (millis() - lastRFID < RFID_DEBOUNCE) return;

 if (!rfid.PICC_IsNewCardPresent()) return;

 if (!rfid.PICC_ReadCardSerial()) return;



 lastRFID = millis();

 lastActivity = millis();



 Serial.print("RFID DETECTED - UID: ");

 for (byte i = 0; i < rfid.uid.size; i++) {

 if (rfid.uid.uidByte[i] < 0x10) Serial.print("0");

 Serial.print(rfid.uid.uidByte[i], HEX);

 if (i < rfid.uid.size - 1) Serial.print(":");

 }

 Serial.println();



 showRFIDReaction();



 rfid.PICC_HaltA();

 rfid.PCD_StopCrypto1();

}



void setup() {







 Serial.begin(115200);







 delay(200);











 // ----------------------------------------------------------



 // PINS



 // ----------------------------------------------------------







 pinMode(



 BUTTON_PIN,



 INPUT_PULLUP



 );







 pinMode(



 LED_PIN,



 OUTPUT



 );







 digitalWrite(



 LED_PIN,



 LOW



 );











 // ----------------------------------------------------------



 // OLED



 // ----------------------------------------------------------







 Wire.begin(



 OLED_SDA,



 OLED_SCL



 );











 if (



 !display.begin(



 SSD1306_SWITCHCAPVCC,



 OLED_ADDRESS



 )



 ) {







 Serial.println(



 "OLED ERROR!"



 );







 while (true) {







 delay(1000);







 }







 }











 // ----------------------------------------------------------



 // RANDOM



 // ----------------------------------------------------------







 randomSeed(



 ESP.getChipId() ^



 micros()



 );











 // ----------------------------------------------------------



 // STARTUP



 // ----------------------------------------------------------







 // ----------------------------------------------------------

 // RFID

 // ----------------------------------------------------------



 SPI.begin();

 rfid.PCD_Init();

 delay(50);

 rfidReady = true;

 Serial.println("RFID RC522 READY!");



 startupAnimation();











 // ----------------------------------------------------------



 // HOME WIFI



 // ----------------------------------------------------------







 Serial.println();



 Serial.println(



 "=============================="



 );







 Serial.println(



 " SHIZO V2.1"



 );







 Serial.println(



 "=============================="



 );







 Serial.println();







 Serial.print(



 "Connecting to WiFi: "



 );







 Serial.println(



 WIFI_SSID



 );











 WiFi.mode(WIFI_STA);







 WiFi.begin(



 WIFI_SSID,



 WIFI_PASSWORD



 );











 int attempts = 0;







 while (



 WiFi.status() != WL_CONNECTED &&



 attempts < 40



 ) {







 delay(500);







 Serial.print(".");







 attempts++;







 yield();







 }











 Serial.println();











 if (



 WiFi.status() == WL_CONNECTED



 ) {







 Serial.println(



 "WiFi CONNECTED!"



 );







 Serial.print(



 "IP Address: "



 );







 Serial.println(



 WiFi.localIP()



 );







 Serial.print(



 "Signal: "



 );







 Serial.print(



 WiFi.RSSI()



 );







 Serial.println(



 " dBm"



 );







 }







 else {







 Serial.println(



 "WiFi CONNECTION FAILED!"



 );







 Serial.println(



 "Check SSID/password."



 );







 }











 // ----------------------------------------------------------



 // WEB SERVER



 // ----------------------------------------------------------







 server.on(



 "/",



 HTTP_GET,



 handleRoot



 );







 server.on(



 "/cmd",



 HTTP_GET,



 handleCommand



 );







 server.on(



 "/status",



 HTTP_GET,



 handleStatus



 );











 server.begin();











 Serial.println(



 "Web server started!"



 );











 if (



 WiFi.status() == WL_CONNECTED



 ) {







 Serial.print(



 "Open: http://"



 );







 Serial.println(



 WiFi.localIP()



 );







 }











 // ----------------------------------------------------------



 // INITIAL STATE



 // ----------------------------------------------------------







 currentState = NORMAL;







 drawNormalFace();







 lastActivity = millis();







 lastBlink = millis();







}











// ============================================================



// LOOP



// ============================================================







void loop() {







 // WiFi



 server.handleClient();







 // Button



 checkButton();







 // RFID

 checkRFID();



 // Auto sleep



 checkAutoSleep();







 // Auto blink



 checkBlink();







 // Keep ESP healthy



 yield();







}