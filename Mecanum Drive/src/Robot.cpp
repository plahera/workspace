#include "WPILib.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{
	Gyro *gyro = new Gyro(0);

    // Channels for the wheels
    const static int frontLeftChannel	= 0;
    const static int rearLeftChannel	= 3;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 2;

    const static int joystickChannel	= 0;

	RobotDrive robotDrive;	// robot drive system
	Joystick stick;			// only joystick


public:
	Robot() :
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(joystickChannel)								// as they are declared above.

{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the left side motors
	//	robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);	// you may need to change or remove this to match your robot
	}

	/**
	 * Runs the motors with Mecanum drive.
	 */
	void OperatorControl()
	{
		gyro->Reset();
		robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{

        	// Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
        	// This sample does not use field-oriented drive, so the gyro input is set to zero.

			double angle = gyro->GetAngle();
			robotDrive.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(),stick.GetTwist()*.5, angle);

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}

};

START_ROBOT_CLASS(Robot);
