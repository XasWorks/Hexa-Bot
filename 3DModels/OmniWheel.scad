/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for the robot.
	
	Author 	= Xasin
	Created	= 17.09.15
*/

use <Transforms.scad>

function subwheelRadius(n, r) = r - cos(360/(2*n))*r + subwheelBaseSize;		//Calculate the radius of a standard subwheel at largest point (Center)
function wheelOffset(n, r) = cos(360/(2*n))*r;						//Calculate the offset of a subwheel that is required to shift it so that it aligns with the main circle (CAUTION Does not implement subwheel size shift!!)
function connectorOffset(n, r) = (sin(360/(2*n))*r);					//Calculate the offset for the cuts on the wheels. (Y axis on the 2D model of a subwheel before being rotated.
	
$fs = 1;

//AXIS HOLE VARIABLE
axisDiameter = 1.75;
axisPlay = 0.4;


subwheelBaseSize = 3.5;

module subwheelBase(n, r=20, p=0, shift = subwheelBaseSize, split=true, positioned=true) {  //The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
	
	//Position the wheel according to the given parameters (Aling it to the outside of the main wheel and rotate it around into position p.)
	render(4) if(positioned) {
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
						
				}
				translate([0, 0, - sin(360/(2*n))*r]) cylinder(r=shift, h= sin(360/(2*n))*r *2);	//Central cylinder inside for the axis.
			}
			
			if(split) {
				translate([0,0,-(sin(360/(2*n))*r)]) cylinder(d= axisDiameter + axisPlay, h= 2* sin(360/(2*n))*r,$fn=15);	//Slot for the Filament-Axis, rolling
			}
		}
	}
}

//OMNIWHEEL BASE VARIABLES
cRad = axisDiameter/2 + 1.5; 	//Radius of the connectors to the subwheels (Best is slightly smaller than the subwheel.
cThick = 0.8; 	//Thickness of the connectors.
cPlay = 0.3; 	//Play room for the connector ports (distance to the subwheel)

//Create a connecting beam for the subwheels
module subwheelConnector(n, r, i) {
	rotate([0,0, (360/n)*i]) 
	difference() {
		intersection() {
			union() {
				translate([wheelOffset(n, r) - subwheelBaseSize, connectorOffset(n, r) + cPlay + cThick]) rotate([90, 0, 0]) cylinder(r= cRad, h= cThick, $fn = 13);
				
				translate([0, connectorOffset(n, r) + cPlay, -cRad]) 
					cube([wheelOffset(n, r) - subwheelBaseSize, cThick, cRad*2]);
				
				translate([wheelOffset(n, r) - subwheelBaseSize, -connectorOffset(n, r) - cPlay]) rotate([90, 0, 0]) cylinder(r= cRad, h= cThick, $fn = 13);
						
				translate([0, -connectorOffset(n, r) - cPlay - cThick, -cRad]) 
					cube([wheelOffset(n, r) - subwheelBaseSize, cThick, cRad*2]);
			}
			
			translate([0,0, -cRad]) cylinder(r=r - 0.3, h= cRad*2);
		}
		
		translate([wheelOffset(n, r) - subwheelBaseSize, connectorOffset(n, r) + 5, 0]) rotate([90,0,0]) cylinder(d= axisDiameter + 0.3, h= connectorOffset(n, r)*2 + 10, $fn=14);
	}
}

//Create a set of subwheels as they would be normally positioned. Inflated = true makes them bigger; useful for creating space around the wheels.
module subwheelSet(n, r, inflated=false) {
	for(i=[0:2:n]) { 	
		if(inflated) {		
			subwheelBase(n, r, i, shift = subwheelBaseSize + 0.5, split=false);									//Create a /bigger/ subwheel in normal, ground position.
		}
		else {
			subwheelBase(n, r, i);									//Do the same as above, however using default subwheels instead of bigger subwheels here.
		}
	}
}

//Create a subwheel connector set for the according wheel of size r with n subwheels.
module connectorSet(n, r) {
	for(i=[0:2:n]) {
		subwheelConnector(n, r, i);
	}
}

//FRAME VARIABLES
frameThickness = 1;
connectorThickness = 1;
beamThickness = 2.5; //Thickness of the beams

//The Mainframe of the OmniWheel
module omniWheel(n, r, subwheels = false) {
	
	//Central Cylinder 
	translate([0,0, - cRad]) difference() {
		cylinder(r= connectorOffset(n, r) + cPlay + cThick, h= cRad + subwheelRadius(n, r));		//Create the central cylinder.
		cylinder(r= connectorOffset(n, r) + cPlay + cThick- frameThickness, h= cRad + subwheelRadius(n, r));	//Hollow it out
		subwheelSet(n, r, true); 	//Make sure that there is enough space for the subwheels.
	}
	
	//Cylinder Interconnections
	translate([0,0, -cRad]) difference() {
		for(i=[0:(360/n)*2:360]) 
			rotate([0,0, i])
			shine(height= cRad + subwheelRadius(n, r) + 3, angle=(360/n) - 0.5, length= r)					//Create an "angle" for the connectors to create an alternating, tooth-like pattern.
			cylinder(r= connectorOffset(n, r) + cPlay + cThick - frameThickness, h= cRad + subwheelRadius(n, r) + 3);	//Create the actual cylinder pieces.
		
		cylinder(r= connectorOffset(n, r) + cPlay + cThick - frameThickness - connectorThickness, h= cRad + subwheelRadius(n, r) + 3);	//Cut the connectors down the appropriate size.
	}

	//Structural beams
	translate([0,0, -cRad]) intersection() {
		cylinder(r= connectorOffset(n, r) + cPlay, h= cRad*2);
		
		for(i=[0:360/n*2:360]) 
			rotate([0,0, i]) translate([0, -beamThickness/2, 0]) cube([r -  subwheelRadius(n, r) - 6, beamThickness, 1]);
	}	
	
	//Connectors
	difference() {
		connectorSet(n, r);			//Create the connectors
		translate([0,0, -cRad]) cylinder(r= connectorOffset(n, r) + cPlay - 0.001, h= cRad + subwheelRadius(n, r)); //Make sure they don't enter the central cylinder
	}
	
	
	if(subwheels) {					//If desired, create subwheels around the model for a better visual inspection.
		%subwheelSet(n, r);
	}
}

rad = 30;
num = 8;

!omniWheel(num, rad, true);

for(i=[0:1]) translate([i* subwheelRadius(num, rad)*2 + 2*i, 0, 0]) subwheelBase(num, rad, positioned=false);