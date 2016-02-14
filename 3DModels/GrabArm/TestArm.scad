use <../Lib/AnglePieces.scad>

cThickness = 0.8;
cAngleThickness = 1.5;

cOuterRadius = 5;
cInnerRadius = 2;
movementAngle = 45;


consProfile = [cOuterRadius, cInnerRadius, cAngleThickness, movementAngle];

$fs = 0.3;

module outerArmConSide() {
	difference() {
		union() {
			cylinder(r=cOuterRadius, h=cThickness, center = true);
			translate([- cOuterRadius, 0, -cThickness /2]) cube([cOuterRadius *2, cOuterRadius, cThickness]);
		}
		cylinder(d = 1.75, h = cThickness, center = true);
	}
}

module conInnerPiece() {
	translate([0, 0, - cAngleThickness/2])
	connectorLeft(consProfile);
}

module conFemalePiece() {
	translate([0, 0, - cAngleThickness/2 - cThickness /2])
		outerArmConSide();
	translate([0, 0, + cAngleThickness/2 + cThickness /2])
		outerArmConSide();
	conInnerPiece();
}

module conMalePiece() {
	rotate([0, 0, 180])
	conInnerPiece();

	difference() {
		cylinder(r=cInnerRadius, h=cAngleThickness, center=true);
		cylinder(d=1.75, h=cAngleThickness, center=true);
	}
}

module conMaleRodPiece() {
	rodWidth = cos(movementAngle / 4) * cOuterRadius * 2;
	rodLength = 20;
	rodThickness = cAngleThickness;

	rotate([0, 0, 180])
	translate([ sin(movementAngle / 4) * cOuterRadius, - rodWidth /2 , -cAngleThickness/2]) cube([rodLength, rodWidth, rodThickness]);
}

module maleConnector() translate([0, 0, cAngleThickness/2]) {
	conMaleRodPiece();
	conMalePiece();
}

module femaleConnector() {
	translate([0, 0, cOuterRadius])
	rotate([-90, 0, 0])
	conFemalePiece();
}

translate([0, 10, 0])
maleConnector();
femaleConnector();
