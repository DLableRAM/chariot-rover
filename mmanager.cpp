#include "defs.hpp"

void motorcontrol::move(int f, int b) {
  analogWrite(motor_F, f);
  analogWrite(motor_B, b);
}
