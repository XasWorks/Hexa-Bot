/*
	.scad file created for the subwheel system of the 3D Printable Omni-Wheels used for a robot.
	
	
	Author 	= Xasin
	Website = https://www.github.com/xasin/hexa-bot.git
	Created	= 17.09.15
*/

use <../Lib/Transforms.scad>

function subwheelRadius(n, r) = r - cos(360/(2*n) + subwheelOverlap)*r + subwheelBaseSize;		//Calculate the radius of a standard subwheel at largest point (Center)
function wheelOffset(n, r) = cos(360/(2*n) + subwheelOverlap)*r;						//Calculate the offset of a subwheel that is required to shift it so that it aligns with the main circle (CAUTION Does not implement subwheel size shift!!)
function connectorOffset(n, r) = (sin(360/(2*n) + subwheelOverlap)*r);					//Calculate the offset for the cuts on the wheels. (Y axis on the 2D model of a subwheel before being rotated.
	
$fs = 0.5;

//What to generate - 1 means base frame, 2 means subwheel piece
generate = 1;

//GENERATION VARIABLES 
num = 10*$t*2;	//Number of all subwheels to create. (Has to be a round number!!)
radius = 35;	//Radius of the omni-wheel.

//SUBWHEEL VARIABLES
subwheelBaseSize = 4;	//Size of the subwheels at their smallest point (The edge)
subwheelPlay = 0.5; 		//The additional size that will be cut out around the subwheels to ensure smooth movement
subwheelOverlap = 1;		//Angle in which the subwheel pieces will overlap. Causes smoother movement as there is no definite edge.

//AXIS HOLE VARIABLE
axisDiameter = 1.75;
axisPlay = 0.45;

//SUBWHEEL CONNECTOR VARIABLES
cRad = axisDiameter/2 + 1.5; 	//Radius of the connectors to the subwheels (Best is slightly smaller than the subwheel.
cThick = 1.5; 					//Thickness of the connectors.
cPlay = 0.1; 					//Play room for the connector ports (distance to the subwheel)

//FRAME VARIABLES
frameRadius = connectorOffset(num, radius) + cPlay + cThick;		//Radius of the frame Cylinder
frameHeight = cRad + subwheelRadius(num, radius);
frameThickness = 0.8;		//Thickness of the main frame

//STABILITY BEAM VARIABLES
beamThickness = 4; 		//Thickness of the stability beams
beamNum = 7;

//CONNECTOR VARIABLES
connectorThickness = 1.3;	//Thickness of the vertical connectors
connectorInShift = 0.2;		//Inwards shift of the vertical connector beams (for smoother connection)
connectorHeight = 2.5;		//Height of the connector pieces above the main frame.

module subwheelBase(n, r=20, p=0, shift = subwheelBaseSize, split=true, positioned=true) {  //The base structure of a Subwheel, basically a slice of a circle of the radius of the wheel, cut down to be rotated into a proper subwheel for a wheel of Radius R with N Subwheels.
	
	//Position the wheel according to the given parameters (Aling it to the outside of the main wheel and rotate it around into position p.)
	render(4) if(positioned) {
		//Rotate to the according outside position.
		rotate([0, 0, (360/n) * p])
		//Translate to the edge of the circle
		translate([ wheelOffset(n, r) - subwheelBaseSize, 0, 0])
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
						translate([0, - sin(360/(2*n) + subwheelOverlap)*r]) square(sin(360/(2*n) + subwheelOverlap)*r *2);			//Intersecting square to only have the desired part of the circle
					}	
						
				}
			}
			
			if(split) {
				translate([0,0,-(sin(360/(2*n) + subwheelOverlap)*r)]) cylinder(d= axisDiameter + axisPlay*2, h= 2* sin(360/(2*n) + subwheelOverlap)*r,$fn=15);	//Slot for the Filament-Axis, rolling
			}
		}
	}
}

//Create the connecting beams for the subwheels
module subwheelConnector(n, r, i) {
	render(convexity = 3)
	rotate([0,0, (360/n)*i]) 
	difference() {				//The difference cuts the hole for the axis into the connectors
		intersection() {		//The intersection makes sure that the subwheel connectors don't poke outside of the wheel radius. This should not be nececary, but for smaller subwheel base sizes might be desirable.
			union() {		//The cylinders here are the end cylinders on either side of the connector, the cubes are the beams that connect those cylinders to the main frame.
				translate([wheelOffset(n, r) - subwheelBaseSize, connectorOffset(n, r) + cPlay + cThick]) rotate([90, 0, 0]) cylinder(r= cRad, h= cThick, $fn = 13);		
				
				translate([0, connectorOffset(n, r) + cPlay, -cRad]) 
					cube([wheelOffset(n, r) - subwheelBaseSize, cThick, cRad*2]);
				
				translate([wheelOffset(n, r) - subwheelBaseSize, -connectorOffset(n, r) - cPlay]) rotate([90, 0, 0]) cylinder(r= cRad, h= cThick, $fn = 13);
						
				translate([0, -connectorOffset(n, r) - cPlay - cThick, -cRad]) 
					cube([wheelOffset(n, r) - subwheelBaseSize, cThick, cRad*2]);
			}
			
			//Intersection Cylinder to make sure that the beams do not interfere with smooth rotation of the wheel.
			translate([0,0, -cRad]) cylinder(r=r - 0.3, h= cRad*2);
		}
		
		//Create the hole for the filament axis to go through
		translate([wheelOffset(n, r) - subwheelBaseSize, connectorOffset(n, r) + 5, 0]) rotate([90,0,0]) cylinder(d= axisDiameter + 0.38, h= connectorOffset(n, r)*2 + 10, $fn=14);
	}
}

