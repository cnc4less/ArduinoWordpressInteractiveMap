#include <Event.h>
#include <Timer.h>
#include <Process.h>

Timer t;

//Leds

int ledUS = 2;
int ledBR = 3;
int ledCM = 4;
int ledIT = 5;
int ledCN = 6;
int ledAU = 7;
//Leds

void setup() {
  pinMode(ledUS, OUTPUT);
  pinMode(ledBR, OUTPUT);
  pinMode(ledCM, OUTPUT);
  pinMode(ledIT, OUTPUT);
  pinMode(ledCN, OUTPUT);
  pinMode(ledAU, OUTPUT);
  digitalWrite(ledUS, HIGH);
  delay(150);
  digitalWrite(ledUS, LOW);
  delay(150);
  digitalWrite(ledBR, HIGH);
  delay(150);
  digitalWrite(ledBR, LOW);
  digitalWrite(ledCM, HIGH);
  delay(150);
  digitalWrite(ledCM, LOW);
  digitalWrite(ledIT, HIGH);
  delay(150);
  digitalWrite(ledIT, LOW);
  digitalWrite(ledCN, HIGH);
  delay(150);
  digitalWrite(ledCN, LOW);
  digitalWrite(ledAU, HIGH);
  delay(150);
  digitalWrite(ledAU, LOW);


  // Initialize Bridge
  Bridge.begin();

  // Initialize Serial
  Serial.begin(9600);
  Serial.println("Starting");
  // Wait until a Serial Monitor is connected.
  //while (!Serial);

  // run various example processes
  runCurl();
  t.every(180000, runCurl);

}

void loop() {
  t.update();

}

void runCurl() {
  Process p;
  p.runShellCommand("curl  -H 'authorization: Bearer BEARER_TOKEN  'https://public-api.wordpress.com/rest/v1.1/sites/YOUR_SITE.com/stats/country-views?fields=days'");
  String result  = "";
  bool saving = false;
  while (p.available() > 0) {
    char c = p.read();
    if (c == '[') {
      saving = true;
    }
    if (c == ']') {
      saving = false;
    }
    if (saving) {
      result =  result + c;
    }


  }

  Serial.println(result);
  Serial.flush();
  digitalWrite(ledUS, LOW);
  digitalWrite(ledBR, LOW);
  digitalWrite(ledCM, LOW);
  digitalWrite(ledIT, LOW);
  digitalWrite(ledCN, LOW);
  digitalWrite(ledAU, LOW);


  //Decoding
  if ((result.indexOf("US") != -1) || (result.indexOf("MX") != -1)|| (result.indexOf("CA") != -1)) {

    digitalWrite(ledUS, HIGH);
  }
  if ((result.indexOf("BR") != -1) || (result.indexOf("CR") != -1) ) {

    digitalWrite(ledBR, HIGH);
  }
  if ((result.indexOf("CM") != -1) || (result.indexOf("IN") != -1) ) {

    digitalWrite(ledBR, HIGH);
  }
  if ((result.indexOf("IT") != -1) || (result.indexOf("GB") != -1) || (result.indexOf("PT") != -1) ) {

    digitalWrite(ledIT, HIGH);
  }
  if ((result.indexOf("CN") != -1) || (result.indexOf("PH") != -1) || (result.indexOf("MY") != -1) ) {

    digitalWrite(ledCN, HIGH);
  }
  if ((result.indexOf("AU") != -1)) {

    digitalWrite(ledAU, HIGH);
  }
}


