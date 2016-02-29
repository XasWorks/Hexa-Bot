$fs = 0.3;

module ringSet(spacing, thickness) {
	translate([0, spacing/2 + thickness])
	
	difference() {
		circle(r = spacing/2 + thickness);
		circle(r = spacing/2);
	}
}

module ringCut(spacing, width, thickness, side) {
	intersection() {
		if(side == "left") {
			translate([- spacing/2 - thickness, 0])
			square([spacing/2 + thickness, spacing + thickness*2]);
		}
		else {
			square([spacing/2 + thickness, spacing + thickness*2]);
		}
	
		ringSet(spacing, thickness);
	}
}

module chainBeams(spacing, width, thickness) {
	square([width/2 - spacing/2 - thickness, thickness]);
	
	translate([0, thickness + spacing])
	square([width/2 - spacing/2 - thickness, thickness]);
}

module chainElement(spacing, width, thickness, side) {
	trXBy = (side != "left") ? (width/2 - (spacing/2 + thickness)) : - (width/2 - (spacing/2 + thickness));
	
	translate([trXBy, 0]) ringCut(spacing, width, thickness, side);
	
	if(side != "left") {
		chainBeams(spacing, width, thickness);
	}
	else {
		translate([- (width/2 - spacing/2 - thickness), 0]) chainBeams(spacing, width, thickness);
	}
}

module chains(spacing, width, thickness, num) {
	trPerNum = spacing + thickness;
	for(i = [0:num-1]) {
		translate([0, trPerNum * i])
		chainElement(spacing, width, thickness, (i%2 == 0) ? "left" : "right");
	}
}

module chain(spacing, width, thickness, height, length) {
	linear_extrude(height)
	chains(spacing - thickness, width, thickness, length / spacing);
}

cube([5, 5, 1]);

translate([2.5, 5, 0])
chain(1.8, 8, 1, 1, 10);

translate([0, 14, 0])
cube([5, 1, 5]);
