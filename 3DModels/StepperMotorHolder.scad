use <HexGrid.scad>


plateThickness = 3.5;

difference() {
	translate([plateThickness,0, -35/2 - 2.5]) rotate([0, -90, 0]) difference() {
		translate([-35/2, -35/2, 0]) cube([40,35,plateThickness]);
		cylinder(d=24,h=plateThickness);
		for(i=[0:3]) rotate([0,0, 90*i]) translate([26/2, 26/2, 0]) cylinder(d=3.5, h=plateThickness, $fn=10);
	}
	
	translate([10, -sin(60)*20, 0]) difference() {
		hexGrid(1,3, true, false);
	}
}

translate([10, -sin(60)*20, 0]) difference() {
	translate([0,0, -2.5 - 1.6 ]) hexGrid(1,3, true, false);
	translate([-50, -50, -6.6]) cube([100, 100, 5]);
}