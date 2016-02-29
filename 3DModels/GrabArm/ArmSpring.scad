springLength = 20;

mntpadLength = 5;


cube([10, springLength, 1]);

cube([10, mntpadLength, 2]);
translate([0, springLength - mntpadLength, 0]) cube([10, mntpadLength, 2]);