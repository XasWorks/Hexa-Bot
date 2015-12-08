use <../Lib/HexGrid.scad>

hexFillRadius = 17.5 - 3;
hexFillHeight = 2.2;

module connectorHex() {
	lowerFill();
}

screwConnectorLength = 6.5;
screwConnectorThickness = 1.5;

lHexSize = 17.5 - 2.2 - 0.4;

module screwCylinder() {
	$fs = 0.85;
	difference() {
		union() {
			children();
			translate([lHexSize/2 - 3, 0, 0]) cylinder(r = 3/2 + screwConnectorThickness, h= screwConnectorLength);
		}
		translate([lHexSize/2 - 3, 0, 0]) cylinder(r= 3/2, h= screwConnectorLength);
	}
}

module sensorConnector() {
	screwCylinder()
	connectorHex();
}

sensorConnector();