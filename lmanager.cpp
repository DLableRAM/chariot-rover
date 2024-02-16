#include "defs.hpp" 

lidardata lidarmanager::scan() {
  lidardata output;
  //define iterators
  int i;
  int j;
  //do scan
  for (i = 0; i < 255; ++i) {
    servos.set_az(i);
    for (j = INITANGLE; j < ENDANGLE; ++j) {
      servos.set_el(j);
      float distance = lidar.getLaserDistance(LWPT_FIRST, LWRF_RAW);
      //get LIDAR value
      //Angles MUST be converted from servo PWM to radians!
      //output.scanlayers[i].distance[j] = ...
      //output.scanlayers[i].elevation[j] = ...
      //output.scanlayers[i].azimuth[j] = ...
    }
  }
}

pointmap lidarmanager::lidarprocess(lidardata raw) {
    //turn raw lidar data into useful cartesian coordinates
    pointmap output;
    int i;
    int j;
    for (i = 0; i < LAYERCOUNT; ++i) {
      for (j = 0; j < LAYERRES; ++j) {
        output.map[j * (i + 1)].x = raw.scanlayers[i].distance[j] * cos(raw.scanlayers[i].azimuth[j]);
        output.map[j * (i + 1)].y = raw.scanlayers[i].distance[j] * sin(raw.scanlayers[i].azimuth[j]);
        output.map[j * (i + 1)].z = raw.scanlayers[i].distance[j] * sin(raw.scanlayers[i].elevation[j]);
    } 
  }
  return output;
}
