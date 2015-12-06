use <../Lib/HexGrid.scad>

hexFillRadius = 17.5 - 3;
hexFillHeight = 2.2;

module connectorHex() {
	lowerFill();
}

screwConnectorLength = 6.5;
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
	connectorHex();
}

sensorConnector();