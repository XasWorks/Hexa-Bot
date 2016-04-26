module sInput(type) {
	linear_extrude(height = 0.01) {
		wall = 0.6;
	
		sSpaceX = 22 - wall * 2;
		sSpaceY = 7;
		
		if(type == "OUTER") 
			translate([-sSpaceX/2 - wall, -sSpaceY/2 - wall]) square([sSpaceX + wall*2, sSpaceY + wall*2]);
		else if(type == "INNER")
			translate([-sSpaceX/2, -sSpaceY/2]) square([sSpaceX, sSpaceY]);
	}
}

module sOutput(type) {
		linear_extrude(height = 0.01) {
		wall = 0.6;
		
		radius = 8; 
		
		if(type == "INNER")
			circle(r = radius);
		else if(type == "OUTER")
			circle(r = radius + wall);
	}
}

module shell() {
	sHeight = 10;
	
	difference() {
		hull() {
			sInput("OUTER");
			translate([0, 0, sHeight]) sOutput("OUTER");
		}
		
		hull() {
			sInput("INNER");
			translate([0, 0, sHeight]) sOutput("INNER");
		}
	}
}

module cPlate() {
	shiftUp = 4.1;
	
	sizeX = 22;
	sizeY = 13;
	
	$fn = 9;
	
	difference() {
		hull() {
			translate([sizeX/2 - 3, sizeY - 3, 0]) cylinder(r = 3, h = 1);
			translate([-sizeX/2 + 3, sizeY - 3, 0]) cylinder(r = 3, h = 1);
			
			translate([-sizeX/2, shiftUp, 0]) cube([sizeX, 0.1, 1]);
		}
		translate([sizeX/2 - 3, sizeY - 3, 0]) cylinder(r = 1.5, h = 1);
		translate([-sizeX/2 + 3, sizeY - 3, 0]) cylinder(r = 1.5, h = 1);
	}
}

cPlate();
shell();