#include <google-maps-device-locator.h>

GoogleMapsDeviceLocator locator;

int ledPin = D1;

int internalLedPin = D7;

int buttonPin = D0;

void setup() {
    Serial.begin(9600);

    Serial.println("Photon starting....");

     // set pins as input
    pinMode( buttonPin , INPUT_PULLUP);

    // set pins as output
    pinMode(ledPin, OUTPUT );
    pinMode(internalLedPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    digitalWrite(internalLedPin, LOW);

    Particle.subscribe("distance_button_result_ack", onAckReceived, ALL_DEVICES);

    // Scan for visible networks
    // Pass the returned location to be handled by the onLocationReceived() method
    // Use this code to publish the location every X seconds instead of waiting for the button
    // locator.withSubscribe(onLocationReceived).withLocatePeriodic(60);
    // then in the loop use this:
    // locator.loop();
    locator.withSubscribe(onLocationReceived).withLocateOnce();
}

void loop() {

    // hanle button press
    int buttonState = digitalRead( buttonPin );

    if ( buttonState == LOW )
    {
        Serial.println("Button pressed!");
        Serial.println("Publishing location to the cloud");
        digitalWrite( ledPin, HIGH);
        delay(1500); // to prevent multiple presses
        locator.publishLocation();
    } else {
        digitalWrite( ledPin, LOW);
    }

}

/**
 * Handle location result
 * @param float lat Latitude
 * @param float lon Longitude
 * @param float accuracy Longitude
 */
void onLocationReceived(float lat, float lon, float accuracy) {

    Serial.println("New location update received!");
    Serial.printlnf("Latitude: %f", lat);
    Serial.printlnf("Longitude: %f", lon);
    Serial.printlnf("Accuracy: %f", accuracy);

    // TODO: Remove these lines in production mode
    // change location to show different results than 0 mins
    lat += 0.02;
    lon += 0.03;

    // publish the location to the Master Photon
    String sharable =  String::format("%f, %f", lat, lon);
    Particle.publish("distance_button_location_share", sharable, PUBLIC, WITH_ACK);

    // light the LED to show, that the location was shared
    digitalWrite( ledPin, HIGH);
    delay(1000);
}

/**
 * Handle final result
 * Blink the integrated LED to show that everything went fine
 */
void onAckReceived(const char *event, const char *data) {
    Serial.println("Process finished, OK!");
    digitalWrite(internalLedPin, HIGH);
    delay(2000);
    digitalWrite(internalLedPin, LOW);

}
