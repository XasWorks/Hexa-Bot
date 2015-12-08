use <../Lib/HexGrid.scad>

basePosition = 	[[0, 1.5* 17.5/cos(30)/2, 2.25],
				 [0,0,0]];

module position(modArray, negative = false) {
	if(negative) {
		rotate([		-modArray[1][0],
					-modArray[1][1],
					-modArray[1][2]])
		translate([	-modArray[0][0],
					-modArray[0][1],
					-modArray[0][2]])
		children();
	}
	else {
		rotate(modArray[1]) translate(modArray[0]) children();
	}
}

module base() {
	hexPattern([
			[-2,2],[-1,2],[0,2],[1,2],[2,2],
			[-2,0],[-1,0],[0,0],[1,0],[2,0]]) {
		lowerHex();
		hexFill();
	}
}

electronicsWidth = 75.8;
electronicsDepth = 35.5;
plateThickness = 1;
wallThickness = 1.5;

pillarSupport = 2;
pillarSupportHeight = 1.5;
pillarThickness = 2;
pillarHeight = 3;

module mountPillar() {
	translate([- pillarThickness/2, -wallThickness - pillarSupport, 0]) {
		cube([pillarThickness, wallThickness + pillarSupport, pillarHeight]);
		translate([0, pillarSupport, pillarHeight]) cube([pillarThickness, wallThickness, pillarSupportHeight]);
	}
}

module pillars(positions) {
	position(platePosition, true) electronicsPlate();

	for(i=positions) {
		rotate([0, 0, -90*i[0]]) {
			if(i[0] == 0 || i[0] == 2) {
				translate([i[1] - electronicsWidth/2, electronicsDepth/2 + wallThickness, 0]) mountPillar();
			}
			else
			translate([i[1] - electronicsDepth/2, electronicsWidth/2 + wallThickness, 0]) mountPillar();
		}
	}
}

platePosition = [	[0, 0, plateThickness],
					[0, 0, 0]];

module electronicsPlate() {
	position(basePosition, true) base();

	difference() {
		translate([ - (electronicsWidth + wallThickness*2)/2, -(electronicsDepth + wallThickness*2)/2, 0])
		cube([(electronicsWidth + wallThickness*2), (electronicsDepth + wallThickness*2), plateThickness]);

		translate([ - (electronicsWidth - pillarSupport*2)/2, -(electronicsDepth-pillarSupport*2)/2, 0]) cube([electronicsWidth - pillarSupport*2, electronicsDepth - pillarSupport*2, plateThickness]);
	}
}

pillars([	[0,2], [0, 22], [0, 46], [0, 66],
		[1, 12], [1, 22],
		[2, 9], [2, 38], [2, 55], [2, 70],
		[3, 5.5], [3, 23], [3, 34]]);
