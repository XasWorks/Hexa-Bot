use <../Lib/HexGrid.scad> 

module connectorPiece() {
	upperHex(aligned=false);
	translate([0,0, 2.2]) upperHex(aligned=false);
}

module base() {
	for(i=[0:5]) rotate([0,0, 360/6*i])
	hexPattern([[1,0], [1,1], [2,0], [2,1], [2,2], [2,3], [3,0], [3,1], [3,2], [4,0]]) connectorPiece();

	connectorPiece();
}

base();
