use <../Lib/HexGrid.scad>
use </usr/lib/openscad/arm_joints.scad>

$fs = 0.7;

module hexConnector() {
	translate([4.5, 0, 2.2]) rotate([0, 0, 90]) armEndRounded();
	lowerFill();
}

module SensrConnector() {
	holeDist = 37; 
	
	difference() {
		hull() {
			translate([-holeDist/2, 0, 0]) 
				cylinder(r = 4, h = 1);
			translate([holeDist/2, 0, 0])
				cylinder(r = 4, h = 1);
		}
		
		translate([-holeDist/2, 0, -0.1]) 
			cylinder(r = 1.5, h = 1.2);
		translate([holeDist/2, 0, -0.1])
			cylinder(r = 1.5, h = 1.2);
	}
	
	translate([0, 0, 1]) armEndRounded();
}

translate([0, 15, 0]) hexConnector();
SensrConnector();
translate([15, 15, 0]) arm(10);