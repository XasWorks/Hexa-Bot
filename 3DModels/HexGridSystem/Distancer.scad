use <../Lib/NewHexGrid.scad>

connectorHeight = 30;

beamWidth = 2;
beamElevation = 2.2 + 1.6;
beamHeight = connectorHeight - 2* beamElevation;


module hexConnector() {
	lowerHex();
	middleHex();
}

module upperHexConnector() {
	translate([0,0, connectorHeight]) rotate([180, 0, 0]) hexConnector();
}

module connectors() {
	hexConnector();
	upperHexConnector();
}

module stabiliserBeam() {
	rotate([0,0, 30]) cube([beamWidth, 1, beamHeight]);
	rotate([0,0, -30]) translate([- beamWidth, 0, 0]) cube([beamWidth, 1, beamHeight]);
}

module beams() {
	for(i=[0:5]) 
		rotate([0,0, 60 * i]) 
		translate([0, - 17.5 / cos(30) / 2, beamElevation]) stabiliserBeam();
}

beams();
connectors();