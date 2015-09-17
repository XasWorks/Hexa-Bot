/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for the robot.
	
	Author 	= Xasin
	Created	= 17.09.15
*/

use <Transforms.scad>



module subwheelBase(n, r=20) {											//The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
		render(convexity=4) difference() {
		rotate_extrude(convexity=5) intersection() {
			translate([0,-r,0]) square([r,r*2]);								//Only use the wanted "outside" circle
			translate([-cos(360/(2*n))*r -0.3,0]) circle(r=r,$fa=4);		//Base circle (Radius of the wheel)
		}
		
		translate([0,0,-r]) cylinder(d=1.8, h=r*2,$fn=15);				//Slot for the Filament-Axis
	}
}

module subwheelBaseCenter(n, r, s=2) {									//Cuts down the base structure into the center of the three parts that will be later used to create a omni-wheel. Creates a Center-Piece for a subwheel for a wheel of Radius R with N Subwheels, whilst leaving S space between pieces.
	render(convexity = 4) difference() {
		subwheelBase(n, r);
		translate([0,0,(sin(360/(2*n))*r )/3 - s/2]) cylinder(r=r, h=r*2);
		translate([0,0,- (sin(360/(2*n))*r)/3 + s/2 - r*2]) cylinder(r=r, h=r*2);
	}
}

module subwheelBaseEdge(n, r, s=2, top=true) {						//Cutss down the base structure into either edge of the three parts that will be later used to create a omni-wheel. Create either the top (default) or bottom (top = false) piece for a Subwheel for a wheel of radius R with N subwheels, whilst leaving S space between pieces.
	render(convexity = 4) intersection() {
		subwheelBase(n, r);
		if(top) {
			translate([0,0,(sin(360/(2*n))*r )/3 + s/2]) cylinder(r=r, h=r*2); }
		else {
			translate([0,0,- (sin(360/(2*n))*r)/3 - s/2 - r*2]) cylinder(r=r, h=r*2); }
	}
}

subwheelBaseEdge(5,30,1.5);
subwheelBaseEdge(5,30,1.5,top=false);
subwheelBaseCenter(5,30,1.5);