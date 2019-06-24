#include "keeper.h"
#include "vars.h"
#include "space_invaders.h"
#include "position.h"
#include "pid.h"
#include "us.h"
#include "camera.h"
#include <Arduino.h>

int defSpeed = 0;
int defDir = 0;
byte defDistance = 160;

void keeper() {

    if(ball_distance > defDistance){
        if (ball_degrees >= 345 || ball_degrees <= 15){
            defDir = 0;
            defSpeed = 0;
        }else if(ball_degrees > 15 && ball_degrees <= 90){
            defDir = 90;
            defSpeed = 255;
        }else if(ball_degrees < 345 && ball_degrees >= 270){
            defDir = 270;
            defSpeed = 255;
        }else if(ball_degrees < 270 && ball_degrees >= 180){
            defDir = 150;
            defSpeed = 255;
        }else if(ball_degrees < 180 && ball_degrees > 90){
            defDir = 210;
            defSpeed = 255;
        }
    }else{
        if (ball_degrees >= 345 || ball_degrees <= 15){
            defDir = 0;
            defSpeed = 0;
        }else if(ball_degrees > 15 && ball_degrees <= 90){
            defDir = 90;
            defSpeed = 255;
        }else if(ball_degrees < 345 && ball_degrees >= 270){
            defDir = 270;
            defSpeed = 255;
        }else if(ball_degrees < 270 && ball_degrees >= 180){
            defDir = 150;
            defSpeed = 255;
        }else if(ball_degrees < 180 && ball_degrees > 90){
            defDir = 210;
            defSpeed = 255;
        }
    }


    preparePID(defDir, defSpeed);
}

// void keeper(){
//     x = 1;
//     y = 1;

//     if(ball_degrees >= 345 || ball_degrees <= 15){
//         if(ball_distance > defDistance){
//             defDir = 0;
//             defSpeed = 0;
//         }else{
//             defDir = 0;
//             defSpeed = 0;
//         }
//     }

//     if(ball_degrees > 15 && ball_degrees < 30){
//         if(ball_distance > defDistance){
//             defDir = 30;
//             defSpeed = 255;
//         }else{
//             defDir = 0;
//             defSpeed = 0;
//         }
//     }

//     if(ball_degrees >= 30 && ball_degrees < 45){
//         if(ball_distance > defDistance){
//             defDir = 90;
//             defSpeed = 255;
//         }else{
//             defDir = 90;
//             defSpeed = 255;
//         }
//     }

//     if(ball_degrees >= 45 && ball_degrees < 90){
//         if(ball_distance > defDistance){
//             defDir = 90;
//             defSpeed = 255;
//         }else{
//             defDir = 90;
//             defSpeed = 255;
//         }
//     }

//     if(ball_degrees >= 90 && ball_degrees < 145){
//         if(ball_distance > defDistance){
//             defDir = 180;
//             defSpeed = 255;
//         }else{
//             defDir = 180;
//             defSpeed = 255;
//         }
//     }

//     if(ball_degrees >= 145 && ball_degrees <= 180){
//         if(ball_distance > defDistance){
//             defDir = 180;
//             defSpeed = 255;
//         }else{
//             defDir = 0;
//             defSpeed = 0;
//         }
//     }

//     if(ball_degrees > 180 && ball_degrees <= 215){
//         if(ball_distance > defDistance){
//             defDir = 180;
//             defSpeed = 255;
//         }else{
//             defDir = 0;
//             defSpeed = 0;
//         }
//     }

//     if(ball_degrees > 215 && ball_degrees <= 270){
//         if(ball_distance > defDistance){
//             defDir = 180;
//             defSpeed = 255;
//         }else{
//             defDir = 180;
//             defSpeed = 255;
//         }
//     }

//     if(ball_degrees > 270 && ball_degrees <= 315){
//         if(ball_distance > defDistance){
//             defDir = 270;
//             defSpeed = 255;
//         }else{
//             defDir = 270;
//             defSpeed = 255;
//         }
//     }

//     if(ball_degrees > 315 && ball_degrees <= 330){
//         if(ball_distance > defDistance){
//             defDir = 270;
//             defSpeed = 255;
//         }else{
//             defDir = 270;
//             defSpeed = 255;
//         }
//     }

//     if(ball_degrees > 330 && ball_degrees < 345){
//         if(ball_distance > defDistance){
//             defDir = 330;
//             defSpeed = 255;
//         }else{
//             defDir = 0;
//             defSpeed = 0;
//         }
//     }

//     // if( (fixCamIMU(pDef) > 20 && ball_degrees <= 90) || (fixCamIMU(pDef) < -20 && ball_degrees <= 90) ) {
//     //     defDir = 0;
//     //     defSpeed = 0;
//     // }

//     preparePID(defDir, defSpeed);

//     if(zoneIndex < 6) centerGoalPostCamera();



// //   if(ball_degrees >= 345 || ball_degrees <= 15)  atk_direction = ball_degrees;
// //   if(ball_degrees > 15  && ball_degrees < 30)    atk_direction = ball_degrees + 20;
// //   if(ball_degrees >= 30 && ball_degrees < 45)    atk_direction = ball_degrees + 40;
// //   if(ball_degrees >= 45 && ball_degrees < 90)    atk_direction = ball_degrees + 50;
// //   if(ball_degrees >= 90 && ball_degrees < 145)   atk_direction = 170;
// //   if(ball_degrees >= 145&& ball_degrees <= 180)  atk_direction = 215;
// //   if(ball_degrees > 180 && ball_degrees <= 215)  atk_direction = 145;
// //   if(ball_degrees > 215 && ball_degrees <= 270)  atk_direction = 190;
// //   if(ball_degrees > 270 && ball_degrees <= 315)  atk_direction = ball_degrees - 50;
// //   if(ball_degrees > 315 && ball_degrees <= 330)  atk_direction = ball_degrees - 40;
// //   if(ball_degrees > 330 && ball_degrees < 345)   atk_direction = ball_degrees - 20;
// }