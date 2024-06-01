#include "../include/wonders.h"

std::list<ressource> Joueur::fetchRessource(std::list<ressource> r){
    
    // iterates through the player's Batiments to find ressources
    std::list<ressource> production ;
    std::list<ressource> temp  ;

    for(auto iter = batiments.begin() ; iter != batiments.end() ; ++iter){
        temp = (**iter).getProduction() ; 
        for(auto iter_res = temp.begin() ; iter_res !=  temp.end() ; ++iter_res ){

            if( std::find(r.begin(), r.end(), *iter_res) != r.end() ){
                production.push_back(*iter_res);
            }

        }

    }

    return production ; 
}

bool Joueur::possessBatiment(std::string s){
    for( auto iter = batiments.begin() ; iter != batiments.end() ;  ++iter){

        if( (**iter).getNom() == s ){
            return true ;
        }

    }
    return false ; 
}

unsigned int Joueur::wannaBuyCard(const Carte* c){
    // retourne le nombre de pièces qu'il faudra dépenser pour acheter la Carte

    // check chaînage 
    if( possessBatiment(c->getNom()) ){ return 0 ;}

    // check ressources possédées
    std::list<ressource> missing = c->achetableRessource(fetchRessource( {ressource::Argile, ressource::Bois, ressource::Pierre, ressource::Papyrus, ressource::Verre} ));
    if( missing.empty() ){ return c->getCoutArgent(); }

    return c->getCoutArgent(); // temporaire, à supprimer;

    // check ressources conditionelles (check Merveilles et Commerce)

    // check ressources offertes
    
    // check prix du commerce pour acheter les ressources manquantes
    unsigned int price = c->getCoutArgent() ;

    if( !missing.empty() ){ // on vérifie que les étapes précédentes n'ont pas permis de trouver toutes les ressources manquantes
        for( auto iter = missing.begin() ; iter != missing.end() ; ++iter ){
            // price += getTradePrice // mais la fonction est dans Box il faut la déplacer dans Joueur 
        }
    }

    return price ; 

}