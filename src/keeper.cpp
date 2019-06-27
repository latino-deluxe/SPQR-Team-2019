#include "keeper.h"
#include "vars.h"
#include "space_invaders.h"
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

void keeper() {

    angle = (90 + ball_degrees) * M_PI / 180;
    angleX = abs(cos(angle));
    
    if (ball_degrees > 345 || ball_degrees < 15){
        if(ball_distance > 225) goalie();
        else preparePID(0, 0);
    }
    else if(ball_degrees >= 15 && ball_degrees <= 90) preparePID(90, 340*angleX*1.2);
    else if(ball_degrees >= 270 && ball_degrees <= 345) preparePID(270, 340*angleX*1.2);
    else{
        int ball_degrees2 = ball_degrees > 180? ball_degrees-360:ball_degrees;
        int dir = ball_degrees2 > 0 ? ball_degrees + 30 : ball_degrees - 30;
        dir = dir < 0? dir + 360: dir;
        preparePID(dir,255);
    }
    
    if(zoneIndex < 6) centerGoalPostCamera();
}