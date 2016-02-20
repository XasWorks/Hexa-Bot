use <../../Lib/HexGrid.scad>

module base() {
	hexPattern([	[-2, 1], [-1, 1], [0, 1], [1, 1],
								[-2,0], [-1,0], [0,0], [1, 0], [2,0]]) {
		translate([0, 0, -3.2]) hexFill();
		translate([0, 0, -1]) hexSegment(17.5/2 - 1, 17.5/2 -1, h = 1);
	}
}

module bHolder() {
	import(file="BHolder.stl");
}

bHolder();
base();
