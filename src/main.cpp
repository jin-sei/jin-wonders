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

        Box& my_box = Box::getInstance(); 
        my_box.newAge(); // on passe de END à START pour setup le jeu
        // on passe à l'âge I et le jeu commence

    } catch(const std::exception& e) {

        std::cerr << e.what() << std::endl; 

    }

    return 0 ;
}

// NILS TO DO:

// CURRENT:
// fix singleton pour qu'il ne soit pas accessible globalement


// NEXT :
// IA Player : add Subject of the ask and Repondant so we know when to ask Player or AI
// create a read only interface that allows to communicate with the game (using askJoueur)


// MAIN QUESTS:



// OTHER TASKS: 


// SIDE QUESTS: 
// écrire une documentation et expliquer les choix de développement
// enhanced console display (Layout, Plateau, Players, Décompte des points)