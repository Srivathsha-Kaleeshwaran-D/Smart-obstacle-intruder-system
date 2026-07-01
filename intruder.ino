#define BLYNK_TEMPLATE_ID "TMPL3ukdVJIL_"
#define BLYNK_TEMPLATE_NAME "Intruder Detection"
#define BLYNK_AUTH_TOKEN "CDSVpMgYc5d1tkggAYsThqyN3413twc9"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Dharshu Arju";
char pass[] = "987654321";

#define IR_SENSOR 14

BlynkTimer timer;

bool notificationSent = false;

void checkSensor()
{
  int sensorValue = digitalRead(IR_SENSOR);

  // LOW = Object Detected
  if(sensorValue == LOW)
  {
    Serial.println("Intruder Detected");

    Blynk.virtualWrite(V0, "🚨 Intruder Detected");
    Blynk.virtualWrite(V1, 255);

    if(!notificationSent)
    {
      Blynk.logEvent("intruder", "Intruder Detected!");
      notificationSent = true;
    }
  }

  // HIGH = No Object
  else
  {
    Serial.println("Area Safe");

    Blynk.virtualWrite(V0, "✅ Area Safe");
    Blynk.virtualWrite(V1, 0);

    notificationSent = false;
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(IR_SENSOR, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, checkSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
