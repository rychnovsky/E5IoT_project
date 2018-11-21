#include <google-maps-device-locator.h>

GoogleMapsDeviceLocator locator;


void setup() {
    Serial.begin(9600);

    Serial.println("Photon starting....");
    
    Particle.subscribe("distance_button_result_ack", onAckReceived, MY_DEVICES);
    
    
    // Scan for visible networks and publish to the cloud every 30 seconds
    // Pass the returned location to be handled by the locationCallback() method
    locator.withSubscribe(onLocationReceived).withLocatePeriodic(20);
}

void loop() {
    // todo call this only on button press
    locator.loop();
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
}
