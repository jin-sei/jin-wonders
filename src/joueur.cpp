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

unsigned int Joueur::fetchPtVictoire(bool tiebreaker) const {

    unsigned int points = 0 ; 

    // BATIMENTS
    for(auto iter = batiments.begin() ; iter != batiments.end() ; ++iter){

        if( tiebreaker && (**iter).getType() != type_batiment::Civil ){
            continue ; 
        } else {
            points += (**iter).getPointVictoire();
        }

    }

    if( tiebreaker ) { return points ; }

    // MERVEILLES
    for(auto iter = merveilles.begin() ; iter != merveilles.end() ; ++iter){
        points += (**iter).getPointVictoire();
    }

    // GUILDES
    for(auto iter = guildes.begin() ; iter != guildes.end() ; ++iter){
        points += (**iter).ptVictoireFinJeu(this);
    }

    // JETONS PROGRÈS
    if( possessJeton(jeton_progres::Mathematiques) ){ points += jetons.size()*3; }
    if( possessJeton(jeton_progres::Philosophie) ){ points += 7; }
    if( possessJeton(jeton_progres::Agriculture) ){ points += 4; }

    return points ; 
    
}

bool Joueur::possessBatiment(std::string s) const{
    for( auto iter = batiments.begin() ; iter != batiments.end() ;  ++iter){

        if( (**iter).getNom() == s ){
            return true ;
        }

    }
    return false ; 
}

bool Joueur::possessJeton(jeton_progres id) const{
    auto it = std::find_if(jetons.begin(), jetons.end(), [id](const Jeton* j){
        return j->getId() == id;  
    });

    return (it!=jetons.end()); 
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

unsigned int Joueur::achetableJoueur(const Carte* c) const {
    // retourne le nombre de pièces qu'il faudra dépenser pour acheter la Carte
    std::list<ressource> cost = c->getCoutRessource() ;

    // check chaînage (on fera ça en dehors de la méthode)
    
    // check ressources possédées
    std::list<ressource> missing = achetableRessource(cost);
    if( missing.empty() ){ return c->getCoutArgent(); }

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

    if( missing.empty() ){ return c->getCoutArgent(); }

    std::cout << "STILL MISSING RESSOURCES: " ; displayRessources( missing ) ; std::cout << std::endl;

    // check ressources offertes : // Jetons Architecture et Maçonnerie

    if( 
        (c->getType() == type_batiment::Civil) && possessJeton(jeton_progres::Maconnerie)
        ||
        (c->getType() == type_batiment::Merveille) && possessJeton(jeton_progres::Architecture)
    ){ 
        if(missing.size() <= 2){ return c->getCoutArgent(); } else {

            // more than 2 ressources were missing
            // determine ressources with the highest trade price to eliminate them

            for(size_t i = 0 ; i <= 1 ; i ++){
                auto max = std::max_element(missing.begin(), missing.end(), 
                [this](ressource r1, ressource r2){ 
                    return this->getTradePrice(r1) < this->getTradePrice(r2) ;
                }) ;
                missing.erase(max);
            }

        }
    }

    std::cout << "STILL MISSING RESSOURCES: " ; displayRessources( missing ) ; std::cout << std::endl;
    
    
    // check prix du commerce pour acheter les ressources manquantes
    unsigned int price = c->getCoutArgent() ;

    if( !missing.empty() ){ // on vérifie que les étapes précédentes n'ont pas permis de trouver toutes les ressources manquantes
        for( auto iter = missing.begin() ; iter != missing.end() ; ++iter ){
            price += getTradePrice(*iter); 
        }
    }

    return price ; 

}


unsigned int Joueur::getFixedTrade(ressource r) const {
    if( static_cast<int>(r) > 5 || static_cast<int>(r) < 1 ){
        throw GameException("ERREUR : FixedTrade ne s'applique que aux ressources de production");
    }
    return fixed_trade.at(r);

}

void Joueur::setFixedTrade(ressource r, unsigned int price){
    if( static_cast<int>(r) > 5 || static_cast<int>(r) < 1 ){
        throw GameException("ERREUR : FixedTrade ne s'applique que aux ressources de production");
    }
    fixed_trade[r] = price ; 
}

unsigned int Joueur::getTradePrice(ressource r) const {
    if( static_cast<int>(r) > 5 || static_cast<int>(r) < 1 ){
        throw GameException("ERREUR : le prix de Trade ne s'obtient que pour les ressources de production");
    }
    if( this->getFixedTrade(r) == 0){
        return this->getAdversaire()->fetchRessource({r}).size() + 2 ;
    } else {
        return this->getFixedTrade(r);
    }
}

unsigned int Joueur::getNumberActiveWonders() const {
    unsigned int nb = 0;  
    for( auto iter =  merveilles.begin() ; iter != merveilles.end() ; ++iter ){
        if( (**iter).getFeed() != nullptr ){
            nb ++ ; 
        }
    }
    return nb;
}

unsigned int Joueur::getNumberBatiment(type_batiment t) const {
    if(t == type_batiment::Merveille){ return getNumberActiveWonders(); }

    unsigned int nb = 0;
    for( auto iter =  batiments.begin() ; iter != batiments.end() ; ++iter ){
        if( (**iter).getType() == t ){
            nb ++ ; 
        }
    }
    return nb;
}

unsigned int Joueur::getNumberUniqueSymbols() const {

    std::set<ressource> set_s = getSymboleScientifique() ; 
    std::list<ressource> list_s(set_s.begin(), set_s.end()) ;
    std::list<ressource> science = fetchRessource( list_s );

    std::set<ressource> no_duplicates(science.begin(), science.end());

    return no_duplicates.size();

}

unsigned int Joueur::getNumberPairs() const {

    std::set<ressource> set_s = getSymboleScientifique() ; 
    std::list<ressource> list_s(set_s.begin(), set_s.end()) ;
    std::list<ressource> science = fetchRessource( list_s );

    return science.size() - getNumberUniqueSymbols(); 
}

void Joueur::reinitTradePrice(){
    fixed_trade.clear();
    fixed_trade[ressource::Argile] = 0;
    fixed_trade[ressource::Pierre] = 0;
    fixed_trade[ressource::Bois] = 0;
    fixed_trade[ressource::Papyrus] = 0;
    fixed_trade[ressource::Verre] = 0;
}

void Joueur::reinit(){
    batiments.clear();
    jetons.clear();
    merveilles.clear();
    reinitTradePrice();
    tresor = 0 ; 
}