use <../Lib/HexGrid.scad>

plateThickness = 2;
extensionDistance = 30;

module holderPlate() {
	
		rotate([0, 0, 30]) {
	hexSegment(b2 = 17.5/2 - 1, t2 = 17.5/2 -1, h = plateThickness);
translate([0, 0, -2.2]) lowerFill();
		}
	
	plateWidth = tan(30) * (17.5/2 -1) * 2; 
	plateLength = extensionDistance - 1.5;
	
	translate([0, - plateWidth/2, 0]) cube([plateLength, plateWidth, plateThickness]);
	
	translate([extensionDistance, 0, 0]) 
	rotate([0, 0, 90])
	mounterPlate();
}

module mounterPlate() {
	holeDistance = 20;
	extraBrim = 5;
	$fn = 10;
	
	difference() {
		union() {
			hull() {
				translate([- holeDistance/2, 0, 0]) cylinder(d = 3 + extraBrim/2, h= plateThickness);
				
				translate([holeDistance/2, 0, 0]) cylinder(d = 3 + extraBrim/2, h= plateThickness);
			}
				rotate([180, 0, 0]) {
					translate([- holeDistance/2, 0, 0]) cylinder(d = 3 + extraBrim/2, h= plateThickness + 1.5);
				
					translate([holeDistance/2, 0, 0]) cylinder(d = 3 + extraBrim/2, h= plateThickness + 1.5);
				}
		}
			
		translate([-holeDistance/2, 0, -5]) cylinder(d = 3, h= 10);
		translate([holeDistance/2, 0, -5]) cylinder(d = 3, h= 10);
	}
}

rotate([180, 0, 0]) holderPlate();