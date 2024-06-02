#include "../include/wonders.h"

std::list<ressource> Joueur::fetchRessource(std::list<ressource> r) const {
    
    // iterates through the player's Batiments to find ressources
    // does not include conditional ressources such as Wonders / Commerce buildings
    std::list<ressource> production ;
    std::list<ressource> temp  ;

    for(auto iter = batiments.begin() ; iter != batiments.end() ; ++iter){
        temp = (**iter).getProduction() ; 

        if( (**iter).getType() != type_batiment::Commerce ){ // on ne fetch pas les poly ressource du Commerce
            for(auto iter_res = temp.begin() ; iter_res !=  temp.end() ; ++iter_res ){

                if( std::find(r.begin(), r.end(), *iter_res) != r.end() ){
                    production.push_back(*iter_res);
                }

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

std::vector<const Batiment*> Joueur::getBatimentsPerType(type_batiment t) const {
    std::vector<const Batiment*> bats ; 
    for( auto iter = batiments.begin() ; iter != batiments.end() ; ++iter ){
        if((**iter).getType()==t){
            bats.push_back(*iter);
        }
    }
    return bats ; 
}

std::list<ressource> Joueur::achetableRessource(std::list<ressource> cost) const {
    if(cost.empty()) { return {} ; }
    //if(cost_r.size() > buy.size()) { return false ; }

    std::list<ressource> pop_buy = fetchRessource( {ressource::Argile, ressource::Bois, ressource::Pierre, ressource::Papyrus, ressource::Verre} );
    std::list<ressource> missing = {}; 
    
    for(auto iter = cost.begin() ; iter != cost.end() ; ++iter){ // parcours les ressources demandées
        std::cout << "ASKED: " << tostringRessources(*iter) << std::endl ;
        
        for(auto iter_b = pop_buy.begin() ; iter_b != pop_buy.end() ; ++iter_b){ // parcours les ressources disponibles
            
            std::cout << "FOUND: " << tostringRessources(*iter_b) << " ; ";

            if(*iter_b == *iter){ // bonne ressource trouvée

                std::cout << " MATCH!" << std::endl;
                pop_buy.erase(iter_b);
                break;

            } else if(next(iter_b) == pop_buy.end()){ // on atteint la fin sans trouver de ressource match : ressource manquante

                std::cout << "NOT FOUND!" << std::endl;
                missing.push_back(*iter);
            }

        } 
        std::cout << std::endl ;
    }
    return missing ;
}

unsigned int Joueur::achetableJoueur(std::list<ressource> cost){
    // retourne le nombre de pièces qu'il faudra dépenser pour acheter la Carte

    // check chaînage (on fera ça en dehors de la méthode)
    
    // check ressources possédées
    std::list<ressource> missing = achetableRessource(cost);
    if( missing.empty() ){ return 0; }

    std::cout << "MISSING RESSOURCES: " ; displayRessources( missing ) ; std::cout << std::endl;

    // check ressources conditionelles (check Merveilles et Commerce)
    // COMMERCE
    std::vector<const Batiment*> poly = getBatimentsPerType(type_batiment::Commerce);
    poly.insert(poly.end(), merveilles.begin(), merveilles.end());
    std::list<ressource> prod_temp  ;
    bool breaker = false ; 

    for( auto iter_missing = missing.begin() ; iter_missing != missing.end() ; ++iter_missing ){
        std::cout << "MISSING: " << tostringRessources(*iter_missing) << std::endl ; 
        for( auto iter_bat = poly.begin() ; iter_bat != poly.end() ; ++iter_bat ){
            std::cout << "ITERATING THROUGH: " << (**iter_bat).getNom() << std::endl ; 
            prod_temp = (**iter_bat).getProduction() ;

            if( !(**iter_bat).getProduction().empty() ){
                for( auto iter_bat_res = prod_temp.begin() ; iter_bat_res != prod_temp.end() ; ++iter_bat_res ){
                    std::cout << "FOUND: " << tostringRessources( *iter_bat_res ) << std::endl; 
                    
                    if( *iter_bat_res == *iter_missing ){
                        std::cout << "MATCH!" << std::endl;
                        iter_missing = missing.erase(iter_missing);
                        breaker = true ; 
                        //if(iter_bat != poly.end()){ ++iter_bat ;};
                        //if(iter_missing != missing.end()) {++iter_missing ;} ;
                        break ;
                    }

                }
            }

            if(breaker) break ; 

        }

        if(breaker){
            breaker = false;
            continue ; 
        }
    }

    std::cout << "STILL MISSING RESSOURCES: " ; displayRessources( missing ) ; std::cout << std::endl;

    // check ressources offertes : // Jetons Architecture et Maçonnerie
    // si il reste plus de 2 ressources manquantes, il faut choisir d'éliminer les ressources 
    // avec le TradePrice les plus élevés
    
    // check prix du commerce pour acheter les ressources manquantes
    unsigned int price = 0 ;

    if( !missing.empty() ){ // on vérifie que les étapes précédentes n'ont pas permis de trouver toutes les ressources manquantes
        for( auto iter = missing.begin() ; iter != missing.end() ; ++iter ){
            price += getTradePrice(*iter); 
        }
    }

    return price ; 

}


unsigned int Joueur::getFixedTrade(ressource r){
    if( static_cast<int>(r) > 5 || static_cast<int>(r) < 1 ){
        throw GameException("ERREUR : FixedTrade ne s'applique que aux ressources de production");
    }
    return fixed_trade[r];

}

void Joueur::setFixedTrade(ressource r, unsigned int price){
    if( static_cast<int>(r) > 5 || static_cast<int>(r) < 1 ){
        throw GameException("ERREUR : FixedTrade ne s'applique que aux ressources de production");
    }
    fixed_trade[r] = price ; 
}

unsigned int Joueur::getTradePrice(ressource r){
    if( static_cast<int>(r) > 5 || static_cast<int>(r) < 1 ){
        throw GameException("ERREUR : le prix de Trade ne s'obtient que pour les ressources de production");
    }
    if( this->getFixedTrade(r) == 0){
        return this->getAdversaire()->fetchRessource({r}).size() + 2 ;
    } else {
        return this->getFixedTrade(r);
    }
}

unsigned int Joueur::getNumberBatiment(type_batiment t){
    unsigned int nb = 0;  
    for( auto iter =  batiments.begin() ; iter != batiments.end() ; ++iter ){
        if( (**iter).getType() == t ){
            nb ++ ; 
        }
    }
    return nb;
}

unsigned int Joueur::getNumberActiveWonders(){
    unsigned int nb = 0;  
    for( auto iter =  merveilles.begin() ; iter != merveilles.end() ; ++iter ){
        if( (**iter).getFeed() != nullptr ){
            nb ++ ; 
        }
    }
    return nb;
}