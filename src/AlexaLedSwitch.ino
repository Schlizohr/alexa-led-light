#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include <fauxmoESP.h>

fauxmoESP fauxmo;
#define LED 0

bool on = false;

void setup() {
    digitalWrite(LED, LOW);
    WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP

    Serial.begin(115200);

    WiFiManager wm;

    bool res;
    res = wm.autoConnect();  // auto generated AP name from chipid

    if (!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } else {
        // if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
    }
    fauxmo.addDevice("Orchidee");
    fauxmo.setPort(80);  // required for gen3 devices
    fauxmo.enable(true);

    fauxmo.onSetState([](unsigned char device_id, const char* device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        digitalWrite(LED, state ? HIGH : LOW);
    });
    pinMode(LED, OUTPUT);
}

void loop() {
    fauxmo.handle();
}