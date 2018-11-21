#include <google-maps-device-locator.h>

GoogleMapsDeviceLocator locator;

int ledPin = D1;

int internalLedPin = D7;

int buttonPin = D0;

void setup() {
    Serial.begin(9600);

    Serial.println("Photon starting....");
    
     // sets pin as input
    pinMode( buttonPin , INPUT_PULLUP);

    // sets pins as output
    pinMode(ledPin, OUTPUT );
    pinMode(internalLedPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    digitalWrite(internalLedPin, LOW);
    
    Particle.subscribe("distance_button_result_ack", onAckReceived, MY_DEVICES);
    
    
    // Scan for visible networks and publish to the cloud every 30 seconds
    // Pass the returned location to be handled by the locationCallback() method
    // locator.withSubscribe(onLocationReceived).withLocatePeriodic(60);
    locator.withSubscribe(onLocationReceived).withLocateOnce();
}

void loop() {
    // locator.loop();

    // todo call this only on button press
    int buttonState = digitalRead( buttonPin );

    if ( buttonState == LOW )
    {
        Serial.println("Button pressed!");
        digitalWrite( ledPin, HIGH);
        delay(1500); // to prevent multiple 

        locator.publishLocation();
    } else {
        digitalWrite( ledPin, LOW);
    }
    
}

/**
 * Handle location result
 * @param float lat
 * @param float lon
 * @param float accuracy
 */
void onLocationReceived(float lat, float lon, float accuracy) {
    // Handle the returned location data for the device. This method is passed three arguments:
    // - Latitude
    // - Longitude
    // - Accuracy of estimated location (in meters)
    
    Serial.println("New location update received!");
    Serial.printlnf("Latitude: %f", lat);
    Serial.printlnf("Longitude: %f", lon);
    Serial.printlnf("Accuracy: %f", accuracy);
    
    // publish the location
    String sharable =  String::format("%f, %f", lat, lon);
    Particle.publish("distance_button_location_share", sharable, PUBLIC);

}

/**
 * Handle final result
 */
void onAckReceived(const char *event, const char *data) {
    Serial.println("Process finished, OK!");
    // TODO: indicate the result to user - eg blink a LED
    digitalWrite(internalLedPin, HIGH);
    delay(2000);
    digitalWrite(internalLedPin, LOW);

}

