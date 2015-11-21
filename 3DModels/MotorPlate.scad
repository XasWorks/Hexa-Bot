use <NewHexGrid.scad>

//Generate the "raw" hex base, without any modifications.
module rawBase() {
	for(i=[0:5]) rotate([0,0, 360/6*i])
	hexPattern([[1,0], [1,1], [2,0], [2,1], [2,2], [2,3], [3,0], [3,1], [3,2], [4,0]]) hex();
	
	hex();
}

//Add holes for the motors etc. 

motorWidth = 35;
motorDepth = 36;

frameSize = 1;
frameHeight = 6;

plateThickness = 1.5;

//Stabilising beams for the motor connector plate
module plateStabiliser() {
	hull() {
		translate([0.5, 0, 0]) cube(1);
		translate([-35 - frameSize*2, 0, frameHeight - 1]) cube(1);
		translate([0.5, 0, 35/2-1]) cube(1);
	}
}

//Generate the plate that holds the motor
module motorHolder() {
	//Generate the stabilising beams for the motors
	translate([0, 35/2, 0]) plateStabiliser();
	translate([0, -35/2 - 1, 0]) plateStabiliser();
	
	//Generate the actual motor mount
	translate([plateThickness, 0, 0]) rotate([0, -90, 0]) difference() {
		translate([0, -35/2, 0]) cube([35/2, 35, plateThickness]);
		
		//Make holes for the screws and the central cylinder.
		cylinder(d=25,h=plateThickness);
		for(i=[0:3]) rotate([0,0, 90*i]) translate([26/2, 26/2, 0]) cylinder(d=3.8, h=plateThickness, $fn=14);
	}	
}


//Generate a union of the motor frame, holder, and the hex structure.
module halfReadyBase() {
	render() {
		//Hex Grid base structure
		rawBase();
		
		//Generate the small outer edge of the motor holder that gives the structure more stability,
		//As well as the parts for more stability.
		for(i=[0:3]) 
			rotate([0,0, 360/3*i + 30]) 
			translate([(3.5 * 17.5) / cos(30), 0, 0]) {
				translate([ - (motorDepth + frameSize), 
							-(motorWidth + 2* frameSize)/2, 0]) 
				cube([motorDepth + frameSize, motorWidth + 2*frameSize, frameHeight]);
				
				motorHolder();
			}
	}
}
	
//Cut out spaces for the motors.
module refinement() {
	render() difference() {
		halfReadyBase();
		
		//Remove the hexGrid structure where the motors should be.
		for(i=[0:3]) 
		rotate([0,0,360/3*i + 30]) 
		translate([(3.5 * 17.5) / cos(30) - motorDepth, -motorWidth/2, -motorWidth/2]) 
		cube([motorDepth + 0.01, motorWidth, motorWidth]);
	}
}

refinement();