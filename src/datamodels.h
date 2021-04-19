#ifndef DATAMODELS_H
#define DATAMODELS_H

#include <ostream>

struct SensorData {
  double cross_track_error;
  double speed;  // miles per hour
  double steering_angle;
  double throttle;
  bool operator==(const SensorData& rhs) const {
    return cross_track_error == rhs.cross_track_error && speed == rhs.speed &&
           steering_angle == rhs.steering_angle && throttle == rhs.throttle;
  }
  bool operator!=(const SensorData& rhs) const { return !(rhs == *this); }
  friend std::ostream& operator<<(std::ostream& os, const SensorData& data) {
    os << "cross_track_error: " << data.cross_track_error
       << " speed: " << data.speed << " steering_angle: " << data.steering_angle
       << " throttle: " << data.throttle;
    return os;
  }
};

#endif  // DATAMODELS_H
