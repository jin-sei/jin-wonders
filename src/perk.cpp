#include "wonders.h"

/*
bool Perk::isPolyRes() {
    if(Perk_PolyRessource* p = dynamic_cast<Perk_PolyRessource*>(this)){
        return true ; 
    } else { return false ;}
}
*/

void Perk_CoinPerCard::gainCoinPerCard() const {
    Box::getInstance().getCurrentJoueur().addTresor( Box::getInstance().getCurrentJoueur().getNumberBatiment(this->card)*coin );
}

void Perk_CoinPerCard::onCall() const {
    gainCoinPerCard();
}

void Perk_FixedTrade::setFixedTrade() const {
    for(auto iter = res.begin() ; iter != res.end() ; ++iter){
        Box::getInstance().getCurrentJoueur().setFixedTrade(*iter, coin);
    }
}

void Perk_FixedTrade::onCall() const {
    setFixedTrade();
}

Perk_Classic::Perk_Classic(unsigned int id):id(id){
    if(id > 2){
        throw GameException("ERREUR: Classic Perk id is 0 - 1 - 2");
    }
    /*
    if(box == nullptr){
        throw GameException("ERREUR: Un pointeur vers Box non nul est requis pour une Perk Classic");
    }
    */
}

void Perk_Classic::saccage() const {
    Box::getInstance().getCurrentJoueur().getAdversaire().subTresor(3);
}

void Perk_Classic::freeConstructionFromDefausse() const {
    // requires player interaction
    if(Box::getInstance().getDefausse().empty()){std::cout << "#. Pas de carte défaussée à construire" << std::endl << std::endl ; return ;}

    std::cout << "#. Choisissez une carte de la défausse à construire:" << std::endl << std::endl ;
    const Carte* c = Box::getInstance().getDefausse()[ askJoueur( Box::getInstance().getDefausse() ) ];
    std::cout << "#. Carte choisie: " << c->getNom() << std::endl << std::endl;
    
    Box::getInstance().getCurrentJoueur().construireCarte(*c);
}

void Perk_Classic::pickJeton() const { 
    // requires player interaction

    std::cout << "#. Choisissez un jeton:" << std::endl << std::endl ; 
    std::vector<const Jeton*> dispo(Box::getInstance().getUnusedJetons().begin(), Box::getInstance().getUnusedJetons().begin()+3);
    unsigned int choice = askJoueur( dispo );

    const Jeton* jet = dispo[choice] ; 
    std::cout << std::endl << "#. Jeton choisi: " << *jet << std::endl << std::endl ;
    Box::getInstance().getCurrentJoueur().addJeton(*jet); 
    
}

void Perk_Classic::onCall() const {
    switch(id){
        case 0 : saccage() ; break ;
        case 1 : pickJeton() ; break ; 
        case 2 : freeConstructionFromDefausse() ; break ; 
        default : throw GameException("ERREUR: unknown Classic Perk id") ; 
    }
}

Perk_Destruction::Perk_Destruction(type_batiment c):card(c){
    if(c != type_batiment::Premiere && c != type_batiment::Manufacture){
        throw GameException("ERREUR: La destruction par Perk Destruction n'est permise que sur Batiment Premiere ou Manufacture");
    }
}

void Perk_Destruction::destruction() const {
    // requires player interaction
    if(Box::getInstance().getCurrentJoueur().getAdversaire().getBatimentsPerType(card).empty()){std::cout << "#. Pas de bâtiment adverse à détruire" << std::endl << std::endl ; return ;}
    std::cout << "#. Choisissez un bâtiment adverse à détruire:" << std::endl << std::endl ;
    std::vector<const Batiment*> bats = Box::getInstance().getCurrentJoueur().getAdversaire().getBatimentsPerType(card);
    unsigned int choice = askJoueur( bats );
    std::cout << "#. Choix: " << bats[choice]->getNom() << std::endl << std::endl ;
    Box::getInstance().getCurrentJoueur().getAdversaire().destroyBatiment(*bats[choice]);

}

void Perk_Destruction::onCall() const {
    destruction();
}

/*
std::list<ressource> Perk_PolyRessource::getPolyRessources() const {
    return res ;
}

void Perk_PolyRessource::onCall(Joueur* j) const {
    
}
*/