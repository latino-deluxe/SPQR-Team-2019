//initialize the imu
void init_imu()
{
  IMU.init();
  return;
}//--------------------------------------------------------

//reading the euler angle and checking if the imu is disconnected
int read_euler()
{
  IMU.readEul();                                    //initializes the readings
  imu_temp_euler = IMU.euler.x;                     //puts the current euler x angle into a temporary variable
  return imu_temp_euler;                              //if nothing happened, returns the current x angle
}//--------------------------------------------------------
