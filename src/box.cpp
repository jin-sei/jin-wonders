#include "../include/wonders.h"


Box::Box(){

    plateau = new Plateau(this);

    joueur1 = new Joueur(0) ; joueur2 = new Joueur(1) ; 
    joueur1->setAdversaire(joueur2); 
    joueur2->setAdversaire(joueur1);
    current = joueur1 ; 
    
    phase = phase_jeu::START ;

    allCardsCreation();

}

Box::~Box(){

    delete plateau ; 
    delete joueur1 ; 
    delete joueur2 ; 

    for( auto iter=all_batiments.begin() ; iter != all_batiments.end() ; ++iter ){
        delete *iter ; 
    }

    for( auto iter=all_merveilles.begin() ; iter != all_merveilles.end() ; ++iter ){
        delete *iter ; 
    }

    for( auto iter=all_jetons.begin() ; iter != all_jetons.end() ; ++iter ){
        delete *iter ; 
    }

}

/*
void Box::displayAllCards(){

    for( auto iter = all_batiments.begin() ; iter != all_batiments.end() ; ++iter){
        
        std::cout << **iter << std::endl ;

    }
}
*/

void Box::newAge(){

    if(phase == phase_jeu::START || phase == phase_jeu::AGE_I || phase == phase_jeu::AGE_II){

        ++phase ;
        plateau->getLayout()->switchAge(phase); // SWITCH AGE CLEAR LES CARTES DE LAYOUT
        distributeCards(phase);
        return ;

    } else if( phase == phase_jeu::AGE_III ){

        ++phase; 
        // fin de jeu ; 
        return ; 

    } else if ( phase == phase_jeu::END ){

        ++phase ; 
        // début d'une nouvelle partie
        return; 

    } else { throw GameException("ERREUR : âge inconnu");}

}

void Box::distributeCards(phase_jeu p){

    // CHOISIR 20 CARTES DE L'ÂGE CORRESPONDANT 
    // AJOUTER LES GUILDES POUR L'ÂGE III
    // MÉLANGER
    // AJOUTER DANS LE LAYOUT

    std::vector<const Carte*> temp ; // stocker les cartes âge 

    for( auto iter = all_batiments.begin() ; iter != all_batiments.end() ; ++iter ){

        //std::cout << tostringAge((**iter).getAge()) << std::endl ;
        if( (**iter).getAge() == p ){ temp.push_back(*iter); }
        // le vector cards de Layout est vide après avoir appelé Layout::SwitchAge dans Box::newAge

    }

    std::random_device rd ; std::mt19937 gen(rd());

    std::shuffle(temp.begin(), temp.end(), gen) ; 

    // on enlève 3 cartes sur 23 pour atteindre 20 cartes 
    temp.pop_back() ;
    temp.pop_back() ; 
    temp.pop_back() ;

     if( p == phase_jeu::AGE_III ){
        std::shuffle(all_guildes.begin(), all_guildes.end(), gen);
        temp.push_back( all_guildes[0] );
        temp.push_back( all_guildes[1] );
        temp.push_back( all_guildes[2] );
        std::shuffle(temp.begin(), temp.end(), gen);
    }

    this->plateau->getLayout()->inputCards( temp ) ;

    /** CHECK IF SHUFFLE WORKS
    for( auto iter = temp.begin() ; iter != temp.end() ; ++iter ){
        std::cout << tostringAge((**iter).getAge()) << std::endl ; 
    }
    */

    return ; 

}

void Box::reinitAll(){
    plateau->reinit();
    joueur1->reinit();
    joueur2->reinit();
}