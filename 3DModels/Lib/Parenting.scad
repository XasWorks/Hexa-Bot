

module parentBy(node) {
  rotate([0, 0, node[1][2]])
  rotate([node[1][0], node[1][1], 0])
  translate(node[0]) {
    children();
  }
}
