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
        ressource::Tablette, 
        ressource::Lyre, 
        ressource::Mesure, 
        ressource::Telescope
    };
}

std::string tostringRessources(ressource r){
    switch(r) {
        case ressource::Roue : return "Roue" ; 
        case ressource::Compas : return "Compas" ; 
        case ressource::Pilon : return "Pilon" ; 
        case ressource::Tablette : return "Tablette" ; 
        case ressource::Lyre : return "Lyre" ; 
        case ressource::Mesure : return "Mesure" ; 
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
        default : throw GameException("Batiment inconnue") ;
    };
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