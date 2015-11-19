use <NewHexGrid.scad>

module rawBase() {
	render() for(i=[0:5]) rotate([0,0, 360/6*i])
	hexPattern([[0,0], [1,0], [1,1], [2,0], [2,1], [2,2], [2,3], [3,0], [3,1], [3,2], [4,0]]) hex();
}

module refinedBase() {
	for(i=[0:3]) {
		rotate([0,0,360/3*i + 30]) translate([sin(60)*4*17.5 + sin(60)*17.5/2 - 36, -35/2, 0]) cube([36, 35, 35]);
	}
}

rawBase();
refinedBase();