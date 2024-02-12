#include "defs.h"

lidardata lidarmanager::scan(LW20& lidar) {
  //run scan
}

pointmap lidarmanager::lidarprocess(lidardata raw) {
    //turn raw lidar data into useful cartesian coordinates
    pointmap output;
    int i;
    int j;
    for (i = 0; i < LAYERCOUNT; ++i) {
      for (j = 0; j < LAYERRES; ++j) {
        output.map[j * (i + 1)].x = raw.scanlayers[i].distance[j] * cos(DEG_TO_RAD * raw.scanlayers[i].azimuth[j]);
        output.map[j * (i + 1)].y = raw.scanlayers[i].distance[j] * sin(DEG_TO_RAD * raw.scanlayers[i].azimuth[j]);
        output.map[j * (i + 1)].z = raw.scanlayers[i].distance[j] * sin(DEG_TO_RAD * raw.scanlayers[i].elevation[j]);
    } 
  }
  return output;
}
