#include "wonders.h"

/*
bool Perk::isPolyRes() {
    if(Perk_PolyRessource* p = dynamic_cast<Perk_PolyRessource*>(this)){
        return true ; 
    } else { return false ;}
}
*/

void Perk_CoinPerCard::gainCoinPerCard(Joueur* j) const {
    j->addTresor( j->getNumberBatiment(this->card)*coin );
}

void Perk_CoinPerCard::onCall(Joueur* j) const {
    gainCoinPerCard(j);
}

void Perk_FixedTrade::setFixedTrade(Joueur* j) const {
    for(auto iter = res.begin() ; iter != res.end() ; ++iter){
        j->setFixedTrade(*iter, coin);
    }
}

void Perk_FixedTrade::onCall(Joueur* j) const {
    setFixedTrade(j);
}

Perk_Classic::Perk_Classic(unsigned int id, const Box* box):id(id), box(box){
    if(id > 2){
        throw GameException("ERREUR: Classic Perk id is 0 - 1 - 2");
    }
    if(box == nullptr){
        throw GameException("ERREUR: Un pointeur vers Box non nul est requis pour une Perk Classic");
    }
}

void Perk_Classic::saccage(Joueur* j) const {
    j->getAdversaire()->subTresor(3);
}

void Perk_Classic::freeConstructionFromDefausse(Joueur* j) const { 
    // requires player interaction
    if(box->getDefausse().empty()){std::cout << "#. Pas de carte défaussée à construire" << std::endl << std::endl ; return ;}

    std::cout << "#. Choisissez une carte de la défausse à construire:" << std::endl << std::endl ;
    const Carte* c = box->getDefausse()[ chooseFromPointerVector( box->getDefausse() ) ];
    std::cout << "#. Carte choisie: " << c->getNom() << std::endl << std::endl;
    
    if(c->getType() == type_batiment::Guilde){
        const Guilde* g = dynamic_cast<const Guilde*>(c);
        if(!g){ j->addGuilde(g) ; g->onBuild(j); return ;} 
        else {
            throw GameException("ERREUR: failed dynamic cast downcasting to Guilde");
        }
    } else {
        const Batiment* b = dynamic_cast<const Batiment*>(c);
        if(!b){ j->addBatiment(b) ; b->onBuild(j); return ;} 
        else {
        throw GameException("ERREUR: failed dynamic cast downcasting to Batiment");
        }
    }
}

void Perk_Classic::pickJeton(Joueur* j) const { 
    // requires player interaction
    std::vector<const Jeton*> temp = box->getUnusedJetons() ;

    std::cout << "#. Choisissez un jeton:" << std::endl << std::endl ; 
    std::vector<const Jeton*> dispo(temp.begin(), temp.begin()+3);
    unsigned int choice = chooseFromPointerVector( dispo );

    const Jeton* jet = dispo[choice] ; 
    std::cout << std::endl << "#. Jeton choisi: " << *jet << std::endl << std::endl ;
    j->addJeton(jet); 
    
}

void Perk_Classic::onCall(Joueur* j) const {
    switch(id){
        case 0 : saccage(j) ; break ;
        case 1 : pickJeton(j) ; break ; 
        case 2 : freeConstructionFromDefausse(j) ; break ; 
        default : throw GameException("ERREUR: unknown Classic Perk id") ; 
    }
}

Perk_Destruction::Perk_Destruction(type_batiment c):card(c){
    if(c != type_batiment::Premiere && c != type_batiment::Manufacture){
        throw GameException("ERREUR: La destruction par Perk Destruction n'est permise que sur Batiment Premiere ou Manufacture");
    }
}

void Perk_Destruction::destruction(Joueur* j) const {
    // requires player interaction
    if(j->getAdversaire()->getBatimentsPerType(card).empty()){std::cout << "#. Pas de bâtiment adverse à détruire" << std::endl << std::endl ; return ;}
    std::cout << "#. Choisissez un bâtiment adverse à détruire:" << std::endl << std::endl ;
    std::vector<const Batiment*> bats = j->getAdversaire()->getBatimentsPerType(card);
    unsigned int choice = chooseFromPointerVector( bats );
    std::cout << "#. Choix: " << bats[choice]->getNom() << std::endl << std::endl ;
    j->getAdversaire()->destroyBatiment(bats[choice]);

}

void Perk_Destruction::onCall(Joueur* j) const {
    destruction(j);
}

/*
std::list<ressource> Perk_PolyRessource::getPolyRessources() const {
    return res ;
}

void Perk_PolyRessource::onCall(Joueur* j) const {
    
}
*/