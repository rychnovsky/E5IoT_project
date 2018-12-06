#include <google-maps-device-locator.h>

GoogleMapsDeviceLocator locator;

// location vars from the Client Photon
float remoteLat;
float remoteLon;

void setup() {
    Serial.begin(9600);

    Serial.println("Photon starting....");

    // setup display pins
    setupDisplay();

    // boot up sequence
    // indicate starting and that there are no errors in the display
    // should be changed in production mode to lower energy consumtion
    for (size_t i = 0; i < 4; i++) {
        showError();
        delay(250);
        showNumber(88);
        delay(250);
    }
    resetDisplay();

    // subscribe to location from Client Photon
    Particle.subscribe("distance_button_location_share", onRemoteLocation, ALL_DEVICES);

    // subscribe to distance calculation
    Particle.subscribe("hook-response/calculate_distance", onCalculationResult, MY_DEVICES);

    // setup location fetching
    // pass the returned location to be handled by the onLocationReceived() method
    locator.withSubscribe(onLocationReceived).withLocateOnce();
}

void loop() {
    // do nothing just wait for remote impuls
    // delay 1sec to prevent WiFi issues
    delay(1000);
}

/**
 * Handle Client Photon sharing
 * Get location of this Photon
 */
void onRemoteLocation(const char *event, const char *data) {

    // indicate location receiving
    showError();

    // save location of remote photon
    // parse two floats separated by comma
    String location = String(data);
    int index = location.indexOf(',');
    remoteLat = location.substring(0, index).toFloat();
    remoteLon = location.substring(index+1, location.length()).toFloat();

    // example of remote location
    // remoteLat = 56.129282;
    // remoteLon = 10.187276;

    // get location of this Photon
    locator.publishLocation();
}

/**
 * Handle location result
 * @param float lat Latitude
 * @param float lon Longitude
 * @param float accuracy Accuracy of estimated location (in meters)
 */
void onLocationReceived(float lat, float lon, float accuracy) {

    // indicate location receiving
    resetDisplay();

    Serial.println("New location update received!");
    Serial.printlnf("Latitude: %f", lat);
    Serial.printlnf("Longitude: %f", lon);
    Serial.printlnf("Accuracy: %f", accuracy);

    // calculate the distance via webhook to Google API
    String data = String::format(
        "{ \"ORIGIN\": \"%f, %f\", \"DESTINATION\": \"%f, %f\" }",
        lat, lon,
        remoteLat, remoteLon
    );
    Particle.publish("calculate_distance", data, PRIVATE, WITH_ACK);

}


/**
 * Handle calculation result
 * Data received by webhook are pre-parsed by Response Template in Particle Console
 * @param const char* - result of calculation in seconds
 */
void onCalculationResult(const char *event, const char *data) {
    // Handle the integration response
    Serial.println("Calculation received");
    int result = atoi( data );
    // change to minutes and round correctly
    if((result%60) != 0) {
        result = (int)(result/60) + 1;
    } else {
        result = (int)(result/60);
    }

    // show on display
    Serial.printlnf("Distance: %d", result );
    showNumber(result);

    // publish acknowledgement to Client Photon
    Particle.publish("distance_button_result_ack", "", PUBLIC, WITH_ACK);

    // show the result for a while and finish
    delay(10000);
    resetDisplay();
}

// DISPLAY FUNCTIONS

/**
* Setup display pins
*/
void setupDisplay() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

/**
* Show number on the display
* If the number has more digits than display, show error
* @param int number - Number to be shown
*/
void showNumber(int number) {
    resetDisplay();
    if(number >= 0 && number < 100) {
        int first = number % 10;
        int second = number / 10;
        firstDigit(first);
        secondDigit(second);
    } else {
       showError();
    }
}

/**
* Show minus minus
*/
void showError() {
    resetDisplay();
    digitalWrite(D7,HIGH);
    digitalWrite(D3,HIGH);
}

