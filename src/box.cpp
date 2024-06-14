#include "../include/wonders.h"

//Box::Handler Box::shell=Box::Handler();
bool Box::constructed = false;  // One instance to rule them all, One instance to find them, One instance to bring them all, and in the darkness bind them
std::vector<const Jeton*> Jeton::instances = {} ; 

/*
const Box& Box::getInstance(){
    if( shell.box == nullptr ){ shell.box = new Box ; }
    return *shell.box ; 
}
*/

Box::Box(){

    if(constructed){
        throw GameException("ERREUR: Already constructed");
    }
    constructed = true; 

    plateau = new Plateau();

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

    constructed = false ; 

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

void Box::construireCarte(Joueur& j, const Carte& c){ // MOVING TO BOX
    // gère l'appliquation des effets et l'ajout à la cité
    // ne gère pas le coût, la possibilité d'obtention
    j << c ;
    c.onBuild(j);

    switch(c.getType()){

        case type_batiment::Militaire :
            // avancement du Pion
        {
            const Batiment* b = dynamic_cast<const Batiment*>(&c);
            if(b==nullptr){ throw GameException("ERREUR: downcasting to Batiment militaire failed"); } 

            plateau->movePion( getCurrentJoueur().getId(), b->getProduction().size() );

            if( abs(plateau->pion_militaire) >= 3 && abs(plateau->pion_militaire) <= 5 ){

                getJoueur( plateau->pion_militaire < 0 )->subTresor( plateau->saccage[0 + 2*static_cast<int>(plateau->pion_militaire < 0)] );
                plateau->saccage[0 + 2*static_cast<int>(plateau->pion_militaire < 0)] = 0 ; 

            } else if( abs(plateau->pion_militaire) >= 6 && abs(plateau->pion_militaire) <= 8 ){
                
                getJoueur( plateau->pion_militaire < 0 )->subTresor(plateau->saccage[1 + 2*static_cast<int>(plateau->pion_militaire < 0)]);
                plateau->saccage[1 + 2*static_cast<int>(plateau->pion_militaire < 0)] = 0 ;
            }

            if(getPlateau()->victoireMilitaire()){ endgame();}
        }

        case type_batiment::Scientifique :
            // gestion d'un nouveau Jeton
            if(j.allowJetonPick()){ // nouveau jeton possible

                const Jeton& jet = plateau->takeJeton( askJoueur(plateau->getJetons()) );
                j.addJeton( jet ) ;
                if( jet.getId() == jeton_progres::Agriculture ){j.addTresor(4);}

            }

            if( j.victoireScientifique() ){ endgame();}
    }

}

void Box::newAge(){

    if(phase == phase_jeu::START || phase == phase_jeu::AGE_I || phase == phase_jeu::AGE_II){

        ++phase ;
        plateau->getLayout()->switchAge(phase); // SWITCH AGE CLEAR LES CARTES DE LAYOUT
        distributeCards(phase);
        gameLoop(); // retour aux tours de jeu
        return ;

    } else if( phase == phase_jeu::AGE_III ){
        // fin de jeu ; comptage des points, détermination du gagant
        ++phase;
        
        // CHECK VICTOIRE MILITAIRE
        if( plateau->victoireMilitaire() ){
            std::cout << "SUPRÉMATIE MILITAIRE DU JOUEUR " << plateau->joueurDominant() << std::endl ; 
            //return ;
        } else if ( joueur0->victoireScientifique() || joueur1->victoireScientifique() ){
            std::cout << "SUPRÉMATIE SCIENTIFIQUE DU JOUEUR " << static_cast<int>(joueur1->victoireScientifique()) << std::endl ;
            //return ;
        } else {

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
        }

        std::cout << std::endl << "Relancer une partie ?" << std::endl ; 
        unsigned int choice = askJoueur(std::vector({"Oui", "Non"}));
        if(!choice){ newAge(); } else { std::cout << "Aurevoir!" << std::endl ; exit(0); }


        return ; 

    } else if ( phase == phase_jeu::END ){

        ++phase ; 
        // début d'une nouvelle partie
        reinitAll();
        setupAll();
        newAge(); 

    } else { throw GameException("ERREUR : âge inconnu");}

}

void Box::gameLoop(){

    unsigned int choice_card = 0;
    unsigned int choice_action = 0;
    std::vector<std::string> choices = {};
    bool replay = false ; 
    if(phase != phase_jeu::AGE_I){

        if(plateau->getPionMilitaire() == 0){
            std::cout << current->getNom() ;
        } else {
            std::cout << getJoueur( plateau->joueurDominant() )->getNom() ;
        }
        std::cout << " choisis le joueur qui prendra la main: " << std::endl << std::endl ;
        current = getJoueur(askJoueur(std::vector({joueur0->getNom(), joueur1->getNom()})));

    }

    while( !plateau->getLayout()->isEmpty() ){

        waitForInteraction();
        //system("clear");

        choices = {"Défausser"}; 
        replay = false ; 
        plateau->displayPlateau();
        current->displayJoueur(); std::cout << std::endl ; 

        std::cout  << "#. Tour de " << current->getNom() << ": " << std::endl << std::endl ;
        choice_card = askJoueur( plateau->getLayout()->getVisibleCards(true) );
        
        const Carte& c = *plateau->getLayout()->getVisibleCards(true)[choice_card];
        if( current->obtainable(c) ){ choices.push_back("Construire la Carte"); }
        if (current->buildableMerveilles().size()!=0 && (current->getNumberActiveMerveilles()+current->getAdversaire().getNumberActiveMerveilles() < 7)){ choices.push_back("Construire une Merveille"); }
        std::cout << "#. Carte choisie: " << c.getNom() << std::endl << std::endl; 
        choice_action = askJoueur(choices);

        if( choices[choice_action] == "Défausser" ){

            // DÉFAUSSER

            defausse.push_back( &plateau->getLayout()->removeCard( plateau->getLayout()->availableToAll(choice_card) ));
            current->addTresor( 2+current->getNumberBatiment(type_batiment::Commerce) );

        } else if ( choices[choice_action] == "Construire la Carte" ){ // CONSTRUIRE LA CARTE

            plateau->getLayout()->removeCard( plateau->getLayout()->availableToAll(choice_card) );

            if( c.getType() != type_batiment::Guilde ){

                const Batiment* b = dynamic_cast<const Batiment*>(&c);
                if(!b){ throw GameException("ERREUR: dynamic cast failed to downcast to Batiment");}
                
                else { 
                    if( current->possessBatiment(b->getChainage())){
                        // le bâtiment est obtenu gratuitement
                        if(current->possessJeton(jeton_progres::Urbanisme)){ current->addTresor(4); }
                    } else {
                        // le bâtiment est obtenu en payant
                        current->subTresor( current->achetableJoueur(c)+c.getCoutArgent() );
                        if(current->getAdversaire().possessJeton(jeton_progres::Economie)){ 
                            current->getAdversaire().addTresor(current->achetableJoueur(c));
                        }
                    }
                }

            }

            construireCarte(*current, c);

        } else if( choices[choice_action] == "Construire une Merveille" ){ // CONSTRUIRE UNE MERVEILLE

            const Merveille* m = current->buildableMerveilles()[ askJoueur( current->buildableMerveilles() ) ];
            std::cout << "#. Merveille choisie: " << m->getNom() << std::endl << std::endl ;

            current->subTresor( current->achetableJoueur(*m)+m->getCoutArgent() );
            current->activateMerveille(*m);

            if(m->getPerk() != nullptr){ m->getPerk()->onCall(*current); } // apply perks

            current->addTresor( m->getRewardArgent() ); // gain money

            if(m->getReplay() || current->possessJeton(jeton_progres::Theologie)){ // replay
                replay = true ; 
            }
            if(!m->getProduction().empty() && m->getProduction().front() == ressource::Bouclier){ // military advance
                plateau->movePion(current->getId(), m->getProduction().size());
            }

            // 7 Merveilles, pas une de plus
            if(current->getNumberActiveMerveilles()+current->getAdversaire().getNumberActiveMerveilles() >= 7){
                if(current->getNumberActiveMerveilles() == 4){
                    current->getAdversaire().deleteLastMerveille();
                } else {
                    current->deleteLastMerveille();
                }
            }

        } else { // DEFUAULT 
            throw GameException("ERREUR: Choix invalide dans Box::gameLoop()");
        }
        if(!replay) { switchCurrent();}
    }

    newAge();
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

    plateau->getLayout()->inputCards( temp ) ;

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

    std::cout << "#. Désigner le joueur qui commence:" << std::endl << std::endl ; 
    choice = askJoueur(std::vector({joueur0->getNom(), joueur1->getNom()}));
    current = getJoueur(choice) ;

    for(int i = 0 ; i <= 5 ; i++){

        if(i == 0 || i == 3){
            selection.resize(4);
            std::copy(temp.begin(), temp.begin()+4, selection.begin());
            temp.erase(temp.begin(), temp.begin()+4);
        }

        std::cout << "#. Joueur " << current->getId() << " (" << current->getNom() << "):" << std::endl << std::endl ;
        choice = askJoueur(selection) ;
        current->addMerveille( *selection[ choice ] ) ;
        selection.erase(selection.begin() + choice) ; 

        if(i == 0 || i == 3){
            switchCurrent(); 
        }

        if( selection.size() == 1 ){
            std::cout << current->getAdversaire().getNom() << " gets " << selection[0]->getNom() << std::endl << std::endl ;
            current->getAdversaire().addMerveille( *selection[0] );
            selection.clear();
        }

    }

}

void Box::setupJetons(){

    if( all_jetons.size() != 10 ){ throw GameException("ERREUR: instanciation des Jetons failed"); }
    
    std::random_device rd ; std::mt19937 gen(rd());
    std::shuffle(all_jetons.begin(), all_jetons.end(), gen);

    for(size_t i = 0 ; i < 10 ; i++){
        if( i < 5 ){ plateau->addJeton( *all_jetons[i] );}
        else { unused_jetons.push_back( all_jetons[i] );}
    }

}

void Box::setupAll(){
    setupJetons();
    choixMerveilles();
    joueur0->setTresor(7) ; joueur1->setTresor(7) ; 
}