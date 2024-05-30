#include "../include/wonders.h"


Plateau::Plateau(){
    this->layout = new Layout() ; 
}

Plateau::~Plateau(){
    delete layout ; 
}