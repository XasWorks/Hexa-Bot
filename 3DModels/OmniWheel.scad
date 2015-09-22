/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for the robot.
	
	Author 	= Xasin
	Created	= 17.09.15
*/

use <Transforms.scad>

function subwheelRadius(n, r) = r - cos(360/(2*n))*r + 2.5;		//Calculate the radius of a standard subwheel at largest point (Center)
function wheelOffset(n, r) = cos(360/(2*n))*r;						//Calculate the offset of a subwheel that is required to shift it so that it aligns with the main circle (CAUTION Does not implement subwheel size shift!!)
function sliceSlitOffset(n, r) = (sin(360/(2*n))*r);					//Calculate the offset for the cuts on the wheels. (Y axis on the 2D model of a subwheel before being rotated.
	
$fs = 2.1;

module subwheelBase(n, r=20, p=0, shift = 2.5, split=true, positioned=true) {  //The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
	
	//Position the wheel according to the given parameters (Aling it to the outside of the main wheel and rotate it around into position p.)
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
	//Generate a standard subwheel without moving it around.
	else {
		render(convexity=4) difference() {				//Render the subwheel and make it hollow.
			union() {
				rotate_extrude() difference() {		//Generate the main subwheel
					intersection() {					//2D Model for the basic subwheel
						translate([ - wheelOffset(n, r) + shift, 0]) circle(r=r, $fn = 70);		//Main circle	
						translate([0, - sin(360/(2*n))*r]) square(sin(360/(2*n))*r *2);			//Intersecting square to only have the desired part of the circle
					}								
					offset(r= -0.8)  intersection() { //Shift this model inwards 0.8mm and remove it, generating a hollow wheel. (Less filament used.)
						translate([ - wheelOffset(n, r) + shift, 0]) circle(r=r, $fn = 70);
						translate([0, - sin(360/(2*n))*r]) square(sin(360/(2*n))*r *2);
					}
						
				}
				translate([0, 0, - sin(360/(2*n))*r]) cylinder(r=shift, h= sin(360/(2*n))*r *2);	//Central cylinder inside for the axis.
			}
			
			if(split) {
				translate([0,0,-(sin(360/(2*n))*r)]) cylinder(d=2 + 0.4 + 0.1, h= 2* sin(360/(2*n))*r,$fn=15);	//Slot for the Filament-Axis, semi-tight
				translate([0,0, -0.625]) cylinder(r= r - wheelOffset(n, r) + 0.1 + shift, h=1.3); //Split for the connectors for the wheels to fit in.
			}
		}
	}
}

sLS = 8;

//Create a connecting beam for the subwheels
module subwheelConnector(n, r, i, flipped=false) {
	if(flipped) {		//Flip it around so that you have a connector for the upper layer of subwheels.
		translate([0,0, sLS]) rotate([180,0, (360/n)*i]) subwheelConnector(n, r, 0);
	}
	else {
		render(convexity= 3) 
		rotate([0,0, (360/n)*i]) translate([wheelOffset(n, r) - 2.5, 0, 0]) difference() {
			hull() {		//Shift the asseembly into the right place, after creating a hull to make one solid piece
				translate([0, 0.5, 0]) rotate([90, 0, 0]) cylinder(r = subwheelRadius(n, r) - 0.5, h=1);		//Create a first cylinder sitting inside the subwheel.
				translate([-5, 0, sLS + subwheelRadius(n, r) - 1]) sphere(r= 0.5, $fn=15);		//Create a small sphere to extend the hull upwards, fitting, so that you have a gradual ascent.
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
			subwheelBase(n, r, i, shift = 3, split=false);									//Create a /bigger/ subwheel in normal, ground position.
			translate([0, 0, sLS]) subwheelBase(n, r, i+1, shift = 3, split=false);			//Create a subwheel in elevated position and shifted over by (360/n) degrees.
		}
		else {
			subwheelBase(n, r, i);									//Do the same as above, however using default subwheels instead of bigger subwheels here.
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
		translate([0,0, - subwheelRadius(n, r) + 0.5]) difference() {
			cylinder(r= r - subwheelRadius(n, r) - 5, h= sLS + 2* subwheelRadius(n, r) - 1);	//Create the central cylinder.
			cylinder(r=  r - subwheelRadius(n, r) - 5 - 0.8, h=sLS + 2* subwheelRadius(n, r) - 1);	//Cut out this cylinder (to reduce filament usage) 
		}
		
		subwheelSet(n, r, true);	//Create spaces for the wheels
	}
	
	connectorSet(n, r);				//Create the subwheel connectors.
	
	if(subwheels) {					//If desired, create subwheels around the model for a better visual inspection.
		subwheelSet(n, r);
	}
}

//Refine the center piece a bit; cut it down for less plastic usage etc.
module omniWheel(n, r, subwheels=false) {
	difference() {
		translate([0,0, subwheelRadius(n, r) - 0.5]) omniWheelBase(n, r, subwheels);			//Create a omniwheel Center piece and shift it up to make it fit flat on the ground.
		cylinder(r = r - subwheelRadius(n, r) - 0.8 - 5, h=sLS + 2* subwheelRadius(n, r));	//Cut out the inside of the subwheel, leaving a 0.8mm wall.
	}
	
	//Generate the structural beams.
	intersection() {
		cylinder(r = r - subwheelRadius(n, r) - 0.8 - 5, h=sLS + 2* subwheelRadius(n, r));	//Cut everything so that it fits into the main cylinder without "poking out".
		difference() {
			for(i=[0:360/n:360]) {		//Generate the basis of the strucural beams,
				rotate([0,0, i]) translate([0, -0.4, 0]) cube([r - subwheelRadius(n, r) - 4, 0.8, sLS + 2* subwheelRadius(n, r) - 1]);
			}
			
			translate([0,0, (sLS + 2* subwheelRadius(n, r) - 1)/2 + 1]) cylinder(r1= 2.5, r2= r- subwheelRadius(n, r) - 3 - 4, h= (sLS + 2* subwheelRadius(n, r) - 1)/2 -1);		//Cut the top part of the structural beams down to make a nice looking gradual ascent (and to aswell conserve filament.)
			cylinder(r1= r- subwheelRadius(n, r) - 3 - 4, r2= 2.5, h= (sLS + 2* subwheelRadius(n, r) - 1)/2 -1 );		//Same as above, except cutting out the bottom part.
		}
	}
	
	cylinder(r=2.5, h= (sLS + 2* subwheelRadius(n, r) - 1) , $fn = 6);		//Generate a central cylinder; Later has to be replaced by a connecting module.
}

!for(i=[0:5]) translate([i* (subwheelRadius(6, 25) * 2 + 1), 0, 0]) intersection() {
		subwheelBase(6, 25, positioned=false);
		cylinder(r=10, h= 50);
	}

omniWheel(6, 25);