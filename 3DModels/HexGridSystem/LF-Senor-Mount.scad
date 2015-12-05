use <../Lib/NewHexGrid.scad>

hexFillRadius = 17.5 - 3;
hexFillHeight = 2.2;

module connectorHex() {
	hexFill();
	lowerHex();
}

screwConnectorLength = 13;
screwConnectorThickness = 1.5;

module screwCylinder() {
	$fs = 0.85;
	difference() {
		union() {
			children();
			cylinder(r = 3/2 + screwConnectorThickness, h= screwConnectorLength);
		}
		cylinder(r= 3/2, h= screwConnectorLength);
	}
}

module sensorConnector() {
	screwCylinder()
	translate([0, 0, screwConnectorLength - hexFillHeight]) connectorHex();
}

sensorConnector();