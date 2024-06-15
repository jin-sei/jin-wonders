#include "../include/wonders.h"

#include <iostream>
#include <string>

int tests(){
    
    return 0 ; 
    
}

int main(){

    //tests() ;
    //system("clear");
    std::cout << std::endl << "7 WONDERS DUEL" << std::endl << "--------------" << std::endl  << std::endl ;

    try {

        Box my_box = Box(); 
        my_box.newAge(); // on passe de END à START pour setup le jeu
        // on passe à l'âge I et le jeu commence

    } catch(const std::exception& e) {

        std::cerr << e.what() << std::endl; 

    }

    return 0 ;
}

// NILS TO DO:

// CURRENT:


// NEXT :


// MAIN QUESTS:


// OTHER TASKS: 


// SIDE QUESTS: 
// enhanced console display (Layout, Plateau, Players, Décompte des points)