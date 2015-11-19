use <NewHexGrid.scad>

//Generate the "raw" hex base, without any modifications.
module rawBase() {
	render() for(i=[0:5]) rotate([0,0, 360/6*i])
	hexPattern([[0,0], [1,0], [1,1], [2,0], [2,1], [2,2], [2,3], [3,0], [3,1], [3,2], [4,0]]) hex();
}

//Add holes for the motors etc. 

motorWidth = 35;
motorDepth = 36;

frameSize = 1;
frameHeight = 6;

module refinedBase() {
	render() difference() {
		union() {
			rawBase();
			
			for(i=[0:3]) rotate([0,0, 360/3*i + 30]) translate([(3.5 * 17.5) / cos(30) - (motorDepth + frameSize), -(motorWidth + 2* frameSize)/2, 0]) cube([motorDepth + frameSize, motorWidth + 2*frameSize, frameHeight]);
		}
		for(i=[0:3])
			#rotate([0,0,360/3*i + 30]) translate([(3.5 * 17.5) / cos(30) - motorDepth, -motorWidth/2, -motorWidth/2]) cube([motorDepth, motorWidth, motorWidth]);
	}
}

refinedBase();