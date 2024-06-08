#include "../include/wonders.h"


Plateau::Plateau(){
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

            Box::getInstance().getJoueur( pion_militaire < 0 )->subTresor( saccage[0 + 2*static_cast<int>(pion_militaire < 0)] );
            saccage[0 + 2*static_cast<int>(pion_militaire < 0)] = 0 ; 

        } else if( abs(pion_militaire) >= 6 && abs(pion_militaire) <= 8 ){
            
            Box::getInstance().getJoueur( pion_militaire < 0 )->subTresor(saccage[1 + 2*static_cast<int>(pion_militaire < 0)]);
            saccage[1 + 2*static_cast<int>(pion_militaire < 0)] = 0 ;
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

const Jeton* Plateau::takeJeton(unsigned int index){

    if(index > jetons.size()-1){ throw GameException("ERREUR: Index pour récupérer le jeton invalide"); }

    /*
    auto it = std::find_if(jetons.begin(), jetons.end(), [id](const Jeton* j){
        return j->getId() == id;  
    });

    if(it == jetons.end()){ throw GameException("ERREUR: Ce jeton n'est pas sur le plateau"); }
    */

    const Jeton* j = jetons[index] ; jetons.erase(jetons.begin()+index);
    
    return j; 

}

void Plateau::displayPlateau() const {
    //std::cout << "|" ; 
    for(int i = -9 ; i <= 9 ; i++){
        if(pion_militaire == i){ std::cout << "X " ; } else { std::cout << "_ " ; }
    }
    std::cout << std::endl ;

    std::cout << "_|__" << saccage[3] << "__|__" << saccage[2] <<"__|___|_|___|__" <<  saccage [0] <<"__|__" << saccage[1] <<"__|_" << std::endl << std::endl;

    for(auto iter =jetons.begin() ; iter != jetons.end() ; ++iter){
        std::cout << **iter << " " ;
    }

    std::cout << std::endl << std::endl ;

    layout->displayLayout(); 
    
    std::cout << std::endl ; 
}

void Plateau::reinit(){
    pion_militaire = 0 ; 
    saccage[0] = 2 ; saccage[1] = 5 ; saccage[2] = 2 ; saccage[3] = 5 ;
    jetons.clear();
    layout->reinit();
}