/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for the robot.
	
	Author 	= Xasin
	Created	= 17.09.15
*/

use <Transforms.scad>

function subwheelRadius(n, r) = r - cos(360/(2*n))*r + 2.5;
function wheelOffset(n, r) = cos(360/(2*n))*r;
function sliceSlitOffset(n, r) = (sin(360/(2*n))*r);

$fs = 2.1;

module subwheelBase(n, r=20, p=0, shift = 2.5, split=true, positioned=true) {  //The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
	
	if(positioned) {
		//Rotate to the according outside position.
		rotate([0, 0, (360/n) * p])
		//Translate to the edge of the circle
		translate([ wheelOffset(n, r) - shift, 0, 0])
		//Rotate into horizontal position
		rotate([-90, 0, 0]) 
		//The main core of the subwheel
		subwheelBase(n, r, p, shift, split, false);
	}
	else {
		render(convexity=4) difference() {
			rotate_extrude() intersection() {
				translate([ - wheelOffset(n, r) + shift, 0]) circle(r=r, $fn = 70);
				translate([0, - sin(360/(2*n))*r]) square(sin(360/(2*n))*r *2);
			}
			
			if(split) {
				translate([0,0,-(sin(360/(2*n))*r)]) cylinder(d=2 + 0.4 + 0.1, h= 2* sin(360/(2*n))*r,$fn=15);	//Slot for the Filament-Axis, semi-tight
				translate([0,0, -0.625]) cylinder(r= r - wheelOffset(n, r) + 0.1 + shift, h=1.3); //Split for the connectors for the wheels to fit in.
			}
		}
	}
}

sLS = 6.5;

//Create a connecting beam for the subwheels
module subwheelConnector(n, r, i, flipped=false) {
	if(flipped) {
		translate([0,0, sLS]) rotate([180,0, (360/n)*i]) subwheelConnector(n, r, 0);
	}
	else {
		render(convexity= 3) 
		rotate([0,0, (360/n)*i]) translate([wheelOffset(n, r) - 2.5, 0, 0]) difference() {
			hull() {		//Shift the asseembly into the right place, after creating a hull to make one solid piece
				translate([0, 0.5, 0]) rotate([90, 0, 0]) cylinder(r = subwheelRadius(n, r) - 0.5, h=1);		//Create a first cylinder sitting inside the subwheel.
				translate([-2.5, 0, sLS + subwheelRadius(n, r) - 1]) sphere(r= 0.5, $fn=15);		//Create a small sphere to extend the hull upwards, fitting, so that you have a gradual ascent.
				translate([-10, 0, -subwheelRadius(n, r) + 1]) sphere(r=0.5, $fn=15);		//Extend the hull inwards so that you have a firm connection with the main wheel.
			}
			translate([0, 0.6, 0]) rotate([90, 0, 0]) cylinder(d=2 + 0.4 + 0.5, h=1.2, $fn=15);
		}
	}
}

//Create a set of subwheels as they would be normally positioned. Inflated = true makes them bigger; useful for creating space around the wheels.
module subwheelSet(n, r, inflated=false) {
	for(i=[0:2:n]) { 	
		if(inflated) {
			subwheelBase(n, r, i, shift = 3, split=false);									//Create a subwheel in normal, ground position.
			translate([0, 0, sLS]) subwheelBase(n, r, i+1, shift = 3, split=false);	//Create a subwheel in elevated position and shifted over by (360/n) degrees.
		}
		else {
			subwheelBase(n, r, i);
			translate([0, 0, sLS]) subwheelBase(n, r, i+1);
		}
	}
}

//Create a subwheel connector set for the according wheel of size r with n subwheels.
module connectorSet(n, r) {
	for(i=[0:2:n]) {
		subwheelConnector(n, r, i);
		subwheelConnector(n, r, i+1, true);
	}
}

//Create the center piece for the omni-wheel
module omniWheelBase(n, r, subwheels=false) {
	difference() {														
		translate([0,0, - subwheelRadius(n, r) + 0.5]) cylinder(r= r - subwheelRadius(n, r) - 2, h= sLS + 2* subwheelRadius(n, r) - 1);	//Create the central cylinder.
		subwheelSet(n, r, true);	//Create spaces for the wheels
	}
	
	connectorSet(n, r);				//Create the subwheel connectors.
	
	if(subwheels) {
		subwheelSet(n, r);
	}
}

//Refine the center piece a bit; cut it down for less plastic usage etc.
module omniWheel(n, r, subwheels=false) {
	difference() {
		translate([0,0, subwheelRadius(n, r) - 0.5]) omniWheelBase(n, r, subwheels);
		cylinder(r = r - subwheelRadius(n, r) - 2 - 4, h=sLS + 2* subwheelRadius(n, r));
	}
	intersection() {
		cylinder(r = r - subwheelRadius(n, r) - 2 - 4, h=sLS + 2* subwheelRadius(n, r));
		difference() {
			for(i=[0:90:360]) {
				rotate([0,0, i]) translate([-1, 0, 0]) cube([2, r - subwheelRadius(n, r) - 2 - 4, sLS + 2* subwheelRadius(n, r) - 1]);
			}
			translate([0,0, 3]) cylinder(r1= 5, r2= r- subwheelRadius(n, r) - 2 - 4, h= sLS + 2* subwheelRadius(n, r) - 1 - 3);
		}
	}
}

omniWheel(8, 25, true);