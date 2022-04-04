#include "xy_drive_algorithm.hpp"
#include <Arduino.h>

XYDriveAlgorithm::Output XYDriveAlgorithm::translate(int speed, int rotation) {
  int drive_power = map(constrain(sqrt(pow(rotation, 2) + pow(speed, 2)), 0, 1000), 0, 1000, 0, 255);

  double angle = atan2(speed, rotation);
  int direction = (speed >= 0 ? 1 : -1);
  int left_wheels_speed{drive_power * direction};
  int right_wheels_speed{drive_power * direction};

  if (angle > M_PI / 2.) {
    // II ćwiartka
    left_wheels_speed *= cos((angle - (M_PI / 2.)) * 2.);  // OK
  } else if (angle >= 0) {
    // I ćwiartka
    right_wheels_speed *= -cos(angle * 2.);  // OK
  } else if (angle > -(M_PI / 2.)) {
    // IV ćwiartka
    left_wheels_speed *= -cos(angle * 2.);  // OK
  } else {
    // III ćwiartka
    right_wheels_speed *= cos((angle + (M_PI / 2.)) * 2.);  // OK
  }

  return {left_wheels_speed, right_wheels_speed};
}