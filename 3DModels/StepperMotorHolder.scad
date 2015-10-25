use <HexGrid.scad>


plateThickness = 1.5;

difference() {
	union() {
		translate([-10 + plateThickness,0, -35/2 - 5 + 2.5]) rotate([0, -90, 0]) difference() {
			translate([0, -35/2, 0]) cube([35/2 + 5,35,plateThickness]);
			cylinder(d=25,h=plateThickness);
			for(i=[0:3]) rotate([0,0, 90*i]) translate([26/2, 26/2, 0]) cylinder(d=3.8, h=plateThickness, $fn=10);
		}
		
		translate([-10, -35/2 - 1, 1.5]) hull() {
			cube(1);
			translate([10,0,0]) cube(1);
			translate([0,0, -21.6]) cube(1);
		}
		
		translate([-10, 35/2, 1.5]) hull() {
			cube(1);
			translate([10,0,0]) cube(1);
			translate([0,0, -21.6]) cube(1);
		}
	}
	
	translate([10, -sin(60)*20, -1.3]) minkowski() {
		hexGrid(1,3, true, false);
		cylinder(r=0.15,h=1.6);
	}
}

translate([10, -sin(60)*20, 0]) difference() {
	translate([0,0, -2.5 - 1.6 ]) hexGrid(1,3, true, false);
	translate([-50, -50, -6.6]) cube([100, 100, 5]);
}