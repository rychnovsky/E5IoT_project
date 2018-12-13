# E5IoT_project - Distance Button

The goal of this project is to create an IoT device connecting two users by sharing their location and showing the walking time between them.

[Documentation of teh project](distance-button.pdf)

![alt Distance Button](/final_product.jpg)

## Project Description

The core part of our project is a pair of devices (stations) connected to the Internet. Each of the stations will belong to one of the users.
These two stations are located on different places (for example one at home, second at school). One station is called client station and the other can be called master station. The client station contains one Photon, a LED and a simple button. The master station contains another Photon and a numeric display.
When the button is pressed, the Client Photon fetches its location from Google Maps Geo-Location API and publishes this event into Particle Cloud. The Master Photon is subscribed to this event and receives this location. When this action is triggered, it fetches its own location also from Google Geo-Location API. These two locations are used to calculate a distance between these two places and time necessary to walk this distance. For the most accurate calculation of walking time the Google API is used again. This walking time will be displayed on the master station.

## Hardware parts

- Particle Photon
- Button
- Seven Segment Display
- LEDs

## Services integration

- Particle Cloud Events
- Google Maps Geolocation API
- Google Maps Distance Matrix API
