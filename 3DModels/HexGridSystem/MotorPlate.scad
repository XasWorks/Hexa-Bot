use <NewHexGrid.scad>


//Generate the "raw" hex base, without any modifications.
module rawBase() {
	for(i=[0:5]) rotate([0,0, 360/6*i])
	hexPattern([[1,0], [1,1], [2,0], [2,1], [2,2], [2,3], [3,0], [3,1], [3,2], [4,0]]) hex();
	
	hex();
}

//Size of the motor
motorWidth = 35;
motorDepth = 36;

//Distance of the screw holes to each other
screwHoleDistance = 26;
motorDistancerSize = 25;

//Size of the frame around it.
frameSize = 1;
frameHeight = 6;

//Thickness of the motor mount plate.
plateThickness = 1.5;

//Stabilising beams for the motor connector plate
module mountStabiliser() {
	hull() {
		translate([0.5, 0, 0]) cube(1);
		translate([-motorWidth - frameSize*2, 0, frameHeight - 1]) cube(1);
		translate([0.5, 0, motorWidth/2-1]) cube(1);
	}
}

//Generate the plate that holds the motor
module motorMount() {
	//Generate the stabilising beams for the motors
	translate([0, motorWidth/2, 0]) mountStabiliser();
	translate([0, -motorWidth/2 - 1, 0]) mountStabiliser();
	
	//Generate the motor mount
	translate([plateThickness, 0, 0]) rotate([0, -90, 0]) difference() {
		//Actual mount plate
		translate([0, -motorWidth/2, 0]) cube([motorWidth/2, motorWidth, plateThickness]);
		
		//Motor Distancer
		cylinder(d=motorDistancerSize, h=plateThickness);
		
		//Screw holes
		for(i=[0:3]) 
		rotate([0,0, 90*i])
		translate([screwHoleDistance/2, screwHoleDistance/2, 0]) 
		cylinder(d=3.8, h=plateThickness, $fn=14);
	}	
}


//Generate a union of the motor frame, holder, and the hex structure.
module halfReadyBase() {
	render() {
		
		//Hex Grid base structure
		rawBase();
		
		//Add in the frame cube (it will be cut out later, as well as the motor mounting structure.
		//Generate and rotate this setup three times.
		for(i=[0:3]) rotate([0,0, 360/3*i + 30]) 
			//Translate it out to the edge of the structure
			translate([(3.5 * 17.5) / cos(30), 0, 0]) {
				//Generate the cube for the frame
				translate([ - (motorDepth + frameSize), 
							-(motorWidth + 2* frameSize)/2, 0]) 
				cube([motorDepth + frameSize, motorWidth + 2*frameSize, frameHeight]);
				
				//Add the motor Mounts.
				motorMount();
			}
	}
}
	
//Cut out spaces for the motors.
module refinement() {
	render() difference() {
		halfReadyBase();
		
		//Clear out spaces for the motors
		//Generate it three times, rotate it to the right angle, and translate it to the edge of the piece
		for(i=[0:3]) rotate([0,0,360/3*i + 30]) 
		translate([(3.5 * 17.5) / cos(30) - motorDepth, -motorWidth/2, -motorWidth/2]) 
		//Generate the cube for the motors
		cube([motorDepth + 0.01, motorWidth, motorWidth]);
	}
}

refinement();