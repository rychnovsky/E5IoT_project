// This #include statement was automatically added by the Particle IDE.
#include <google-maps-device-locator.h>


GoogleMapsDeviceLocator locator;

float remoteLat;
float remoteLon;

void setup() {
    Serial.begin(9600);

    Serial.println("Photon starting....");

    // setup display pins
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
    
    resetDisplay();

    // subscribe to location from remote photon
    Particle.subscribe("distance_button_location_share", onRemoteLocation);

    // subscribe to distance calculation
    Particle.subscribe("hook-response/calculate_distance", onCalculationResult, MY_DEVICES);

}

void loop() {
    // do nothing just wait for remote impuls
}

/**
 * Handle calculation result
 * @param const char* - result of calculation in seconds
 */
void onRemoteLocation(const char *event, const char *data) {
    // save location of remote photon

    // TODO get actual values from data
    
    
    shownumber(0);
    String location = String(data);
    
    int index = location.indexOf(',');
        

    remoteLat = location.substring(0, index).toFloat();
    
    remoteLon = location.substring(index+1, location.length()).toFloat();
    

    
    String somestring = String::format(
        "{ \"ORIGIN\": \"%f, %f\", \"DESTINATION\": \"%f, %f\" }",
        56.129282, 10.187276,
        remoteLat, remoteLon
    );
    Serial.println(somestring);
    
    Particle.publish("calculate_distance", somestring, PRIVATE, WITH_ACK);
    Particle.publish("distance_button_result_ack", NULL, PUBLIC, WITH_ACK);


    // get my location
    //locator.withSubscribe(onLocationReceived).withLocateOnce();
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

    // calculate the distance
     String data = String::format(
        "{ \"ORIGIN\": \"%f, %f\", \"DESTINATION\": \"%f, %f\" }",
        lat, lon,
        remoteLat, remoteLon
    );
    Particle.publish("calculate_distance", data, PRIVATE);

}


/**
 * Handle calculation result
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
    shownumber(result);

    // publish acknowledgement
    Particle.publish("distance_button_result_ack");
}


void shownumber(int number) {
    resetDisplay();
    if(number < 100) {
        int first = number % 10;
        int second = number / 10;
        firstDigit(first);
        secondDigit(second);
    } else {
       showError();
    }
}


void showError() {
    // show minus minus
    digitalWrite(D7,HIGH);
    digitalWrite(D3,HIGH);
}

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
