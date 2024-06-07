#include "../include/wonders.h"


std::set<ressource> getMatierePremiere() {
    return {
        ressource::Pierre,
        ressource::Argile,
        ressource::Bois
    };
}

std::set<ressource> getProduitManufacture() {
    return {
        ressource::Papyrus,
        ressource::Verre
    };
}

std::set<ressource> getRessource() {
    return {
        ressource::Pierre,
        ressource::Argile,
        ressource::Bois,
        ressource::Papyrus,
        ressource::Verre
    };
}

std::set<ressource> getSymboleScientifique() {
    return {
        ressource::Roue,
        ressource::Compas, 
        ressource::Pilon, 
        ressource::Cadran, 
        ressource::Plume, 
        ressource::Balance, 
        ressource::Telescope
    };
}

std::string tostringRessources(ressource r){
    switch(r) {
        case ressource::Roue : return "Roue" ; 
        case ressource::Compas : return "Compas" ; 
        case ressource::Pilon : return "Pilon" ; 
        case ressource::Cadran : return "Cadran" ; 
        case ressource::Plume : return "Plume" ; 
        case ressource::Balance : return "Balance" ; 
        case ressource::Telescope : return "Telescope" ; 
        case ressource::Bouclier : return "Bouclier" ; 
        case ressource::Papyrus : return "Papyrus" ; 
        case ressource::Verre : return "Verre" ; 
        case ressource::Pierre : return "Pierre" ; 
        case ressource::Argile : return "Argile" ; 
        case ressource::Bois : return "Bois" ; 
        default : throw GameException("Ressource inconnue") ;
    };
}

std::string tostringType(type_batiment t){
    switch(t){
        case type_batiment::Civil : return "Civil" ; 
        case type_batiment::Militaire : return "Militaire" ; 
        case type_batiment::Scientifique : return "Scientifique" ;
        case type_batiment::Manufacture : return "Manufacture" ;
        case type_batiment::Premiere : return "Premiere" ;
        case type_batiment::Commerce : return "Commerce" ;
        case type_batiment::Guilde : return "Guilde" ;
        case type_batiment::Merveille : return "Merveille" ;
        default : throw GameException("Batiment inconnu") ;
    };
}

std::string tostringJeton(jeton_progres j){
    switch(j){
        case jeton_progres::Agriculture : return "Agriculture" ;
        case jeton_progres::Architecture : return "Architecture" ;
        case jeton_progres::Economie : return "Economie" ; 
        case jeton_progres::Loi : return "Loi" ;
        case jeton_progres::Maconnerie : return "Maçonnerie" ;
        case jeton_progres::Mathematiques : return "Mathématiques" ;
        case jeton_progres::Philosophie : return "Philosophie" ; 
        case jeton_progres::Strategie : return "Stratégie" ;
        case jeton_progres::Theologie : return "Théologie" ;
        case jeton_progres::Urbanisme : return "Urbanisme" ;
        default : throw GameException("Jeton inconnu");
    }
}

std::string tostringAge(phase_jeu p){
    switch(p){
        case phase_jeu::START : return "INIT" ; 
        case phase_jeu::AGE_I : return "AGE I" ; 
        case phase_jeu::AGE_II: return "AGE II" ; 
        case phase_jeu::AGE_III : return "AGE III" ; 
        case phase_jeu::END : return "FIN" ; 
        default : throw GameException("Age inconnu") ;
    }
}


phase_jeu& operator++(phase_jeu& phase){
    if( static_cast<int>(phase) != 4 ){
        phase = static_cast<phase_jeu>(static_cast<int>(phase)+1) ;
    } else {
        phase = static_cast<phase_jeu>(static_cast<int>(0));
    }
    return phase ; 
}

std::ostream& operator<<(std::ostream& f, const Jeton& j){
    f << tostringJeton(j.getId()) ;
    return f ;
}

void displayRessources(std::list<ressource> r){
    //std::cout << "DISPLAYING RESSOURCES" << std::endl ; 
    for( auto iter = r.begin() ; iter != r.end() ; ++iter ){
        std::cout << tostringRessources(*iter) << " ; " ; 
    }
    std::cout << std::endl ; 
}

unsigned int askJoueur(std::vector<std::string> r){
    for( size_t i = 0 ; i < r.size() ; i++ ){
        std::cout << i << ". " << r[i] << std::endl;
    }
    std::cout << std::endl ; 

    unsigned int choice = r.size() ; 
    while( choice >= r.size() ){
        std::cout << "0-" << r.size()-1 << " > " ;
        std::cin >> choice ;  
    }
    std::cout << std::endl;
    return choice ; 
}

void waitForInteraction() {
    
    std::cout << "#. Press enter to continue > " ;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input
    std::cin.get();
    return ; 
    
}