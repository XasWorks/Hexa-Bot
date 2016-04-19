

Subspace::Subspace(Movable *destination) {
  this->desitnation = destination;

  this->xOrig = destination->getX();
  this->yOrig = destination->getY();
  this->rOrig = destination->getR();
}
