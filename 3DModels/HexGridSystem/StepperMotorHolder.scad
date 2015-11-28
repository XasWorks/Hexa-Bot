use <../Lib/NewHexGrid.scad>


plateThickness = 1.5;

module mountPlate() {
	difference() {
		cube([35, 35/2, plateThickness]);
		translate([35/2, 35/2, 0]) {
			cylinder(d=25,h=plateThickness);
			for(i=[0:3]) rotate([0,0, 90*i]) translate([26/2, 26/2, 0]) cylinder(d=3.8, h=plateThickness, $fn=10);
		}
	}
}

module plateStabiliser() {
	hull() {
		translate([0,0.5, -1]) cube(1);
		translate([0,0.5, -22.5]) cube(1);
		translate([0, -15, -1]) cube(1);
	}
}

translate([-35/2, sin(60) * 17.5+ sin(30) * 17.5, 2.2]) {
	translate([0,0, -5]) {
		rotate([-90, 0, 0]) mountPlate();
		cube([35, plateThickness, 5]);
	}
	
	translate([-0.999,0,0]) plateStabiliser();
	translate([35 - 0.001, 0, 0]) plateStabiliser();
}

hexPattern([[-1,0], [0,0], [1,0], [-1,1], [0,1]]) {
	upperHex(aligned=false);
	translate([0,0, - 1.6]) middleHex(aligned=false);
}