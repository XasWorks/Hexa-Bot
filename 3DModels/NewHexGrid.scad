use <Transforms.scad>

defaultHexSize = 15;
beamSize = 1;			//Thickness of the beam
beamHeight = 2.5;			//The height of either one of the upper or lower beams.
beamOuterShift = 1.6;		//How far should the outer edge point of the transition from either lower or upper section to middle section be shifted inwards?
beamShift = 1.6;			//How far should the two sections be spread apart?

beamPlay = 0.08; 			//How much room should be left between 

module lowerHex(hexSize = defaultHexSize) {
	render() for(i=[0:5]) rotate([0,0, 360/6 * i]) 
		translate([hexSize/2 - beamSize*2 - beamPlay, 
			-tan(30) * (hexSize- beamSize*2 - beamPlay) * 0.5, 0]) 
		cube([beamSize, tan(30)* (hexSize - beamSize*2 - beamPlay), beamHeight]);
}

module middleHex(hexSize = defaultHexSize, aligned= false) {
	if(aligned) translate([0,0, beamHeight]) middleHex(hexSize);
	else 
	render() for(i=[0:5]) rotate([0,0, 360/6 *i])
		shine(length = hexSize, height= beamHeight*2, angle = 60.1)
		rotate([90,0,0]) 
		translate([0, 0, -tan(30) * hexSize * 0.5]) 
		linear_extrude(height= tan(30)* (hexSize))
			polygon([	[hexSize/2 - beamSize*2 - beamPlay, 0],
							[hexSize/2 - beamSize - beamPlay, 0],
							[hexSize/2, beamShift],
							[hexSize/2 - beamSize, beamShift]]);
}

module upperHex(hexSize = defaultHexSize, aligned= false) {
	if(aligned) translate([0,0, beamHeight + beamShift]) upperHex(hexSize);
	else 
	render() for(i=[0:5]) rotate([0,0, 360/6 * i]) 
		translate([hexSize/2 - beamSize + 0.0001, 
			-tan(30) * (hexSize) * 0.5, 0]) 
		cube([beamSize, tan(30)* (hexSize), beamHeight]);
}

module hexPattern(i, hexSize = defaultHexSize) {
	for(x=i) {
		if(x[1] % 2 != 0)
			translate([hexSize * x[0] + hexSize/2, x[1] * hexSize * sin(60)]) children();
		else 
			translate([hexSize * x[0], x[1] * sin(60) * hexSize]) children();
	}
}

hexPattern([[1,-2], [0,-1], [0,0], [0,1], [1,2]]) union() {
	upperHex(aligned=true);
	lowerHex();
	middleHex(aligned=true);
}

hexPattern([[0,-1], [0,0], [0,1]], 20) union() {
	upperHex(20, true);
	lowerHex(20);
	middleHex(20, true);
}