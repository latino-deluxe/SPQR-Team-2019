void ball_read_position()
{
  spi_readfrom644l(); //getting our data from our spi slave
  ball_seen = true; //in any other case the ball is seen by the robot
  if (ball_distance == 6)
  {
    ball_seen = false; //if the distance is 6 it means that the robot doesnt see the ball
  }

  if (old_s_ball != ball_sensor)
  {
    old_s_ball = ball_sensor;
    time_s_ball = millis();  // per quanto tempo lo stesso sensore vede la palla >usata in keeper e non in goalie<
  }
  return;
}//--------------------------------------------------------------


void update_sensors_all()
{
  us_read(); //reads the ultrasonic sensors every 70 ms >us_fr,us_px,us_dx,us_sx<

  imu_current_euler = read_euler(); //reads the imu euler angle >imu_current_euler<

  ball_read_position(); //reads the ball sensor >ball_sensor, ball_distance, ball_seen<
  return;
}//--------------------------------------------------------------
