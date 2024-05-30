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