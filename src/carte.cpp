#include "../include/wonders.h"


bool Carte::checkTypeRessources(std::list<ressource> cost_r, std::set<ressource> subset) const {
    //std::set<ressource> standard_ressources = getRessource(); 
    for(auto iter = cost_r.begin() ; iter != cost_r.end() ; ++iter ) { // list iterator 
        if( subset.find(*iter) == subset.end() ) {
            //std::cout << "WARNING : INVALID RESSOURCE LIST" << std::endl ;
            return false ; 
        }
    }
    //std::cout << "CORRECT RESSOURCE LIST" << std::endl ;
    return true ; 
} 

Carte::Carte(std::string n, type_batiment t,  phase_jeu a, std::list<ressource> c_r, unsigned int c_m, unsigned int arge, unsigned int vic):nom(n), type(t), c_age(a), argent(arge), pt_victoire(vic){

    if(c_r.size() > 5){
        throw GameException("ERREUR : trop de ressources dans le coût de la carte instanciée") ; 
    }

    cost_m = c_m ; 
    
    if(!checkTypeRessources(c_r, getRessource())){
        throw GameException("ERREUR : list de ressources invalide dans la carte instanciée (matières premières ou produits manufacturés SEULEMENT)") ;
    } 
    cost_r = c_r ;
}

void Carte::setCoutRessource(std::list<ressource> cost){
    if(checkTypeRessources(cost, getRessource()) && cost.size() <= 5) {
        cost_r = cost ; 
    } else {
        throw GameException("ERREUR : list de ressources invalide dans la carte à modifier (matières premières ou produits manufacturés SEULEMENT)") ;
    }
}


std::ostream& operator<<(std::ostream& f, const Carte& c){
    c.affichage();
    return f ; 
}

Batiment::Batiment(std::string nom, type_batiment type, phase_jeu age, std::list<ressource> cost_r, unsigned int cost_m, unsigned int argent, unsigned int pt_victoire, std::list<ressource> prod, std::string chained_by):
Carte(nom, type, age, cost_r, cost_m, argent, pt_victoire), chained_by(chained_by){
    // vérifications liées au type : 
    if(type == type_batiment::Civil && !production.empty()){
        throw GameException("ERREUR (Batiment instancié) : un bâtiment CIVIL ne produit pas de ressources");
    }
    if(type == type_batiment::Scientifique){
        if(!checkTypeRessources(prod, getSymboleScientifique())){throw GameException("ERREUR (Batiment instancié) : un bâtiment SCIENTIFIQUE ne produit que des symboles scientifiques");}
        if(prod.size() != 1){throw GameException("ERREUR (Batiment instancié) : un bâtiment SCIENTIFIQUE ne produit qu'un seul symbole");}
    }
    if(type == type_batiment::Militaire){
        if(!checkTypeRessources(prod, {ressource::Bouclier})){throw GameException("ERREUR (Batiment instancié) : un bâtiment MILITAIRE ne produit que des boucliers");}
    }
    if(type == type_batiment::Manufacture){
        if(!checkTypeRessources(prod, getProduitManufacture())){throw GameException("ERREUR (Batiment instancié) : un bâtiment de ressources GRIS ne produit que des produits manufacturés");}
    }
    if(type == type_batiment::Premiere){
        if(!checkTypeRessources(prod, getMatierePremiere())){throw GameException("ERREUR (Batiment instancié) : un bâtiment de ressources MARRON ne produit que des matièrs premières");}

    }

    production = prod ; 
}

void Carte::affichage() const {
    std::cout << nom << ", " << tostringType(type) << ", " << tostringAge(c_age) << std::endl ; 
    if(cost_m != 0){ std::cout << "COUT ARGENT: " << cost_m << std::endl ; }

    if( !getCoutRessource().empty() ){
        std::cout << "COUT RESSOURCES: " ;
        for(auto iter = getCoutRessource().begin() ; iter != getCoutRessource().end() ; ++iter) { std::cout << tostringRessources(*iter) << " ; " ; }
        std::cout << std::endl ;
    }
    if(argent != 0 || pt_victoire != 0){std::cout<< "REWARDS: ";}
    if(argent != 0) {std::cout << argent << " pièces ; " ; }
    if(pt_victoire != 0){std::cout << pt_victoire << " points victoire" ;}
    if(argent != 0 || pt_victoire != 0){std::cout << std::endl;}
}

void Batiment::affichage() const {
    Carte::affichage();
    if(!production.empty()){
        std::cout << "PRODUCTION: " ;
        displayRessources( production ) ;
    }
    std::cout << std::endl ; 
}

void Batiment::onBuild(Joueur& j) const {
    //std::cout << "CALLING ONBUILD BATIMENT" << std::endl ;
    j.addTresor( this->getRewardArgent() );
    return ; 
}

Commerce::Commerce(
    std::string nom, type_batiment type, phase_jeu age, 
    std::list<ressource> cost_r, unsigned int cost, 
    unsigned int argent, unsigned int pt_victoire, std::list<ressource> prod, 
    std::string chained_by, const Perk* perk):
        Batiment(nom, type,age, cost_r, cost, argent, pt_victoire, prod, chained_by), perk(perk) {

            if( type != type_batiment::Commerce && type != type_batiment::Merveille ){ throw GameException("ERREUR : instanciation d'un bâtiment non Commerce avec la classe Commerce");}
            // comme le constructeur de Commerce est appelé pour construire Merveille
            // we need to allow the Commerce constructor to create Merveille types

}

Commerce::~Commerce() { if(perk!=nullptr){delete perk ;} }

void Commerce::onBuild(Joueur& j) const {
    //std::cout << "CALLING ONBUILD COMMERCE" << std::endl ;
    j.addTresor( this->getRewardArgent() );
    if(perk!=nullptr){
        perk->onCall(j); 
    }
}

Guilde::Guilde(
    std::string nom, type_batiment type, phase_jeu age,
    std::list<ressource> cost_r, unsigned int cost,
    unsigned int argent, unsigned int pt_victoire,

    std::list<type_batiment> affectation, bool usurier):
    Carte(nom, type, age,cost_r, cost, argent, pt_victoire),affectation(affectation), usurier(usurier){
        if( type != type_batiment::Guilde ){ throw GameException("ERREUR: Utilisation du constructeur de Guilde avec un type_batiment invalide");}
}

unsigned int Guilde::ptVictoireFinJeu(const Joueur* j) const {

    if( usurier ){ return std::max(j->getTresor()/3, j->getAdversaire().getTresor()/3) ;}

    unsigned int p[2] = {0, 0} ;
    const Joueur* jp[2] = {j, &j->getAdversaire()};

    for(size_t i = 0 ; i < 1 ; i++){
        for( auto iter = affectation.begin() ; iter != affectation.end() ; ++iter ){
            p[i] += jp[i]->getNumberBatiment(*iter);
        }
    }

    return std::max(p[0], p[1]) ;

}

void Guilde::rewardArgent(Joueur& j) const {

    unsigned int p[2] = {0, 0} ;
    Joueur* jp[2] = {&j, &j.getAdversaire()};

    for(size_t i = 0 ; i < 1 ; i++){
        for( auto iter = affectation.begin() ; iter != affectation.end() ; ++iter ){
            p[i] += jp[i]->getNumberBatiment(*iter) * getRewardArgent() ;
        }
    }

    j.addTresor( std::max(p[0], p[1]) );
}

void Guilde::onBuild(Joueur& j) const {
    //std::cout << "CALLING ONBUILD GUILDE" << std::endl ;
    if(!usurier) rewardArgent(j);
}