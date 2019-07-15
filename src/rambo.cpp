 #include "rambo.h"
 #include "keeper.h"
 #include "goalie.h"
 #include "vars.h"
 #include "bluetooth.h"
 #include "chat.h"
 #include "pid.h"
 #include "position.h"
 #include "camera.h"

float angleII = 0;
float angleXII = 0, angleYII = 0;

void rambo() {
    angleII = (90 + ball_degrees) * M_PI / 180;
    angleXII = abs(cos(angleII));
    
    if(ball_degrees >= 30 && ball_degrees <= 90) preparePID(90, 255 * angleXII * 2);
    else if(ball_degrees >= 270 && ball_degrees < 330) preparePID(270, 255 * angleXII * 2);
    else {
        ballBack();
        preparePID(atk_direction, 255);
    }

    if(ball_distance > 190) {
        if(ball_degrees >= 355 || ball_degrees <= 5)  preparePID(ball_degrees, 220);

        if(ball_degrees > 5   && ball_degrees <  30)    atk_direction = ball_degrees + 30;
        if(ball_degrees > 330 && ball_degrees <  355)   atk_direction = ball_degrees - 30;

        if((ball_degrees >= 330 || ball_degrees <= 30) && ball_distance > 200) preparePID(atk_direction, 220, cstorc);
        else preparePID(atk_direction, 220);
    } else {
        if(ball_degrees >= 0 && ball_degrees <= 30) preparePID(90, 255 * angleXII * 2);
        else if(ball_degrees >= 355 && ball_degrees < 360) preparePID(270, 255 * angleXII * 2);
    }


    if(zoneIndex < 6) {
        int vel = 255;
        if(us_px > 45) preparePID(180, 200);
        if (fixCamIMU(pDef) > 20) preparePID(270, vel);
        else if (fixCamIMU(pDef) < -20) preparePID(90, vel);
        else if(!ball_seen) preparePID(0, 0);
    }
    
}
