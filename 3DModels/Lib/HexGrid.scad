//Size of the hexagons, from one end to another
hexDiameter = 17.5;

//Height of the different pieces
hexHeight = 2.2;
hexMiddleHeight = 1.6;

//Thickness of a beam of the hex piece
beamThickness = 1;

//By how much should the polygon piece slope at the bottom layer?
hexPlay = 0.3;

//Generate a parenting node for the according hexagon
function hexNode(hexagon, height = hexHeight + hexMiddleHeight, rotation = 0) =
			//Translative coordinates
			[	[	hexDiameter * hexagon[0] + ((hexagon[1] % 2 != 0) ? hexDiameter/2 : 0),
					hexDiameter * sin(60) * hexagon[1],
					height],
			//Rotation coordinates
				[	0, 0, 60 * rotation] ];

module hexSegment(b2, t2, b1 = 0.0001, t1 = 0.0001, h) {
	fixDist = 0;

	render(convexity = 3)
	for(i=[0:5]) rotate([0, 0, i * 60])
	polyhedron(
		points = [	//Lower segments
					[b1, -tan(30) *b1, 0],	//0 - bottom left
					[b1,  tan(30) *b1, 0],	//1 - top left
					[b2,  tan(30) *b2, 0],	//2 - top right
					[b2, -tan(30) *b2, 0],	//3 - bottom right
					//Upper segments
					[t1, -tan(30 - fixDist) *t1, h],	//4 - bottom left
					[t1,  tan(30 - fixDist) *t1, h],	//5 - top left
					[t2,  tan(30 - fixDist) *t2, h],	//6 - top right
					[t2, -tan(30 - fixDist) *t2, h]],	//7 - bottom right
		faces = [
					[0, 3, 2, 1],	//Bottom face
					[4, 5, 6, 7],	//Top face
					[2, 3, 7, 6],	//Front face

					[0, 1, 5, 4],	//Back face

					[0, 4, 7, 3],	//Left face

					[1, 2, 6, 5]] );	//Right face
}

module lowerHex() {
	hexSegment(	hexDiameter /2 - beamThickness - hexPlay,
					hexDiameter /2 - beamThickness,
					hexDiameter /2 - beamThickness *2,
					hexDiameter /2 - beamThickness *2,
					hexHeight);
}

module lowerFill() {
	hexSegment(	 hexDiameter /2 - beamThickness - hexPlay,
					hexDiameter /2 - beamThickness,
					0.0001,
					0.0001,
					hexHeight);
}

module hexFill() {
	lowerFill();
	lowerHex();
}

module hexBase(filled = true) {
		translate([0, 0, -3.2]) if(filled) hexFill(); else lowerHex();
		translate([0, 0, -1]) hexSegment(17.5/2 - 1, 17.5/2 + 0.01, filled ? 0.01 : 17.5/2 - 2, filled ? 0.01 : 17.5/2 - 1.5, h = 1);
}

module middleHex(aligned = true) {
	if(aligned)
		translate([0, 0, hexHeight]) middleHex(false);
	else
		hexSegment(	hexDiameter/2 - beamThickness,
						hexDiameter/2,
						hexDiameter/2 - beamThickness *2,
						hexDiameter/2 - beamThickness,
						hexMiddleHeight);
}

module upperHex(aligned = true) {
	if(aligned)
		translate([0, 0, hexHeight + hexMiddleHeight]) upperHex(false);
	else
		hexSegment(	hexDiameter/2,
						hexDiameter/2,
						hexDiameter/2 - beamThickness,
						hexDiameter/2 - beamThickness,
						hexHeight);
}

module hex() {
	lowerHex();
	middleHex();
	upperHex();
}

module hexPattern(i) {
	render() for(x=i) {
		if(x[1] % 2 != 0)
			translate([hexDiameter * x[0] + hexDiameter/2, x[1] * hexDiameter * sin(60)]) children();
		else
			translate([hexDiameter * x[0], x[1] * sin(60) * hexDiameter]) children();
	}
}
