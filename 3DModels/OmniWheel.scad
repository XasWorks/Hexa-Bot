/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for the robot.
	
	Author 	= Xasin
	Created	= 17.09.15
*/

use <Transforms.scad>

function wheelOffset(n, r) = cos(360/(2*n))*r;
function sliceSlitOffset(n, r) = (sin(360/(2*n))*r);

$fs = 2.1;

module subwheelBase(n, r=20) {											//The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
	difference() {
		render(convexity = 4) rotate_extrude() intersection() {
			translate([ - wheelOffset(n, r) + 4, 0]) circle(r=r);
			translate([0, - sin(360/(2*n))*r]) square(sin(360/(2*n))*r *2);
		}
		
		translate([0,0,-(sin(360/(2*n))*r)]) cylinder(d=2 + 0.4 + 0.4, h= 2* sin(360/(2*n))*r,$fn=15);				//Slot for the Filament-Axis, loose
	}
}

module inflatedSubwheel(n, r) {
	render(convexity = 4) minkowski() {
		subwheelBase(n, r);
		sphere(r=2);
	}
}
	
module connectorBeam(n, r) {
	render(convexity=3) difference() {
		union() {
			cylinder(r= 3, h= 1.4, $fn=13);								//Outer cylinder for the axis connector
			translate([0, -3, 0]) cube([wheelOffset(n, r), 6, 1.4]);	//Connector beam
		}
		cylinder(d= 3, h= 1.4, $fn=10);										//Slot for the filament axis
	}
}

//Creates the two 5mm beams that connect the filament axis with the actual wheel for a omniwheel of N Subwheels with radius R.
module subwheelConnector(n, r) {
	translate([wheelOffset(n, r), 0, 0]) rotate([-90,180,0]) {					//Translate the outer connectors to the right position (wheel Offset) and rotate them around for fitting position.
		translate([0, 0, sliceSlitOffset(n, r) + 0.1]) {							//Translate the upper slot and connector beam.
			connectorBeam(n, r);
		}
		
		translate([0, 0, -sliceSlitOffset(n, r) - 1.4 - 0.1]) {						//Translate the lower slot and connector beam.
			connectorBeam(n, r);
		}
	}
}

//Create the center piece for the omni-wheel
module omniWheel(n, r, subwheels=false, skip=2) {
	for(i=[0:(360/n)*skip:360]) {									//Create the connector beams
		rotate([0,0,i]) subwheelConnector(n, r);
	}
	
	difference() {														//Create the central cylinder.
		translate([0,0, -3]) cylinder(r= r - 4, h=6);
		
		for(i=[0:(360/n)*skip:360]) {
			rotate([-90,0, i]) translate([wheelOffset(n, r), 0, 0]) render(convexity=3) inflatedSubwheel(n, r);
		}
	}
	
	if(subwheels) for(i=[0:(360/n)*skip:360]) {
		rotate([-90,0,i]) translate([wheelOffset(n, r), 0, 0]) subwheelBase(n, r);
	}
}

!omniWheel(6, 25, true);