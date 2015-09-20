/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for the robot.
	
	Author 	= Xasin
	Created	= 17.09.15
*/

use <Transforms.scad>

function wheelOffset(n, r) = cos(360/(2*n))*r;
function sliceSlitOffset(n, r) = (sin(360/(2*n))*r);

$fs = 2.1;

module subwheelBase(n, r=20, p=0, shift = 3, split=true) {  //The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
	
	//Rotate to the according outside position.
	rotate([0, 0, (360/n) * p])
	//Translate to the edge of the circle
	translate([ wheelOffset(n, r) - shift, 0, 0])
	//Rotate into horizontal position
	rotate([-90, 0, 0]) 
	//The main core of the subwheel
	render(convexity=4) difference() {
		rotate_extrude() intersection() {
			translate([ - wheelOffset(n, r) + shift, 0]) circle(r=r);
			translate([0, - sin(360/(2*n))*r]) square(sin(360/(2*n))*r *2);
		}
		
		if(split) {
			translate([0,0,-(sin(360/(2*n))*r)]) cylinder(d=2 + 0.4 + 0.1, h= 2* sin(360/(2*n))*r,$fn=15);	//Slot for the Filament-Axis, semi-tight
			translate([0,0, -0.625]) cylinder(r= r - wheelOffset(n, r) + 0.1 + shift, h=1.3); //Split for the connectors for the wheels to fit in.
		}
	}
}


module subwheelSet(n, r, inflated=false) {
	for(i=[0:2:n]) { 	
		if(inflated) {
			subwheelBase(n, r, i, shift = 4.5, split=false);
			translate([0, 0, 10]) subwheelBase(n, r, i+1, shift = 4.25, split=false);
		}
		else {
			subwheelBase(n, r, i);
			translate([0, 0, 10]) subwheelBase(n, r, i+1);
		}
	}
}

//Create the center piece for the omni-wheel
module omniWheel(n, r, subwheels=false) {
	difference() {														
		translate([0,0,-3]) cylinder(r= wheelOffset(n, r) - 4, h=16);	//Create the central cylinder.
		subwheelSet(n, r, true);	//Create spaces for the wheels
	}
	
	if(subwheels) {
		subwheelSet(n, r);
	}
}

omniWheel(6, 25, true);