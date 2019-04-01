#include "bluetooth.h"
#include "chat.h"
#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "space_invaders.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>
#include <math.h>

int vel = 160;
int usDist = 70;

int defDir = 0;
int defSpeed = 0;
int defDistance = 2;

void keeper() {

  switch (ball_sensor) {
  case 0:
    if (ball_distance > defDistance) {
      defDir = 0;
      defSpeed = 0;
    } else {
      defDir = 0;
      defSpeed = 180;
    }
    break;
  case 1:
    if (ball_distance > defDistance) {
      defDir = 0;
      defSpeed = 0;
    } else {
      defDir = 10;
      defSpeed = 180;
    }
    break;
  case 2:
    if (ball_distance > defDistance) {
      defDir = 90;
      defSpeed = 80;
    } else {
      defDir = 35;
      defSpeed = 180;
    }
    break;
  case 3:
  case 4:
  case 5:
    if (ball_distance > defDistance) {
      defDir = 90;
      defSpeed = 80;
    } else {
      defDir = 90;
      defSpeed = 180;
    }
  case 6:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 90;
        defSpeed = 180;
      } else {
        defDir = 90;
        defSpeed = 180;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 120;
        defSpeed = 180;
      } else {
        defDir = 120;
        defSpeed = 180;
      }
    }
    break;
  case 7:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 90;
        defSpeed = 180;
      } else {
        defDir = 90;
        defSpeed = 180;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 160;
        defSpeed = 180;
      } else {
        defDir = 160;
        defSpeed = 180;
      }
    }
    break;
  case 8:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 90;
        defSpeed = 180;
      } else {
        defDir = 90;
        defSpeed = 180;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 180;
        defSpeed = 180;
      } else {
        defDir = 180;
        defSpeed = 180;
      }
    }
    break;
  case 9:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 90;
        defSpeed = 180;
      } else {
        defDir = 90;
        defSpeed = 90;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 200;
        defSpeed = 180;
      } else {
        defDir = 200;
        defSpeed = 180;
      }
    }
    break;
  case 10:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 90;
        defSpeed = 180;
      } else {
        defDir = 0;
        defSpeed = 0;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 200;
        defSpeed = 180;
      } else {
        defDir = 200;
        defSpeed = 180;
      }
    }
    break;
  case 11:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 270;
        defSpeed = 180;
      } else {
        defDir = 270;
        defSpeed = 90;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 160;
        defSpeed = 180;
      } else {
        defDir = 160;
        defSpeed = 180;
      }
    }
    break;
  case 12:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 270;
        defSpeed = 180;
      } else {
        defDir = 270;
        defSpeed = 180;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 180;
        defSpeed = 180;
      } else {
        defDir = 180;
        defSpeed = 180;
      }
    }
    break;
  case 13:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 270;
        defSpeed = 180;
      } else {
        defDir = 270;
        defSpeed = 180;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 200;
        defSpeed = 180;
      } else {
        defDir = 200;
        defSpeed = 180;
      }
    }
    break;
  case 14:
    if (us_px < 15) {
      if (ball_distance > defDistance) {
        defDir = 270;
        defSpeed = 180;
      } else {
        defDir = 240;
        defSpeed = 180;
      }
    } else {
      if (ball_distance > defDistance) {
        defDir = 120;
        defSpeed = 180;
      } else {
        defDir = 120;
        defSpeed = 180;
      }
    }
    break;
  case 15:
  case 16:
  case 17:
    if (ball_distance > defDistance) {
      defDir = 270;
      defSpeed = 80;
    } else {
      defDir = 270;
      defSpeed = 180;
    }
    break;
  case 18:
    if (ball_distance > defDistance) {
      defDir = 90;
      defSpeed = 80;
    } else {
      defDir = 325;
      defSpeed = 180;
    }
    break;
  case 19:
    if (ball_distance > defDistance) {
      defDir = 0;
      defSpeed = 0;
    } else {
      defDir = 350;
      defSpeed = 180;
    }
    break;
  default:
    tone(BUZZER, 50000, 500);
    defDir = 0;
    defSpeed = 0;
    break;
  }
  preparePID(defDir, defSpeed);
}

void centerGoalPost() {
  int vel = 150;
  if ((zoneIndex >= 0 && zoneIndex <= 2) || zoneIndex == 4) {
    preparePID(180, vel);
  } else if (zoneIndex == 3 || zoneIndex == 6) {
    preparePID(90, vel);
  } else if (zoneIndex == 5 || zoneIndex == 8) {
    preparePID(270, vel);
  } else {
    stop_menamoli = false;
    if (us_px >= 30)
      preparePID(180, vel);
    else
      preparePID(0, 0);
  }
}

void centerGoalPostCamera() {
  if (portx == 0 || portx == 999) {
    centerGoalPost();
  } else {
    if (zoneIndex < 6) {
      centerGoalPost();
    } else {
      if (portx < keeperMin) {
        preparePID(270, vel);
      } else if (portx > keeperMax) {
        preparePID(90, vel);
      }
    }
  }
}

// void space_invaders_camera() {
//   if (us_px >= 35 || portx == 999) {
//     centerGoalPost();
//   } else {
//     // dx
//     if (ball_sensor >= 1 && ball_sensor <= 6) {
//       if (portx > keeperMin) {
//         preparePID(90, vel);
//       } else {
//         preparePID(0, 0);
//       }
//     }
//     // sx
//     else if (ball_sensor <= 19 && ball_sensor >= 14) {
//       if (portx < keeperMax) {
//         preparePID(270, vel);
//       } else {
//         preparePID(0, 0);
//       }
//     }
//     // behind
//     else if (ball_sensor < 14 && ball_sensor > 6) {
//       goalie();
//     }
//     // in front
//     else {
//       preparePID(0, 0);
//       if (ball_distance <= 3) {
//         goalie();
//       }
//     }
//   }
// }
//
// void space_invaders_us() {
//   if (us_px <= 35) {
//     // dx
//     if (ball_sensor >= 1 && ball_sensor <= 6) {
//       if (us_dx > usDist || us_sx < usDist) {
//         preparePID(90, vel);
//       } else {
//         preparePID(0, 0);
//       }
//     }
//     // sx
//     else if (ball_sensor <= 19 && ball_sensor >= 14) {
//       if (us_sx > usDist || us_dx < usDist) {
//         preparePID(270, vel);
//       } else {
//         preparePID(0, 0);
//       }
//     }
//     // behind
//     else if (ball_sensor < 14 && ball_sensor > 6) {
//       goalie();
//     }
//     // in front
//     else {
//       preparePID(0, 0);
//       if (ball_distance <= 2) {
//         goalie();
//       }
//     }
//   } else {
//     centerGoalPost();
//   }
// }
