#include "pid.h"

PID::PID(double Kp, double Ki, double Kd)
    : Kp_{Kp},
      Ki_{Ki},
      Kd_{Kd},
      p_error_{0},
      i_error_{0},
      d_error_{0},
      squared_error_{0},
      count_{0} {}

void PID::Reset(double Kp, double Ki, double Kd) {
  Kp_ = Kp;
  Ki_ = Ki;
  Kd_ = Kd;
  p_error_ = 0;
  i_error_ = 0;
  d_error_ = 0;
  count_ = 0;
  squared_error_ = 0;
}

void PID::UpdateError(double cte) {
  d_error_ = cte - p_error_;
  p_error_ = cte;
  i_error_ += cte;
  squared_error_ += cte * cte;
  ++count_;
}

double PID::TotalError() const {
  return Kp_ * p_error_ + Ki_ * i_error_ + Kd_ * d_error_;
}

double PID::MeanSquaredError() const { return squared_error_ / count_; }