/**
* Switch off display
*/
void resetDisplay(){
    digitalWrite(D0,LOW);
    digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    digitalWrite(D3,LOW);
    digitalWrite(D4,LOW);
    digitalWrite(D5,LOW);
    digitalWrite(D6,LOW);
    digitalWrite(D7,LOW);
    digitalWrite(A0,LOW);
    digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(A3,LOW);
    digitalWrite(A4,LOW);
    digitalWrite(A5,LOW);
}

/**
* Mapping of integer to first segment display
*/
void firstDigit(int number) {
    switch(number) {
        case 0:
          digitalWrite(A5,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A2,HIGH);
          digitalWrite(A1,HIGH);
          digitalWrite(A0,HIGH);
          break;
        case 1:
          digitalWrite(A3,HIGH);
          digitalWrite(A2,HIGH);
          break;
        case 2:
          digitalWrite(D3,HIGH);
          digitalWrite(A1,HIGH);
          digitalWrite(A2,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A5,HIGH);
          break;
        case 3:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A1,HIGH);
          digitalWrite(A2,HIGH);
          digitalWrite(A4,HIGH);
          break;
        case 4:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A2,HIGH);
          digitalWrite(A0,HIGH);
          break;
        case 5:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A1,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A0,HIGH);
          break;
        case 6:
          digitalWrite(D3,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A1,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A0,HIGH);
          digitalWrite(A5,HIGH);
          break;
        case 7:
          digitalWrite(A3,HIGH);
          digitalWrite(A2,HIGH);
          digitalWrite(A1,HIGH);
          break;
        case 8:
          digitalWrite(D3,HIGH);
          digitalWrite(A0,HIGH);
          digitalWrite(A1,HIGH);
          digitalWrite(A2,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A4,HIGH);
          digitalWrite(A5,HIGH);
          break;
        case 9:
          digitalWrite(D3,HIGH);
          digitalWrite(A0,HIGH);
          digitalWrite(A1,HIGH);
          digitalWrite(A2,HIGH);
          digitalWrite(A3,HIGH);
          digitalWrite(A4,HIGH);
          break;
    }
}

/**
* Mapping of integer to second segment display
*/
void secondDigit(int number) {
    switch(number) {
        case 0:
            digitalWrite(D0,HIGH);
            digitalWrite(D1,HIGH);
            digitalWrite(D2,HIGH);
            digitalWrite(D4,HIGH);
            digitalWrite(D5,HIGH);
            digitalWrite(D6,HIGH);
            break;
        case 1:
            digitalWrite(D2,HIGH);
            digitalWrite(D4,HIGH);
            break;
        case 2:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(D1,HIGH);//D
            digitalWrite(D0,HIGH);//E
            break;
        case 3:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D2,HIGH);//C
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(D1,HIGH);//D
            break;
        case 4:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D2,HIGH);//C
            digitalWrite(D4,HIGH);//B
            digitalWrite(D6,HIGH);//F
            break;
        case 5:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D2,HIGH);//C
            digitalWrite(D5,HIGH);//A
            digitalWrite(D1,HIGH);//D
            digitalWrite(D6,HIGH);//F
            break;
        case 6:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D2,HIGH);//C
            digitalWrite(D5,HIGH);//A
            digitalWrite(D1,HIGH);//D
            digitalWrite(D6,HIGH);//F
            digitalWrite(D0,HIGH);//E
            break;
        case 7:
            digitalWrite(D2,HIGH);//C
            digitalWrite(D4,HIGH);//B
            digitalWrite(D5,HIGH);//A
            break;
        case 8:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D6,HIGH);//F
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(D2,HIGH);//C
            digitalWrite(D1,HIGH);//D
            digitalWrite(D0,HIGH);//E
            break;
        case 9:
            digitalWrite(D7,HIGH);//G
            digitalWrite(D6,HIGH);//F
            digitalWrite(D5,HIGH);//A
            digitalWrite(D4,HIGH);//B
            digitalWrite(D2,HIGH);//C
            digitalWrite(D1,HIGH);//D
            break;
    }
}
