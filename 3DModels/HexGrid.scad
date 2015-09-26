use <Transforms.scad>

module beam() {
	beamSize = 0.8;
	beamHeight = 1.75;
	beamOuterShift = 1.3;
	beamShift = 1.5;
	
	translate([- (beamSize*2 + 0.3),0]) 
	polygon([ 	[0,0],
				[beamSize,0],
				[beamSize, beamHeight],
				[beamSize*2 + 0.3, beamOuterShift + beamHeight],
				[beamSize*2 + 0.3, beamHeight*2 + beamShift],
				[beamSize   + 0.4, beamHeight*2 + beamShift],
				[beamSize   + 0.3, beamHeight + beamShift],
				[0, beamHeight + beamShift - beamOuterShift] ]);
}


module alignedBeam() {
shine(length=20,height=10,angle=60)
translate([10.01,7,0]) rotate([90,0,0]) linear_extrude(height = 15,convexity=3) {
	beam();
}
}

module hexPad() 
render(4) for(i=[0:5]) {
	rotate([0,0,i*60]) alignedBeam();
}

module hexStrip(l = 3) {
	for(i=[0:l-1]) {
		translate([20*i,0,0]) hexPad();
	}
}

module hexGrid(x, y, leftEdge= true, rightEdge= true) {
	for(i=[0:y-1]) {
		translate([0, sin(60) * 20 * i]) {
			if(i%2 == 0) {
				hexStrip(x);
			}
			else {
				if(leftEdge && rightEdge) {
					translate([-10, 0, 0]) hexStrip(x +1);
				}
				else if(leftEdge) {
					translate([-10, 0, 0]) hexStrip(x);
				}
				else if(rightEdge) {
					translate([10, 0, 0]) hexStrip(x);
				}
				else {
					translate([10, 0, 0]) hexStrip(x -1);
				}
			}
		}
	}
}


hexGrid(5,5, false, false);