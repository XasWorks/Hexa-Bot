use <../Lib/HexGrid.scad>

mountYPos = 17.5/2 - 3;
		

//cylinderHeight = 13;
//cylinderHeight = 10;
cylinderHeight = 5;
		
module base() render() {
	difference() {
		union() {
			hexPattern([[0,0], [1, 0], [-1, 0]]) {	
				hexFill();
				lowerHex();
				translate([0, 0, 2.2]) 
				hexSegment(b2 = 17.5/2 - 1, t2 = 17.5/2 -1, h = 1);
	
				
				translate([0, mountYPos, 0]) 
				cylinder(d = 3.1 + 1.6, h= cylinderHeight, $fn= 20);
			}
			
			translate([0, 0, 3.2]) children();
		}
		
		hexPattern([[0,0], [1, 0], [-1, 0]]) translate([0, mountYPos, -0.1]) 
 		cylinder(d = 3.05, h= 30, $fn= 20);
	}
}
	

module connectingBeam() {
	beamWidth = 3 * 17.5 - 2;
	beamHeight = (tan(30) * (17.5/2 -1)) * 2;
	beamThickness = 1;
	
	translate([ -beamWidth /2, -beamHeight /2, 0])
	cube([beamWidth, beamHeight, beamThickness]);
}

base()
connectingBeam();