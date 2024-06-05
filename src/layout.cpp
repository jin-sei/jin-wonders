#include "../include/wonders.h"


void Layout::displayLayout() const {
    size_t rows = age.size() ; 
    size_t columns = age[0].size();
    //size_t rows = sizeof(age) / sizeof(age[0]);
    //size_t columns = sizeof(age[0]) / sizeof(age[0][0]) ;
    //std::cout << rows << " ; " << columns << std::endl;
    // DEPRECATED : on utilise des vecteurs finalement c'est mieux

    for(int i = 0 ; i < rows ; i++){
        std::cout << " | " ; 
        for(int j=0 ; j < columns ; j++){
            if( age[i][j] != 0 && age[i][j] != 4) { std::cout << age[i][j] ; } else { std::cout << " " ;}  
            std::cout << " | " ;
        }
        std::cout << std::endl ;
    }
}

/*
void Layout::displayCards(){
    for( auto iter = cards.begin() ; iter != cards.end() ; ++iter ){
        std::cout << **iter << std::endl ; 
    }
}
*/

void Layout::updateLayout(){
    size_t rows = age.size();
    size_t columns = age[0].size() ;

    for(int i = 0 ; i < rows-1 ; i++){ // on ne va pas sur la dernière rangée, toujours accessibles
        for(int j=0 ; j < columns ; j++){
           
           //std::cout << "reading : " << age[i][j] << " | " << age[i+1][j] << " | " << age[i+1][j+1] << std::endl ;
            if(j == columns -1){
                if( ((age[i][j] != 0) && (age[i][j] != 4)) && ((age[i+1][j] == 0)||(age[i+1][j] == 4)) ){ // on ne check que la carte du dessous pour les cartes les plus à droite
                    age[i][j] = 1 ; // visible et accessible
                }
            } else {

                if( ((age[i][j] != 0)&&(age[i][j] != 4)) && ((age[i+1][j] == 0)||(age[i+1][j] == 4)) && ((age[i+1][j+1] == 0)||(age[i+1][j+1] == 4)) ){ // les deux cartes qui recouvrent ont disparues
                    age[i][j] = 1 ; // visible et accessible
                }
            }

        }
    }
}

std::vector<int> Layout::getAvailableSlots() const {

    size_t rows = age.size() ;
    size_t columns = age[0].size() ;

    std::vector<int> available ; 

    for(int i = 0 ; i < rows ; i++){ // on ne va pas sur la dernière rangée, toujours accessibles
        for(int j=0 ; j < columns ; j++){
            if( age[i][j] == 1 ){
                //std::cout << i << " " << j << std::endl ; 
                available.push_back(i);
                available.push_back(j);
            }
        }
    }

    return available ;

}

std::vector<const Carte*> Layout::getAvailableCards() const {

    std::vector<const Carte*> temp ; 

    for( size_t i = 0 ; i < getAvailableSlots().size() ; i+=2 ){
        temp.push_back( cards[ getBatimentFromLayout( getAvailableSlots()[i], getAvailableSlots()[i+1] ) ] );
    }

    return temp  ;
}

void Layout::switchAge(phase_jeu p){

    cards.clear(); 
    
    switch(p){
        case phase_jeu::AGE_I : 
            age = ageI ; 
            break ; 
        case phase_jeu::AGE_II : 
            age = ageII ;
            break ;  
        case phase_jeu::AGE_III :
            age = ageIII ;
            break ;
        case phase_jeu::START :
            age.clear();
            break ;
        case phase_jeu::END :
            age.clear();
            break ; 
        default : 
            throw GameException("AGE INCONNU") ; 
    };
}

const Carte* Layout::pickSlot(int i, int j){

    if( age[i][j] != 1 ){ throw GameException("ERREUR : cette carte n'est pas accessible"); }

    unsigned int x = this->getBatimentFromLayout(i, j);
    const Carte* save = cards[ x ];
    cards[ x ] = nullptr ;
    age[ i ][  j ] = 4 ; 
    //displayLayout();
    updateLayout();

    return save ;

}

unsigned int Layout::getBatimentFromLayout(int i, int j) const {

    if( this->getLayoutSize() != this->getVectorSize() ){ throw GameException("ERREUR : unmatched matrix ("+std::to_string(this->getLayoutSize())+") and vector ("+std::to_string(this->getVectorSize())+")" ); }
    if( this->getLayoutSize() == 0 || this->getVectorSize() == 0 ){ throw GameException("ERREUR : le layout est vide"); }
    if( age[i][j] == 0 ){ throw GameException("ERREUR : pas de carte à cette position");}

    size_t rows = age.size() ;
    size_t columns = age[0].size() ;

    if( i > rows || j > columns ){ throw GameException("ERREUR : indexes out of bounds");}

    unsigned int position = 0 ;

    for(size_t iter_rows = 0 ; iter_rows != rows ; ++iter_rows){
        for(size_t iter_columns = 0 ; iter_columns != columns ; ++iter_columns){

            if( iter_rows == i && iter_columns == j ){

                return position ;

            }

            if( age[ iter_rows ][ iter_columns ] != 0 ){

                position ++ ; 

            }

        }
    }

    throw GameException("ERREUR : erreur dans le parcours de la matrice");
}

bool Layout::isEmpty() const {
    for(auto iter_rows = age.begin() ; iter_rows != age.end() ; ++iter_rows){
        for(auto iter_columns = iter_rows->begin() ; iter_columns != iter_rows->end() ; ++iter_columns){
            
            if( *iter_columns != 0 && *iter_columns != 4 ){
                return false ; 
            }

        }
    }
    return true ; 
}

unsigned int Layout::getLayoutSize() const { // retourne le nombre de non 0 dans la matrice

    unsigned int size = 0 ; 

    for(auto iter_rows = age.begin() ; iter_rows != age.end() ; ++iter_rows){
        for(auto iter_columns = iter_rows->begin() ; iter_columns != iter_rows->end() ; ++iter_columns){
            if( *iter_columns != 0 && *iter_columns != 4 ){ size ++ ;}
        }
    }

    return size ; 
            
}

unsigned int Layout::getVectorSize() const { // retourne le nombre d'éléments non nullptr dans cards

    unsigned int x = 0 ; 
    
    for( auto iter = cards.begin() ; iter != cards.end() ; ++iter ){

        if( *iter != nullptr ){ x++ ;}

    }

    return x ;

}


void Layout::inputCards(std::vector<const Carte*> deck){

    // ajoute seulement des cartes 
    // pas de shuffle, c'est Box qui s'en occupe

    for(auto iter = deck.begin() ; iter != deck.end() ; ++iter){
        cards.push_back(*iter);
    }

    return ;

}

void Layout::reinit(){
    cards.clear();
    age = ageI ; 
}