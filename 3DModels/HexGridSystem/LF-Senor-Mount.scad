use <../Lib/NewHexGrid.scad>

hexFillRadius = 17.5 - 3;
hexFillHeight = 2.2;

module hexFill() {
	for(i=[0:60:360]) rotate([0, 0, i]) translate([0, -tan(30)*hexFillRadius /2, 0]) cube([hexFillRadius/2, tan(30)*hexFillRadius, hexFillHeight]);
}

module connectorHex() {
	hexFill();
	lowerHex();
}

screwConnectorLength = 10;
screwConnectorThickness = 1;

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