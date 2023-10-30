#include <Romi32U4.h>
#include "chassis.h"

float RomiChassis::SpeedLeft(void)
{
    // !!! ATTENTION !!!
    // Assignment 1
    float delta_count_left = count_left - prev_count_left;
    return (C_wheel*delta_count_left)/(N_wheel*interval); //[mm/s]

}

float RomiChassis::SpeedRight(void)
{
    // !!! ATTENTION !!!
    // Assignment 1

    
    float delta_count_right = count_right - prev_count_right;

    return (C_wheel*delta_count_right)/(N_wheel*interval); //[mm/s]
}

void RomiChassis::UpdateEffortDriveWheels(int left, int right)
{ 
    motors.setEfforts(left,right);
}

void RomiChassis::UpdateEffortDriveWheelsPI(int target_speed_left, int target_speed_right)
{
  // !!! ATTENTION !!!
  // Assignment 2
  
    {

      E_left = E_left + (target_speed_left-SpeedLeft()); //accumulated errors
      E_right = E_right + (target_speed_right-SpeedRight()) ;
      u_left = Kp*(target_speed_left-SpeedLeft())+ Ki*E_left;
      u_right = Kp*(target_speed_right-SpeedRight())+Ki*E_right;
      motors.setEfforts(u_left,u_right);
    }

    // curLeftError = target_left-count_left;
    // curRightError = target_right-count_right;
    // float u_left = Kp*(curLeftError) + Ki*(target_speed_left-SpeedLeft());
    // float u_right = Kp*(curRightError) + Ki*(target_speed_right-SpeedRight());
    // motors.setEfforts(u_left,u_right);
    // curLeftEffort = u_left;
    // curRightEffort = u_right;
  
}

void RomiChassis::SerialPlotter(float a, float b, float c, float d, float e, float f, float g)
{
    // !!! ATTENTION !!!
    // USE this function for assignment 3!
    Serial.print(a);
    Serial.print(' ');
    Serial.print(b);
    Serial.print(' ');
    Serial.print(c);
    Serial.print(' ');
    Serial.print(d);
    Serial.print(' ');
    Serial.print(e);
    Serial.print(' ');
    Serial.print(f);
    Serial.print(' ');
    Serial.print(g);
    Serial.println();
    delay(5);
}

void RomiChassis::MotorControl(void)
{
  uint32_t now = millis();
  if(now - last_update >= 50)
  {    
    prev_count_left = count_left;
    prev_count_right = count_right;
    count_left = encoders.getCountsLeft();
    count_right = encoders.getCountsRight();
    previous_time = millis();
    UpdateEffortDriveWheelsPI(target_left, target_right);
    last_update = now;
    //SerialPlotter(chassis.SpeedLeft(),chassis.u_left, chassis.E_left,millis()-start_time);
    SerialPlotter(chassis.SpeedLeft(),chassis.u_left, chassis.E_left, chassis.SpeedRight(),chassis.u_right, chassis.E_right,millis()-start_time);

  }
}

void RomiChassis::StartDriving(float left, float right, uint32_t duration)
{
  target_left = left; 
  target_right = right;

  start_time = millis();
  last_update = start_time;
  end_time = start_time + duration; //fails at rollover
  E_left = 0;
  E_right = 0;


}

bool RomiChassis::CheckDriveComplete(void)
{
  return millis() >= end_time;
}

void RomiChassis::Stop(void)
{
  target_left = 0;
  target_right = 0;
  motors.setEfforts(0, 0);
}