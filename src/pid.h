#ifndef PID_H
#define PID_H

class PID {
 public:
  explicit PID(double Kp = 0, double Ki = 0, double Kd = 0);
  void Set(double Kp, double Ki, double Kd);
  void UpdateError(double cte);
  double TotalError() const;

 private:
  double Kp_;
  double Ki_;
  double Kd_;
  double p_error_;
  double i_error_;
  double d_error_;
};

#endif  // PID_H