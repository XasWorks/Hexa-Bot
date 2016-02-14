// Data structure for a connection piece: 
/* [ outer Radius,
	 inner Radius,
	 height,
	 angle Freedom]
*/


use <Transforms.scad>

module donut(r1, r2, h) {
	difference() {
		cylinder(r = r1, h = h);
		cylinder(r = r2, h = h);
	}
}

module connectorLeft(profile) {
	thisAngle = 180 - profile[3] /2;
	
	shine(angle = thisAngle, height = profile[2], length = 30)
	donut(profile[0], profile[1], profile[2]);
}

module connectorRight(profile) {
	rotate([0, 0, 180]) connectorLeft(profile);
}
