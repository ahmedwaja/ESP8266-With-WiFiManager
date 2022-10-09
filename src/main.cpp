#include <Arduino.h>
#include <WiFiManager.h>

#define TRIGGER_PIN 0

short timeout = 120;

WiFiManager wm;

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  Serial.println("\n Starting");
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  wm.setConfigPortalTimeout(timeout);

  if (!wm.autoConnect("AutoConnectAP"))
  {
    Serial.println("Failed to connect");
    ESP.restart();
  }
  else
  {
    Serial.println("connected...yeey :)");
  }
}

void loop()
{
  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    wm.setConfigPortalTimeout(timeout);

    if (!wm.startConfigPortal("OnDemandAP"))
    {
      Serial.println("failed to connect and hit timeout");
      delay(3000);

      ESP.restart();

      delay(5000);
    }
    Serial.println("connected...yeey :)");
  }
}
