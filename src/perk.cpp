#include "wonders.h"

/*
bool Perk::isPolyRes() {
    if(Perk_PolyRessource* p = dynamic_cast<Perk_PolyRessource*>(this)){
        return true ; 
    } else { return false ;}
}
*/

void Perk_CoinPerCard::gainCoinPerCard(Joueur* j) const {
    if(this->card != type_batiment::Merveille){
        j->addTresor( j->getNumberBatiment(this->card)*coin );
    }else{
        j->addTresor( j->getNumberActiveWonders()*coin );
    }
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

/*
std::list<ressource> Perk_PolyRessource::getPolyRessources() const {
    return res ;
}

void Perk_PolyRessource::onCall(Joueur* j) const {
    
}
*/