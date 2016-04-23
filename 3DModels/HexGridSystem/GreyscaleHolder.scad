use <../Lib/HexGrid.scad>

holder_distance = 8;


lowerFill();
translate([0, 0, -holder_distance]) difference() {
	$fn = 10;
	cylinder(r = 1.5 + 1.2, h = holder_distance);
	cylinder(r = 1.5 + 0.2, h = holder_distance);
}