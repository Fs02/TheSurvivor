#ifndef ME_MATH_HPP_INCLUDED
#define ME_MATH_HPP_INCLUDED

#define DEGTORAD (b2_pi /180)
#define RADTODEG (180/b2_pi)
#define RATIO 30.f
#define UNRATIO (1/30.f)

//-------------------------------------------------------------------------------------------------
//Define Player State
//-------------------------------------------------------------------------------------------------

#define IDLE 0
#define FOWARD 1
#define BACKWARD 2
#define TURNLEFT 3
#define TURNRIGHT 4
#define HANDBRAKE 5

//-------------------------------------------------------------------------------------------------
//Fixture Category Bits
//-------------------------------------------------------------------------------------------------
#define PLAYER 1
#define VEHICLE 2
#define ENEMY 3
#define H_VEHICLE_SENSOR 4


#endif // ME_MATH_HPP_INCLUDED
