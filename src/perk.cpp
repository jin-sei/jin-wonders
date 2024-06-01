#include "wonders.h"

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
    j->setFixedTrade(res, coin);
}

void Perk_FixedTrade::onCall(Joueur* j) const {
    setFixedTrade(j);
} 