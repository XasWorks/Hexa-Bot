use <Transforms.scad>

beamSize = 0.8;			//Thickness of the beam
beamHeight = 2.5;			//The height of either one of the upper or lower beams.
beamOuterShift = 1.4;		//How far should the outer edge point of the transition from either lower or upper section to middle section be shifted inwards?
beamShift = 1.6;			//How far should the two sections be spread apart?

beamPlay = 0.08; 			//How much room should be left between 


module beam() {
	translate([- (beamSize*2 + beamPlay),0]) 
	polygon([ 	[0,0],
				[beamSize,0],
				[beamSize, beamHeight],
				[beamSize*2 + beamPlay, beamOuterShift + beamHeight],
				[beamSize*2 + beamPlay, beamHeight*2 + beamShift],
				[beamSize   + beamPlay, beamHeight*2 + beamShift],
				[beamSize   + beamPlay, beamHeight + beamShift],
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

hexGrid(1,1, false, false);