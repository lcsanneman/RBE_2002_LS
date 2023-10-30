#include <Arduino.h>
#include <Romi32U4.h>
#include "chassis.h"

RomiChassis chassis;

//LUKE GIT TEST


enum ROBOT_STATE {ROBOT_IDLE, ROBOT_DRIVING};
ROBOT_STATE robot_state = ROBOT_IDLE;

Romi32U4ButtonA buttonA;

void setup() {
    Serial.begin(115200);
}

void loop() 
{
  switch(robot_state)
  {
    case ROBOT_IDLE:
      if(buttonA.getSingleDebouncedRelease()) 
      {
        //chassis.StartDriving(50, 50, 10000); //contains your program that the robot executes when pushbutton A is pressed
        //chassis.StartDriving(36, 36, 10000);
        chassis.StartDriving(26, 26, 8000);
        robot_state = ROBOT_DRIVING;
      }
      break;

    case ROBOT_DRIVING:
      chassis.MotorControl();
      //chassis.SerialPlotter(chassis.SpeedLeft(),chassis.u_left, chassis.E_left,millis());
      //chassis.SerialPlotter(chassis.SpeedRight(),chassis.u_right, chassis.E_right,millis()-startTime);


      if(chassis.CheckDriveComplete()) 
      {
        chassis.Stop();
        robot_state = ROBOT_IDLE;
      }
      if(buttonA.getSingleDebouncedRelease()) 
      {
        chassis.Stop();
        robot_state = ROBOT_IDLE;
      }
  }
}



/*#include <Arduino.h>
#include <Romi32U4.h>
#include "chassis.h"

RomiChassis chassis;

enum ROBOT_STATE {ROBOT_IDLE, ROBOT_DRIVING};
ROBOT_STATE robot_state = ROBOT_IDLE;

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;

void setup() {
    Serial.begin(115200);


}

void loop() 
{
  
      if(buttonB.getSingleDebouncedPress()) 
      {
        unsigned long startTime = millis();
        Serial.print(startTime);
        chassis.StartDriving(100, 100, 10000); //contains your program that the robot executes when pushbutton A is pressed
        //robot_state = ROBOT_DRIVING;

        while(millis()<3000+startTime)
        {
          chassis.SerialPlotter(chassis.SpeedLeft(),chassis.curLeftEffort,chassis.curLeftError,millis(),startTime);
          chassis.MotorControl();
          delay(10);
           

        }
        //chassis.Stop();
      }
  
  
  // switch(robot_state)
  // {
  //   case ROBOT_IDLE:

  //     break;

  //   case ROBOT_DRIVING:
  //     chassis.MotorControl();
  //     /*if(chassis.CheckDriveComplete()) 
  //     {
  //       chassis.Stop();
  //       robot_state = ROBOT_IDLE;
  //     }
  //     if(buttonB.isPressed()) 
  //     {
  //       chassis.Stop();
  //       robot_state = ROBOT_IDLE;
  //     }
  // }
}
*/