module connectorStrengthener(n, r, i) {
	rotate([0,0, 360/n * i]) translate([0,0, -cRad]) intersection() {
		cylinder(r=sqrt(pow(connectorOffset(n, r),2) + pow(wheelOffset(n, r) - subwheelBaseSize, 2)) + 0.6, h=0.8, $fn=75);
		translate([0,connectorOffset(n, r) + cPlay,0]) cube([r, r, 0.8]);
		rotate([0,0, 360/n*2]) translate([0,-(connectorOffset(n,r) + cPlay + r), 0]) cube([r,r, 0.8]);
	}
}

//Create a set of subwheels as they would be normally positioned. Inflated = true makes them bigger; useful for creating space around the wheels.
module subwheelSet(n, r, inflated=false) {
	for(i=[0:2:n]) { 	
		if(inflated) {		
			subwheelBase(n, r, i, shift = subwheelBaseSize + subwheelPlay, split=false);									//Create a /bigger/ subwheel in normal, ground position.
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
		connectorStrengthener(n, r, i);
	}
}

//Create the central cylinder piece.
module centralCylinder(n, r) {
	render(convexity = 4) translate([0,0, - cRad]) difference() {
		cylinder(r= frameRadius, h= frameHeight);		//Create the central cylinder.
		cylinder(r= frameRadius - frameThickness, h= frameHeight);	//Hollow it out
	}
}
		
//Create the pieces that connect the two Omniwheel pieces together
module interconnectorPiece(n, r) {
	difference() {
		shine(height= frameHeight + connectorHeight, angle=(360/n) - 0.5, length= r)
		//"Shine" is a custom function that cuts down an object to a specific angle
		union() {
			cylinder(r= frameRadius - 0.1, h= frameHeight);		//Cylinder piece to connect the connector to the main frame.
			cylinder(r= frameRadius - frameThickness - connectorInShift, h= frameHeight + connectorHeight);		//Cylinder piece for the actual interconnector. This one is slightly smaller due to printing imperfections, thusly making sure that the pieces fit together nicely.
		}
		cylinder(r= frameRadius - frameThickness - connectorThickness - connectorInShift, h= frameHeight + connectorHeight);		//Hollow the interconnection pieces out so that they have the correct thickness.
		
	}
}

//Create the interconnections between two wheel pieces
module interconnections(n, r) {
	render(convexity= 2) translate([0,0, -cRad])
		for(i=[0:(360/(n/2)):360]) 
			rotate([0,0, i + 360/n])											
			interconnectorPiece(n, r);	
}

//Create the structural beams inside the subwheel for better stability.
module structuralBeams() {
	render(convexity = 4) translate([0,0, -cRad]) intersection() {
		cylinder(r= frameRadius, h= cRad*2);		//Make sure that the structural beams don't poke out of the main frame.
		
		for(i=[0:360/beamNum:360]) 
			rotate([0,0, i + 360/beamNum/2]) translate([0, -beamThickness/2, 0]) cube([frameRadius, beamThickness, 2]);		//Create the beams.
	}
}

//The Mainframe of the OmniWheel
module omniWheel(n, r, subwheels = false) {
	difference() {  union() {
			//Central Cylinder 
			centralCylinder(n, r);
			
			//Cylinder Interconnections

			interconnections(n, r);

			//Structural beams
			structuralBeams();
			
			//Connectors
			render(convexity = 5) difference() {
				connectorSet(n, r);			//Create the connectors
				translate([0,0, -cRad]) cylinder(r= frameRadius - 0.001, h= frameHeight); //Make sure they don't enter the central cylinder
			}
			
			//Generate the cylinder for the stepper motor axis
			translate([0,0,-cRad])
				cylinder(d= 5 + 4, h= frameHeight);
				
		}
		
		//Generate the hole for the axis, as well as the edge to fix the wheel on the axis
		rotate([0,0, 360/(n*2)]) translate([0,0, -cRad]) difference() {
			cylinder(d= 5.2, h= frameHeight);
			translate([ 2.5 - 0.48, -(5 + 0.4)/2, 0]) cube([ (5 + 0.4) / 2, 5 + 0.4, frameHeight]);
		}
		
		subwheelSet(n, r, true); 	//Make sure that there is enough space for the subwheels.
	}
	
	%subwheelSet(n, r);		//Create subwheels around the model for a better visual inspection.
}

if(generate == 1) {
	omniWheel(num, radius, true);
}
else if(generate == 2) { 
	subwheelBase(num, radius, positioned=false);
}