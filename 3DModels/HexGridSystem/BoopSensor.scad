use <../Lib/HexGrid.scad>

plateThickness = 1;
extensionDistance = 10;

hexSegment(b2 = 17.5/2 - 1, t2 = 17.5/2 -1, h = plateThickness);
translate([0, 0, -2.2]) lowerFill();

module holderPlate() {
	plateWidth = tan(30) * (17.5/2 -1) * 2; 
	plateLength = extensionDistance;
	
	translate([0, - plateWidth/2, 0]) cube([plateLength, plateWidth, plateThickness]);
}

holderPlate();