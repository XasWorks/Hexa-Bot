use <../Lib/NewHexGrid.scad>

mountYPos = 17.5/2 - 3;
		
module base() {
	difference() {
		union() {
			hexPattern([[0,0], [1, 0], [-1, 0]]) {	
				hexFill();
				lowerHex();
					
				translate([0, mountYPos, 0]) 
				cylinder(d = 3.1 + 1.6, h= 6, $fn= 20);
			}
			translate([0, 0, 2.2]) children();
		}
		
		hexPattern([[0,0], [1, 0], [-1, 0]]) translate([0, mountYPos, -0.1]) 
 		cylinder(d = 3.1, h= 10, $fn= 20);
	}
}
	
	

			
//translate([0, mountYPos, -0.1]) 
//cylinder(d = 3.1, h= 10, $fn= 20);
//translate([0, 0, 2.2]) children();

module connectingBeam() {
	beamWidth = 3 * 17.5 - 2;
	beamHeight = (tan(30) * (17.5/2 -1)) * 2;
	beamThickness = 0.5;
	
	translate([ -beamWidth /2, -beamHeight /2, 0])
	cube([beamWidth, beamHeight, beamThickness]);
}

base()
connectingBeam();