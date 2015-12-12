use <../Lib/HexGrid.scad>

hexFillRadius = 17.5 - 3;
hexFillHeight = 2.2;

module connectorHex() {
	lowerFill();
}

screwConnectorLength = 6.5;
screwConnectorThickness = 1.5;

lHexSize = 17.5 - 2.2 - 0.4;

inMovement = 6;

mountXPos = lHexSize /2 - sin(30) * (inMovement);
mountYPos = tan(30) * mountXPos;

module screwCylinder() {
	$fs = 0.85;
	difference() {
		union() {
			children();
			translate([mountXPos, mountYPos, 0]) cylinder(r = 3/2 + screwConnectorThickness, h= screwConnectorLength);
		}
		translate([mountXPos, mountYPos, 0]) cylinder(r= 3/2, h= screwConnectorLength);
	}
}

module sensorConnector() {
	screwCylinder()
	connectorHex();
}

sensorConnector();
