#include "keeper.h"
#include "vars.h"
#include "config.h"
#include "position.h"
#include "pid.h"
#include "us.h"
#include "camera.h"
#include "nano_ball.h"
#include "goalie.h"
#include "math.h"
#include <Arduino.h>

int defSpeed = 0;
int defDir = 0;
byte defDistance = 160;

float angle = 0;
float angleX = 0, angleY = 0;
elapsedMillis t = 0;

elapsedMillis toh = 0;

void keeper() {
    
    digitalWrite(Y, HIGH);
    
    if(ball_distance > KEEPER_ATTACK_DISTANCE){
        // Ball is quite near
        goalie();
        if(!keeper_tookTimer){
            keeperAttackTimer = 0;
            keeper_tookTimer = true;
        }
        if(keeperAttackTimer > KEEPER_ALONE_ATTACK_TIME && keeper_tookTimer && !comrade) keeper_backToGoalPost = true;
        if(keeperAttackTimer > KEEPER_COMRADE_ATTACK_TIME && keeper_tookTimer && comrade) keeper_backToGoalPost = true;

    }else{
        
        angle = (90 + ball_degrees) * M_PI / 180;
        angleX = abs(cos(angle));

        if(ball_degrees >= 0 && ball_degrees <= 90 && fixCamIMU(pDef) < 30) preparePID(90, KEEPER_BASE_VEL*angleX*KEEPER_VEL_MULT);
        else if(ball_degrees >= 270 && ball_degrees <= 360  && fixCamIMU(pDef) > -30) preparePID(270, KEEPER_BASE_VEL*angleX*KEEPER_VEL_MULT);
        else if(ball_degrees < 270 && ball_degrees > 90){
            int ball_degrees2 = ball_degrees > 180? ball_degrees-360:ball_degrees;
            int dir = ball_degrees2 > 0 ? ball_degrees + KEEPER_BALL_BACK_ANGLE : ball_degrees - KEEPER_BALL_BACK_ANGLE;
            dir = dir < 0? dir + 360: dir;
            
            preparePID(dir, KEEPER_BASE_VEL);
        }
        centerGoalPostCamera(false);    
        if(keeper_tookTimer && keeper_backToGoalPost && comrade) centerGoalPostCamera(true);       
        
            // if(ball_degrees >= 0 && ball_degrees <= 90) preparePID(90, 320*angleX*1.2);
        // else if(ball_degrees >= 270 && ball_degrees <= 360) preparePID(270, 320*angleX*1.2);
        // else {
        //     int ball_degrees2 = ball_degrees > 180? ball_degrees-360:ball_degrees;
        //     int dir = ball_degrees2 > 0 ? ball_degrees + 30 : ball_degrees - 30;
        //     dir = dir < 0? dir + 360: dir;
            
        //     preparePID(dir, 320);
        // }
        // centerGoalPostCamera(false);    
    }
}