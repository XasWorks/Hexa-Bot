use <../Lib/Parenting.scad>
use <../Lib/HexGrid.scad>

//function linearSegmet(start, end, v1, v2) = if($t < start) v1 else if($t > end) v2 else (($t - start) / (end - start)) * (v2 -v1) + v1;
function linearSegmet(start, end, v1, v2) = ($t < start) ? (v1) : ( ($t > end) ? v2 : ( (($t - start) / (end - start)) * (v2 -v1) + v1 ));
function linearLift(start, end, v1, v2) = [[0, 0, linearSegmet(start, end, v1, v2)], 0];
function segmentedLift(n, i, v1, v2) = linearLift(i/n, (i+1)/n, v1, v2);

module electronicsMount() color("Orange"){
  translate([17.5/2, 0, 2.2 + 1]) import(file = "../STL/ControllerHolder.stl");
}

module basePlate() color("YellowGreen") {
  import(file = "../STL/BasePlate.stl");
}

top_layer_node = [[0, 0, 30 - 2.2], [0, 0, 0]];
module distancerModules() color("orange") {
  translate([0, 0, -3.8])
  for (i = [0:5]) {
    rotate([0, 0, 60*i])
    parentBy(hexNode([4, 0]))
    import(file = "../STL/Distancer.stl");
  }
}

module LF_Sensor() color("Orange") {
  translate([0, 0, -13 + 2.2]) import(file = "../STL/LF-Senor-Mount.stl");
}

module motorPlate() color("YellowGreen") {
  translate([0, 0, 6]) rotate([180, 0, 0]) import(file = "../STL/MotorPlate.stl");
}

splitDistance = $t * 4;

//Node for the robot's ground position
ground_node = [[0, 0, 0], [0, 0, 0]];

//Additional node for animation distancing
split_node = [[0, 0, splitDistance], [0, 0, 0]];

totalSegments = 3;

$vpr = [70, 0, linearSegmet(0, 1, 120, -5)];

parentBy(ground_node) {

  motorPlate();

  parentBy(hexNode([3, 1]) + linearLift(0, 0.3, 100, 0) ) LF_Sensor();
  parentBy(hexNode([2, 3]) + linearLift(0, 0.3, 100, 0) ) LF_Sensor();

  parentBy(hexNode([0,0])) {
    parentBy(linearLift(0.1, 0.4, 100, 0)) distancerModules();

    parentBy(top_layer_node) {
      parentBy(linearLift(0.2, 0.5, 100, 0)) basePlate();

      parentBy(hexNode([-1, -3], 2.2) + linearLift(0.3, 0.6, 100, 0)) electronicsMount();
    }
  }
}
