//  Author:Frankie.Chu
//  Date:20 November, 2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/
#include "MotorDriver.h"
#include "seeed_pwm.h"

void MotorDriver::begin()
{
    speed0 = 0;
    speed1 = 0;
	pinMode(MOTORSHIELD_IN1,OUTPUT);
	pinMode(MOTORSHIELD_IN2,OUTPUT);
	pinMode(MOTORSHIELD_IN3,OUTPUT);
	pinMode(MOTORSHIELD_IN4,OUTPUT);
    digitalWrite(MOTORSHIELD_IN1, LOW);
    digitalWrite(MOTORSHIELD_IN2, LOW);
    digitalWrite(MOTORSHIELD_IN3, LOW);
    digitalWrite(MOTORSHIELD_IN4, LOW);
    PWM.init();
}

void MotorDriver::stop(unsigned char motor_id)
{
    speed(motor_id, 0);
}

void MotorDriver::brake(unsigned char motor_id)
{
    switch(motor_id)
    {
        case 0:
        //move(0, 0);
        digitalWrite(MOTORSHIELD_IN1, HIGH);
        digitalWrite(MOTORSHIELD_IN2, HIGH);
        speed0 = 0;
        
        break;
        
        case 1:
        //move(1, 0);
        digitalWrite(MOTORSHIELD_IN3, HIGH);
        digitalWrite(MOTORSHIELD_IN4, HIGH);
        speed1 = 0;
        
        break;
        
        default:;
    }
}

void MotorDriver::speed(int motor_id, int _speed)
{
    if(motor_id<0 || motor_id>1)return;
    
    _speed = _speed<-100 ? -100 : _speed;
    _speed = _speed>100 ? 100 : _speed;
    
    if(motor_id == 0 && speed0 == _speed)return;
    else speed0 = _speed;
    
    if(motor_id == 1 && speed1 == _speed)return;
    else speed1 = _speed;
    
    switch(motor_id)
    {
        case 0:
        
        if(_speed>0)
        {
            digitalWrite(MOTORSHIELD_IN1, HIGH);
            digitalWrite(MOTORSHIELD_IN2, LOW);
            PWM.setPwm(9, _speed, 10000);
        }
        else if(_speed<0)
        {
            digitalWrite(MOTORSHIELD_IN1, LOW);
            digitalWrite(MOTORSHIELD_IN2, HIGH);
            PWM.setPwm(9, 0-_speed, 10000);
        }
        else
        {
            digitalWrite(MOTORSHIELD_IN1, LOW);
            digitalWrite(MOTORSHIELD_IN2, LOW);
            PWM.setPwm(9, _speed, 10000);
        }
        
        break;
        
        case 1:
        
        if(_speed>0)
        {
            digitalWrite(MOTORSHIELD_IN3, HIGH);
            digitalWrite(MOTORSHIELD_IN4, LOW);
            PWM.setPwm(10, _speed, 10000);
        }
        else if(_speed<0)
        {
            digitalWrite(MOTORSHIELD_IN3, LOW);
            digitalWrite(MOTORSHIELD_IN4, HIGH);
            PWM.setPwm(10, 0-_speed, 10000);
        }
        else
        {
            digitalWrite(MOTORSHIELD_IN3, LOW);
            digitalWrite(MOTORSHIELD_IN4, LOW);
            PWM.setPwm(10, _speed, 10000);
        }
        break;
        
        default:;
    }
}
