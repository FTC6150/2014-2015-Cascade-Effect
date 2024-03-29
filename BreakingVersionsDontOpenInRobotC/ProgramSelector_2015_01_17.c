#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     bottomLimitSwitch, sensorTouch)
#pragma config(Sensor, S3,     topLimitSwitch, sensorTouch)
#pragma config(Sensor, S4,     IrSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          IrScanner,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     nada,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    TubeGrab,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    ScoopGate,            tServoStandard)

/*
Make sure to check autonomous include file names for the latest and most stable autonomous filename
 and that the latest and most stable autonomous files do NOT have a task main() method in them  as there
 should only be one main method which is included in this Program Selector file.
*/

#include "JoystickDriver.c";
#include "DriveSingleencoder.c"
//#include "MoveSingleTiming.c"
#include "AutoBaseKick_2015_01_15.c"
#include "AutoRamp_2015_01_15.c"

task main()
{
    static const short NoButton         = -1;
	static const short ExitButton       =  0;
	static const short RightButton      =  1;
	static const short LeftButton       =  2;
	static const short EnterButton      =  3;
    static const short InitialUninited  =  0;
    static const short ramp        		=  1;
    static const short base         	=  2;

    int action = InitialUninited;
    bool actionSelector = true; // wil this work  or will it point to what ever is in the 1 place in ram.
	bool grabBase = true;
	char *actionString = "none";

    while(actionSelector)
   {
	   nxtDisplayBigTextLine(4, actionString); //To print currently selected action.

       switch(nNxtButtonPressed)
       {
           case ExitButton:
                action = InitialUninited;
				actionString = "none"; //Click the bottom button (or the back button if  you prefer)  to exit the program. Will print  "none" on NXT screen.
                break;
           case RightButton:
                action = ramp;
				actionString = "ramp"; //Click the right arrow on nxt to select the ramp autonomous. Will print "ramp" on NXT screen.
                break;
           case LeftButton:
                action = base;
				actionString = "base";// Click the left arrow button on nxt to select the base autonomous. Will print "base" on NXT screen.
                break;
           case EnterButton:
                if(action != InitialUninited) // Click the  middle button (or select button if you prefer) to finalize the autonomous that you want to run. Will print nothing on NXT screen.
                {
                   actionSelector = false;
				   actionString = "grab";
                }
                break;
        }
   }

    actionSelector = true;

		 //To start up while loop in case base autonomous was selected.

		while(actionSelector)
		{
			nxtDisplayBigTextLine(4, actionString); //To print choosen style of base autonomous.

			switch(nNxtButtonPressed)
			{
			    case ExitButton:
				    grabBase = true;
				    actionString = "none";  //Click the bottom button (or the back button if  you prefer)  to exit the program. Will print  "none" on NXT screen.
				    break;
			    case RightButton:
				    grabBase = true;
				    actionString = "grab"; //Click the right arrow on nxt to select grabber sequence. Will print "grab" on NXT screen.
				    break;
			    case LeftButton:
				    grabBase = false;
				    actionString = "no grab"; // Click the left arrow button on nxt to select no grabber sequence. Will print "no grab" on NXT screen.
			    	break;
			    case EnterButton:
				    actionSelector = false;
			        break;
		    }
	    }

	/*
	Waiting for the start signal to the samatha after program has been selected.
	Pressing the back button will still exit  this programming if deemed unnecessary.
	*/
   waitForStart();

   if(action == ramp)
   {
		RampProgram(grabBase); //ramp autonomous with no grabber sequence.
   }
   else if(action == base)
   {
		BaseWithKickProgram(grabBase); // Base autonmous with kickstand sequence.
   }
   else
   {
        nxtDisplayBigTextLine(6, "Error"); // Will print "Error" on NXT screen due to failure of launch of requested autonomous.
   }

}