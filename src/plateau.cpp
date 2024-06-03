#include "../include/wonders.h"


Plateau::Plateau(Box* box):box(box){
    this->layout = new Layout() ; 
}

Plateau::~Plateau(){
    delete layout ; 
}

void Plateau::movePion(bool id, unsigned int avance){
    // 0 | 1 ; 2 | 3 ; 4 ; 5 | 6 ; 7 ; 8 | 9 

    int a ;
    if(!id){ a = -avance ;} else { a = avance ; }

    if( pion_militaire + a <= -9){

        pion_militaire = -9 ; // victoire Joueur 0
        return ;

    } else if( pion_militaire + a >= 9){

        pion_militaire = 9 ; // victoire Joueur 1
        return ; 

    } else {

        pion_militaire += a;

        if( abs(pion_militaire) >= 3 && abs(pion_militaire) <= 5 ){

            box->getJoueur( pion_militaire < 0 )->subTresor( saccage[0 + 2*static_cast<int>(pion_militaire < 0)] );
            saccage[0 + 2*static_cast<int>(pion_militaire < 0)] = 0 ; 

        } else if( abs(pion_militaire) >= 6 && abs(pion_militaire) <= 8 ){
            
            box->getJoueur( pion_militaire < 0 )->subTresor(saccage[1 + 2*static_cast<int>(pion_militaire < 0)]);
            saccage[0 + 2*static_cast<int>(pion_militaire < 0)] = 0 ;
        }

        return;

    }


}

unsigned int Plateau::pointsVictoire() const {

    if( abs(pion_militaire) >= 1 && abs(pion_militaire) <= 2 ){

        return 2 ; 

    } else if( abs(pion_militaire) >= 3 && abs(pion_militaire) <= 5 ){

        return 5 ;

    } else if( abs(pion_militaire) >= 6 && abs(pion_militaire) <= 8 ){

        return 10 ; 

    }

    return 0 ; 
}