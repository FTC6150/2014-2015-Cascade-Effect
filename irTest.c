#pragma config(Sensor, S1,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          IRdirection,   tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
    nMotorEncoder[IRdirection] = 0;
    while(true)
    {   int x = SensorValue[IR];
        char    buffer[16];

        sprintf(buffer, "%d", x);
        nxtDisplayBigTextLine(3 , buffer );

        sprintf(buffer, "%d", nMotorEncoder[IRdirection]);
        nxtDisplayBigTextLine(5 , buffer );
    }


}
