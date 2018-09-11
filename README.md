# E5IoT_project - Distance Button

The goal of this project is to create a device connecting two users by sharing their location and the walking distance between them.

## Project usecases

1. There are two friends living in the same town who visit each other very often. The one who is leaving the house would like to inform tje other friend, that he is comming and how long it will take.
2. Children can easily inform their parents that they are leaving school and if they don't come home in expected time, parents know, that there is a problem.
3. A couple living far away from each other can let each other know, how long it would take to walk to the partner's place.
   If we use photon with cellular connection, we will be able to add continuous location sharing feature.

## Project description

There are two stations located on diferent places (ex. one at home, second at school), each one consists of one Photon, one button, and a small display. When the button is pressed, the photon fetches its location from GoogleMap API and publishes this event into Particle cloud. The second photon is subscribed to this event and gets the location of the second photon. In the same time it fetches its own location also from GoogleMap API. These two locations are used to calculate a distance between these two places and time necessery to walk this distance. The receiving photon will display this walking time, which will be counting down to zero.

## Hardware parts per one station

- Particle Photon
- Button
- Display

## Services integration

- Google map API

## Idea pool

- send a push notification to user's mobile phone, when someone is sharing location with him
- continuous location sharing - another type of Photon is required
