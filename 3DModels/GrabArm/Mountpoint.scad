use <../Lib/HexGrid.scad>

hexPat = [	[-1, 2], [0,2], [1, 2],
			[0,1],
			[-1, 0], [0, 0], [1, 0], 
			[-1, 1]];

module mntpoint() {
	import(file = "Mountpoint.stl");
}

module base() translate([0, -10, 0]) {
	hexPattern(hexPat) hexBase();
}

 render()  intersection(){
	base();
	translate([0, 0, -3.2]) mntpoint();
}

mntpoint();