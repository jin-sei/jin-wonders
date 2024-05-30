#include "../include/wonders.h"

#include <iostream>
#include <string>

int main(){

    //try {

    std::cout << std::endl << "7 WONDERS DUEL" << std::endl << "--------------" << std::endl  << std::endl ;
    
    Carte my_carte1 = Carte("Stables", type_batiment::Militaire, phase_jeu::AGE_I, {ressource::Argile, ressource::Argile, ressource::Bois, ressource::Bois, ressource::Bois}, 3) ;
    my_carte1.setCoutRessource({ressource::Argile, ressource::Argile, ressource::Bois});
    std::cout << my_carte1 << std::endl ; 

    Merveille my_wonder1 = Merveille("Le Mausolée", type_batiment::Merveille, phase_jeu::AGE_I, {ressource::Argile, ressource::Bois, ressource::Bois, ressource::Pierre, ressource::Papyrus}, 0, 0, 5, true);
    std::cout << my_wonder1 << std::endl;

    my_wonder1.achetableRessource({{ressource::Argile, ressource::Bois, ressource::Bois, ressource::Pierre, ressource::Verre, ressource::Papyrus, ressource::Papyrus}});

    Batiment my_batiment1 = Batiment("Muraille", type_batiment::Militaire, phase_jeu::AGE_III, {ressource::Pierre, ressource::Pierre}, 0, 0, 0, {ressource::Bouclier, ressource::Bouclier}, "");
    std::cout << my_batiment1 << std::endl ; 

    Batiment my_batiment2 = Batiment("Palace", type_batiment::Civil, phase_jeu::AGE_I, {}, 0, 0, 0, {}, "Obélisque");
    Batiment my_batiment3 = Batiment("Académie", type_batiment::Scientifique, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Roue}, "");

    Layout my_layout1 = Layout();
    my_layout1.switchAge(phase_jeu::AGE_I);

    my_layout1.displayLayout();
    //my_layout1.updateLayout();
    std::cout << std::endl;

    //my_layout1.pickSlot(4, 5);
    //my_layout1.pickSlot(4, 4);

    //my_layout1.updateLayout();
    my_layout1.displayLayout();

    std::cout << std::endl; 

    my_layout1.switchAge(phase_jeu::AGE_III);
    my_layout1.displayLayout();
    std::cout << std::endl;

    //my_layout1.pickSlot(6, 3);
    //my_layout1.pickSlot(6, 4);

    my_layout1.displayLayout();
    std::cout << my_layout1.getLayoutSize() << std::endl;

    std::cout << my_layout1.isEmpty() << std::endl; 

    phase_jeu p = phase_jeu::END ; 
    std::cout << tostringAge(++p) << std::endl << std::endl ;

    std::cout << "SANDBOX END" << std::endl << "--------------" << std::endl  << std::endl ;


    Box my_box1 = Box();
    my_box1.allCardsCreation();
    //my_box1.displayAllCards();
    my_box1.newAge();
    my_box1.getPlateau()->getLayout()->displayCards();
    my_box1.getPlateau()->getLayout()->displayLayout() ;
    std::cout << my_box1.getPlateau()->getLayout()->getLayoutSize() << " : " << my_box1.getPlateau()->getLayout()->getVectorSize() << std::endl;

    my_box1.getPlateau()->getLayout()->pickSlot(4, 0);
    my_box1.getPlateau()->getLayout()->pickSlot(4, 1);
    //std::cout << *(my_box1.getPlateau()->getLayout()->pickSlot(4, 2)) << std::endl;
    //my_box1.getPlateau()->getLayout()->pickSlot(3, 0);
    //my_box1.getPlateau()->getLayout()->pickSlot(4, 5);
    //my_box1.getPlateau()->getLayout()->pickSlot(4, 4);
    //my_box1.getPlateau()->getLayout()->pickSlot(4, 3);

    my_box1.getPlateau()->getLayout()->displayLayout() ;
    std::cout << my_box1.getPlateau()->getLayout()->getLayoutSize() << " : " << my_box1.getPlateau()->getLayout()->getVectorSize() << std::endl;

    
    /*
    } catch(const GameException& e) {

        std::cerr << e.getInfo() << std::endl; 

    }
    */

    return 0 ;  
}

// NILS TO DO : 

// CURRENT :
// setup github 
// setup CMake file

// NEXT : 

// ajout des cartes d'un âge dans le Layout à chaque nouvel âge
// mélange du vector "cards" dans le Layout


// MAIN QUESTS : 
// implémenter le commerce et améliorer la fonction de checkCout et d'achat ;
// (chaingage < ressources possédées < ressources conditionelles < ressources offertes < ressources à acheter)
// implémenter les Guildes et les bâtiments Commerce
// distribution -> rajouter les cartes Guildes
// distribution (début de partie) -> initialiser le plateau avec 5 jetons
// effet des Merveilles et des Jetons


// OTHER TASKS : 
// choisir quels cartes rentrer dans le Plateau à chaque âge
// tours de jeu 


// SIDE QUESTS : 
// rendre Box singleton
// rendre Carte abstraite (non instanciable)
// rendre Joueur doubleton
