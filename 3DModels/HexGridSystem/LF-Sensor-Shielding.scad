/*
    LF-Sensor shielding to increase precision of the sensors despite their ... quality.
    Created on 11.12.15, @Xasin
*/

use <../Lib/Parenting.scad>

baseThickness = 1;
holePosition = 13.3;

basePosition = [[0, 0, baseThickness], 0];


sensorYSize = 6.7;
sensorXSize = 7;

sensorYDistance = 1.2;
sensorXDistance = 2;

module base() {
  difference() {
      translate([-5, 0, 0]) cube([10, 17, baseThickness]);

      translate([0, holePosition, -0.001]) cylinder(r=3/2, h=baseThickness + 1, $fn = 10);

      translate([-sensorXSize/2, sensorYDistance, -0.001]) cube([sensorXSize, sensorYSize, baseThickness + 1]);
  }
}

shieldingHeight = 25;
shieldingScale = 1.7;

module shieldShape() {
  difference() {
    translate([-5, 0]) square([10, sensorYDistance*1.8 + sensorYSize]);

    translate([-sensorXSize/2, sensorYDistance]) square([sensorXSize, sensorYSize]);
  }
}

module shield() {
  translate([0, sensorYSize + sensorYDistance, 0]) linear_extrude(height = shieldingHeight, scale = shieldingScale) {
    translate([0, -sensorYSize - sensorYDistance, 0]) shieldShape();
  }
}

base();
parentBy(basePosition) shield();
