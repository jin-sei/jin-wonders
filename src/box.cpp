#include "../include/wonders.h"


Box::Box(){

    plateau = new Plateau(this);

    std::string nom; 
    std::cout << "Joueur-0 : Nom > " ; 
    std::cin >> nom ; 
    joueur0 = new Joueur(0, nom) ; 
    std::cout << "Joueur-1 : Nom > " ; 
    std::cin >> nom ;
    std::cout << std::endl ; 
    joueur1 = new Joueur(1, nom) ; 

    joueur0->setAdversaire(joueur1); 
    joueur1->setAdversaire(joueur0);
    current = joueur0 ; 
    
    phase = phase_jeu::END ;

    allCardsCreation();

}

Box::~Box(){

    delete plateau ; 
    delete joueur0 ; 
    delete joueur1 ; 

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
        // commencer les tours de jeu
        return ;

    } else if( phase == phase_jeu::AGE_III ){
        // fin de jeu ; comptage des points, détermination du gagant
        ++phase;
        
        // CHECK VICTOIRE MILITAIRE
        if( plateau->victoireMilitaire() ){
            std::cout << "SUPRÉMATIE MILITAIRE DU JOUEUR " << plateau->joueurDominant() << std::endl ; 
            return ;
        } else if ( joueur0->victoireScientifique() || joueur1->victoireScientifique() ){
            std::cout << "SUPRÉMATIE SCIENTIFIQUE DU JOUEUR " << static_cast<int>(joueur1->victoireScientifique()) << std::endl ;
            return ;
        }
        
        // CHECK VICTOIRE SCIENTIFIQUE

        // COMPTAGE DE POINTS
        unsigned int pt_j0 = joueur0->fetchPtVictoire(false) + plateau->pointsVictoire() * static_cast<int>(plateau->joueurDominant() == 0), 
        pt_j1 = joueur1->fetchPtVictoire(false) + plateau->pointsVictoire() * static_cast<int>(plateau->joueurDominant() == 1) ;
        
        if( pt_j0 == pt_j1 ){
            
            pt_j0 = joueur0->fetchPtVictoire(true) ; pt_j1 = joueur1->fetchPtVictoire(true); 
            
            if( pt_j0 == pt_j1 ){
                std::cout << "ÉGALITÉ ABSOLUE" << std::endl ; 
            } else {
                std::cout << "LE JOUEUR " << static_cast<int>(pt_j0 < pt_j1) << " EST VICTORIEUX" << std::endl;
            }
        } else {
            std::cout << "LE JOUEUR " << static_cast<int>(pt_j0 < pt_j1) << " EST VICTORIEUX" << std::endl; 
        }

        return ; 

    } else if ( phase == phase_jeu::END ){

        ++phase ; 
        // début d'une nouvelle partie
        reinitAll();
        setupAll();
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
    phase = phase_jeu::START ; 
    plateau->reinit();
    joueur0->reinit();
    joueur1->reinit();
    unused_jetons.clear();
    defausse.clear();
}

void Box::choixMerveilles(){
    // requires player interaction
    std::vector<const Merveille*> temp = all_merveilles ;
    std::vector<const Merveille*> selection(4) ; 
    unsigned int choice = 0 ;

    std::random_device rd ; std::mt19937 gen(rd());
    std::shuffle(temp.begin(), temp.end(), gen);

    std::cout << "Désigner le joueur qui commence:" << std::endl << std::endl ; 
    choice = askJoueur({joueur0->getNom(), joueur1->getNom()});
    current = getJoueur(choice) ;

    for(int i = 0 ; i <= 5 ; i++){

        if(i == 0 || i == 3){
            selection.resize(4);
            std::copy(temp.begin(), temp.begin()+4, selection.begin());
            temp.erase(temp.begin(), temp.begin()+4);
        }

        std::cout << "#. Joueur " << current->getId() << " (" << current->getNom() << "):" << std::endl << std::endl ;
        choice = chooseFromPointerVector(selection) ;
        current->addMerveille( selection[ choice ] ) ;
        selection.erase(selection.begin() + choice) ; 

        if(i == 0 || i == 3){
            current = current->getAdversaire(); 
        }

        if( selection.size() == 1 ){
            std::cout << current->getAdversaire()->getNom() << " gets " << selection[0]->getNom() << std::endl << std::endl ;
            current->getAdversaire()->addMerveille(selection[0]);
            selection.clear();
        }

    }

}

void Box::setupJetons(){

    if( all_jetons.size() != 10 ){ throw GameException("ERREUR: instanciation des Jetons failed"); }
    
    std::random_device rd ; std::mt19937 gen(rd());
    std::shuffle(all_jetons.begin(), all_jetons.end(), gen);

    for(size_t i = 0 ; i < 10 ; i++){
        if( i < 5 ){ plateau->addJeton( all_jetons[i] );}
        else { this->unused_jetons.push_back( all_jetons[i] );}
    }

}

void Box::setupAll(){
    setupJetons();
    choixMerveilles();
    joueur0->setTresor(7) ; joueur1->setTresor(7) ; 
}