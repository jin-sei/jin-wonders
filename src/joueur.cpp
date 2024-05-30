#include "../include/wonders.h"

std::list<ressource> Joueur::fetchRessource(std::list<ressource> r){
    // iterates through the player's Batiments to find a ressource
    std::list<ressource> production ;

    for(auto iter = batiments.begin() ; iter != batiments.end() ; ++iter){

        for(auto res_iter = (**iter).getProduction().begin() ; res_iter != (**iter).getProduction().end() ; ++res_iter ){

            if( std::find(r.begin(), r.end(), *res_iter) != r.end() ){ 

                production.push_back(*res_iter);

            }

        }

    }

    return production ; 

}