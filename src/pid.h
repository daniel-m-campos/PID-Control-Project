#ifndef PID_H
#define PID_H

#include <cstddef>

class PID {
 public:
  explicit PID(double Kp = 0, double Ki = 0, double Kd = 0);
  void Reset(double Kp, double Ki, double Kd);
  void UpdateError(double cte);
  double TotalError() const;
  double MeanSquaredError() const;

 private:
  double Kp_;
  double Ki_;
  double Kd_;
  double p_error_;
  double i_error_;
  double d_error_;
  double squared_error_;
  size_t count_;
};

#endif  // PID_H