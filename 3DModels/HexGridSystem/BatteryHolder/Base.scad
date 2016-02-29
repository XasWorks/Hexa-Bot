use <../../Lib/HexGrid.scad>

hex_ShiftX = -4.5;
hex_ShiftY = -7.5;
hex_pattern = [	[-2, 1], [-1, 1], [0, 1], [1, 1], [2, 1],
							[-2,0], [-1,0], [0,0], [1, 0], [2,0]];

module base() translate([hex_ShiftX, hex_ShiftY, 0]) {
	hexPattern(hex_pattern) {
		translate([0, 0, -3.2]) lowerHex();
		translate([0, 0, -1]) hexSegment(17.5/2 - 1, 17.5/2, 17.5/2 - 2, 17.5/2 - 1.5, h = 1);
	}
}

batteryWidth = 	28;
batteryLength =	73;

module bHolder_middlePlate() {
	translate([-batteryLength/2, -batteryWidth/2, 0])
	cube([batteryLength, batteryWidth, 1.1]);
}

module bHolder_hex() translate([hex_ShiftX, hex_ShiftY, 0])  {
	hexPattern(hex_pattern)
		hexSegment(17.5/2, 17.5/2, 17.5/2 - 1.5, 17.5/2 - 1.5, h=0.9);
}

module bHolder_everythingElse() {
	difference() {
		translate([-50, -50, 0])
		cube([100, 100, 100]);

		bHolder_middlePlate();
	}
}

module bHolder_IntsecScheme() render() {
	intersection() {
		bHolder_middlePlate();
		bHolder_hex();
	}

	bHolder_everythingElse();
}

module bHolder() render() {
	intersection() {
		import(file="BHolder.stl");
		bHolder_IntsecScheme();
	}
}

bHolder();
base();
