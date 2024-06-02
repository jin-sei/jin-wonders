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

Perk_Classic::Perk_Classic(unsigned int id){
    if(id > 2){
        throw GameException("ERREUR: Classic Perk id is 0 - 1 - 2");
    }
    id = id; 
}

void Perk_Classic::saccage(Joueur* j) const {
    j->getAdversaire()->subTresor(3);
}

void Perk_Classic::freeConstructionFromDefausse(Joueur* j) const { // need access to Box

}

void Perk_Classic::pickJeton(Joueur* j) const { // need access to Box

}

void Perk_Classic::onCall(Joueur* j) const {
    switch(id){
        case 0 : saccage(j) ; break ;
        case 1 : pickJeton(j) ; break ; 
        case 2 : freeConstructionFromDefausse(j) ; break ; 
        default : throw GameException("ERREUR: unknown Classic Perk id") ; 
    }
}

/*
std::list<ressource> Perk_PolyRessource::getPolyRessources() const {
    return res ;
}

void Perk_PolyRessource::onCall(Joueur* j) const {
    
}
*/