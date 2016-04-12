use <../Lib/HexGrid.scad>

// Board variables
boardSize = [46.6, 30];

boardPins = [ 	[0, 10], [0, 23.3], [0, 46],
				[1, 13], [1, 19], 
				[3, 1], [3, 11], [3, 23]];

// Mounting pin variables
liftHeight = 2;
wallSize = 1;

module board_base() {
	baseThickness = 1;
	baseWallSize = 2;
	
	boardSize = boardSize + [wallSize*2, wallSize*2];
	
	difference() {
		square([boardSize[0], boardSize[1]]);
		translate([baseWallSize, baseWallSize]) square([boardSize[0] - baseWallSize*2, boardSize[1] - baseWallSize*2]);
	}
}

module board_mountPin(width = 1) {
	translate([width, 0, 0]) rotate([0, 0, 90]) {
		cube([wallSize*2, width, liftHeight]);
		cube([wallSize, width, liftHeight + wallSize]);
	}
}

module board_placedMountPin(side, distance, pinWidth = 1) {
	boardSize = boardSize + [wallSize*2, wallSize*2];
	
	if(side == 0)
		translate([distance, 0, 0]) board_mountPin(pinWidth);
	else if(side == 1) 
		translate([boardSize[0], 0, 0]) rotate([0, 0, 90]) board_placedMountPin(0, distance, pinWidth);
	else if(side == 2) 
		translate([boardSize[0], boardSize[1], 0]) rotate([0, 0, 180]) board_placedMountPin(0, distance, pinWidth);
	else if(side == 3) 
		translate([0, boardSize[1], 0]) rotate([0, 0, -90]) board_placedMountPin(0, distance, pinWidth);
}

module board_mounts() {
	for(i=[0:len(boardPins) -1]) board_placedMountPin(boardPins[i][0], boardPins[i][1]);
}

module hex_base() {
	render()
		translate([-2, 0, 0]) hexPattern([[0,0], [1,0], [2,0], [3,0], 
				[0,1], [1,1], [2,1], 
				[0,2], [1,2], [2,2], [3,2]]) hexBase();
}

linear_extrude(1) board_base();
hex_base();
board_mounts();