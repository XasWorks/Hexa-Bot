/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for the robot.
	
	Author 	= Xasin
	Created	= 17.09.15
*/

use <Transforms.scad>

function wheelOffset(n, r) = cos(360/(2*n))*r + 0.2;
function sliceSlitOffset(n, r) = (sin(360/(2*n))*r )/3;

module subwheelBase(n, r=20) {											//The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
		render(convexity=4) difference() {
		rotate_extrude(convexity=5) intersection() {
			translate([0,-r,0]) square([r,r*2]);								//Only use the wanted "outside" circle
			translate([-wheelOffset(n,r),0]) circle(r=r,$fa=4);		//Base circle (Radius of the wheel)
		}
		
		translate([0,0,-(sin(360/(2*n))*r) + 3]) cylinder(d=2 + 0.4 + 0.3, h= 2* sin(360/(2*n))*r - 6,$fn=15);				//Slot for the Filament-Axis, loose
		translate([0,0,-(sin(360/(2*n))*r)]) cylinder(d=2 + 0.4, h= 2* sin(360/(2*n))*r);
	}
}

//Cuts down the base structure into the center of the three parts that will be later used to create a omni-wheel. Creates a Center-Piece for a subwheel for a wheel of Radius R with N Subwheels, whilst leaving S space between pieces.
module subwheelBaseCenter(n, r, s=2) {
	render(convexity = 4) difference() {
		subwheelBase(n, r);
		translate([0,0,(sin(360/(2*n))*r )/3 - s/2]) cylinder(r=r, h=r*2);
		translate([0,0,- (sin(360/(2*n))*r)/3 + s/2 - r*2]) cylinder(r=r, h=r*2);
	}
}

//Cutss down the base structure into either edge of the three parts that will be later used to create a omni-wheel. Create either the top (default) or bottom (top = false) piece for a Subwheel for a wheel of radius R with N subwheels, whilst leaving S space between pieces.
module subwheelBaseEdge(n, r, s=2, top=true) {	
	render(convexity = 4) intersection() {
		subwheelBase(n, r);
		if(top) {
			translate([0,0,sliceSlitOffset(n, r) + s/2]) cylinder(r=r, h=r*2); }
		else {
			translate([0,0,- sliceSlitOffset(n, r) - s/2 - r*2]) cylinder(r=r, h=r*2); }
	}
}

//Creates a ready made sliced subwheel for a wheel with R radius and N subwheels, leaving S space between pieces.
module subwheelSliced(n, r, s=2) {
	subwheelBaseEdge(n, r, s);
	subwheelBaseEdge(n, r, s, top=false);
	subwheelBaseCenter(n, r, s);
}


module connectorBeam(n, r) {
	render(convexity=3) difference() {
		union() {
			cylinder(r= 2.5, h= 1.4, $fn=13);								//Outer cylinder for the axis connector
			translate([0, -2.5, 0]) cube([wheelOffset(n, r), 5, 1.4]);	//Connector beam
		}
		cylinder(d= 2.4, h= 1.4, $fn=10);										//Slot for the filament axis
	}
}
			
//Creates the two 5mm beams that connect the filament axis with the actual wheel for a omniwheel of N Subwheels with radius R.
module subwheelConnector(n, r) {
	translate([wheelOffset(n, r), 0, 0]) rotate([-90,180,0]) {					//Translate the outer connectors to the right position (wheel Offset) and rotate them around for fitting position.
		translate([0, 0, sliceSlitOffset(n, r) - 1.4/2]) {							//Translate the upper slot and connector beam.
			connectorBeam(n, r);
		}
		
		translate([0, 0, -sliceSlitOffset(n, r) - 1.4/2]) {						//Translate the lower slot and connector beam.
			connectorBeam(n, r);
		}
	}
}
	
	
//Create the center piece for the omni-wheel
module omniWheel(n, r, subwheels=false) {
	for(i=[0:360/n:360]) {
		rotate([0,0,i]) subwheelConnector(n, r);
	}
	minkowski() {
		cylinder(r= -r + wheelOffset(n, r)*2 - 3.5, h=0.00001);
		sphere(d=5.1,$fn=20);
	}
	
	if(subwheels) for(i=[0:360/n:360]) {
		rotate([-90,0,i]) translate([wheelOffset(n, r), 0, 0]) subwheelSliced(n, r, 1.8);
	}
}

//subwheelBaseCenter(5, 25);
//subwheelBaseEdge(5, 25);
omniWheel(4, 25, true, $fn=50);