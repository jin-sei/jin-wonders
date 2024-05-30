#include "../include/wonders.h"


Box::Box(){

    plateau = new Plateau();

    joueur1 = new Joueur() ; joueur2 = new Joueur() ; 
    joueur1->setAdversaire(joueur2); 
    joueur2->setAdversaire(joueur1);
    
    phase = phase_jeu::START ;

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

void Box::allCardsCreation(){

    // 23 cartes Âge I
    // 23 cartes Âge II
    // 20 cartes Âge III
    // 7 cartes Guilde
    // 12 cartes Merveille

    // MOCK CARDS TO TEST THE GAME : TO BE REMOVED 
    phase_jeu p = phase_jeu::AGE_I ;

    for(size_t i = 0 ; i < 66 ; i++){

        if( i < 23 ){ p = phase_jeu::AGE_I ; } 
        else if ( i < 46 ){ p = phase_jeu::AGE_II ;  } 
        else if ( i < 66 ){ p = phase_jeu::AGE_III ; }

        Batiment* new_bat = new Batiment("Bâtiment Civil "+std::to_string(i+1), type_batiment::Civil, p);
        all_batiments.push_front(new_bat);

    }

}

void Box::displayAllCards(){

    for( auto iter = all_batiments.begin() ; iter != all_batiments.end() ; ++iter){
        
        std::cout << **iter << std::endl ;

    }

}

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

    std::vector<Carte*> temp ; // stocker les cartes âge 

    for( auto iter = all_batiments.begin() ; iter != all_batiments.end() ; ++iter ){

        //std::cout << tostringAge((**iter).getAge()) << std::endl ;
        if( (**iter).getAge() == p ){ temp.push_back(*iter); }

    }

    std::random_device rd ; std::mt19937 gen(rd());

    std::shuffle(temp.begin(), temp.end(), gen) ; 

    // on enlève 3 cartes sur 23 pour atteindre 20 cartes 
    temp.pop_back() ;
    temp.pop_back() ; 
    temp.pop_back() ;

     if( p == phase_jeu::AGE_III ){
        // ajouter les guildes
        // shuffle again (?)
    }

    this->plateau->getLayout()->inputCards( temp ) ;

    /** CHECK IF SHUFFLE WORKS
    for( auto iter = temp.begin() ; iter != temp.end() ; ++iter ){
        std::cout << tostringAge((**iter).getAge()) << std::endl ; 
    }
    */

    return ; 

}
