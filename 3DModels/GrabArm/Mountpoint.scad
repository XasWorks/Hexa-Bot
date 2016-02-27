use <../Lib/HexGrid.scad>

hexPat = [	[-1, 2], [0,2], [1, 2],
			[0,1],
			[-1, 0], [0, 0], [1, 0], 
			[-1, 1]];

module mntpoint() {
	import(file = "Mountpoint.stl");
}

module base() translate([0, -10, 0]) {
	hexPattern(hexPat) {
		hexBase();
		translate([0, 0, -3.2]) hexFill();
		translate([0, 0, -2.2]) hexFill();
	}
}

 render()  intersection(){
	base();
	addition = 5;
	translate([-25/2 - addition, -16, -3.2]) cube([25 + addition, 40, 3.2]);
}

mntpoint();