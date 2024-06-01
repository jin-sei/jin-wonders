#include "../include/wonders.h"

#include <iostream>
#include <string>

int tests(){
    
    try {
    
    Carte my_carte1 = Carte("Stables", type_batiment::Militaire, phase_jeu::AGE_I, {ressource::Argile, ressource::Argile, ressource::Bois, ressource::Bois, ressource::Bois}, 3) ;
    my_carte1.setCoutRessource({ressource::Argile, ressource::Argile, ressource::Bois});
    std::cout << my_carte1 << std::endl ; 

    Merveille my_wonder1 = Merveille("Le Mausolée", type_batiment::Merveille, phase_jeu::AGE_I, {ressource::Argile, ressource::Bois, ressource::Bois, ressource::Pierre, ressource::Papyrus}, 0, 0, 5, true);
    std::cout << my_wonder1 << std::endl;

    std::cout << "display missing ressources : " << std::endl ; 
    displayRessources( my_wonder1.achetableRessource({{ressource::Bois, ressource::Bois, ressource::Verre, ressource::Papyrus, ressource::Papyrus}})) ;
    std::cout << std::endl ; 

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
    std::cout << tostringAge(++p) << std::endl << std::endl;

    //std::cout << "SANDBOX END" << std::endl << "--------------" << std::endl  << std::endl ;

    Box my_box1 = Box();
    my_box1.allCardsCreation();
    //my_box1.displayAllCards();
    my_box1.newAge();
    //my_box1.getPlateau()->getLayout()->displayCards();
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

    my_box1.newAge();
    //my_box1.getPlateau()->getLayout()->displayCards();
    my_box1.getPlateau()->getLayout()->displayLayout();

    const Batiment my_batiment4 = Batiment("Montagne", type_batiment::Militaire, phase_jeu::AGE_III, {ressource::Pierre, ressource::Pierre}, 0, 0, 0, {ressource::Bouclier, ressource::Bouclier, ressource::Bouclier}, "");
    const Batiment my_batiment5 = Batiment("Chateau", type_batiment::Scientifique, phase_jeu::AGE_I, {ressource::Pierre, ressource::Pierre}, 0, 0, 0, {ressource::Roue}, "");
    const Batiment my_batiment6 = Batiment("Caverne", type_batiment::Premiere, phase_jeu::AGE_II, {ressource::Pierre, ressource::Pierre}, 3, 0, 0, {ressource::Argile, ressource::Argile, ressource::Pierre}, "");
    
    my_box1.getJoueur(1)->addBatiment(&my_batiment4);
    my_box1.getJoueur(1)->addBatiment(&my_batiment5);
    my_box1.getJoueur(1)->addBatiment(&my_batiment6);

    displayCards( my_box1.getJoueur(1)->getBatiments() );

    displayRessources( my_box1.getJoueur(1)->fetchRessource({ressource::Argile, ressource::Bois})) ;
    std::cout << my_box1.getJoueur(1)->possessBatiment("Montagne") << std::endl ;
    std::cout << my_box1.getJoueur(1)->wannaBuyCard(&my_batiment6) << std::endl ;

    std::cout << "Fixed price p2: " << my_box1.getJoueur(2)->getFixedTrade(ressource::Argile) << std::endl ; 
    //my_box1.getJoueur(2)->setFixedTrade(ressource::Argile, 1);
    //std::cout << "Fixed price p2: " << my_box1.getJoueur(2)->getFixedTrade(ressource::Argile) << std::endl ;
    std::cout << "Trade price for p2: " << my_box1.getJoueur(2)->getTradePrice(ressource::Argile) << std::endl << std::endl ; 

    const Batiment mock_bat_1 = Batiment("Mock 1", type_batiment::Premiere);
    const Batiment mock_bat_2 = Batiment("Mock 2", type_batiment::Premiere);
    const Batiment mock_bat_3 = Batiment("Mock 3", type_batiment::Premiere);
    const Batiment mock_bat_4 = Batiment("Mock 4", type_batiment::Premiere);
    const Batiment mock_bat_5 = Batiment("Mock 5", type_batiment::Premiere);
    const Batiment mock_bat_6 = Batiment("Mock 6", type_batiment::Manufacture);
    my_box1.getJoueur(2)->addBatiment(&mock_bat_1);
    my_box1.getJoueur(2)->addBatiment(&mock_bat_2);
    my_box1.getJoueur(2)->addBatiment(&mock_bat_3);
    my_box1.getJoueur(2)->addBatiment(&mock_bat_4);
    my_box1.getJoueur(2)->addBatiment(&mock_bat_5);
    my_box1.getJoueur(2)->addBatiment(&mock_bat_6);

    std::cout << "batiment de p2 : " << std::endl ; 
    displayCards( my_box1.getJoueur(2)->getBatiments() );

    const Perk* perk_1 = new Perk_CoinPerCard(2, type_batiment::Premiere);
    Commerce commerce_1 = Commerce("Commerce I", type_batiment::Commerce, phase_jeu::AGE_I, {}, 0, 0, 0, {}, "", perk_1);
    std::cout << "trésor p2 before perk : " << my_box1.getJoueur(2)->getTresor() << std::endl;
    commerce_1.getPerk()->onCall(my_box1.getJoueur(2));
    std::cout << "trésor p2 after perk : " << my_box1.getJoueur(2)->getTresor() << std::endl;

    delete perk_1 ;

    
    } catch(const GameException& e) {

        std::cerr << e.getInfo() << std::endl; 

    }

    return 0 ; 
    
}

int main(){

    tests() ;
    std::cout << std::endl << "7 WONDERS DUEL" << std::endl << "--------------" << std::endl  << std::endl ;
    //Box my_box = Box() ; 
    //my_box.allCardsCreation();
    //my_box.newAge();
    //displayCards( my_box.getAllBatiments() );

    return 0 ;
}

// NILS TO DO :

// CURRENT :
// systèmes des perks
// implémenter les bâtiments Commerce
// fix trade
// ressources conditionelles
// pièces par type de bâtiment


// NEXT : 
// implémenter les Guildes


// MAIN QUESTS : 
// méthodes du Plateau (pion conflit, saccages...)
// distribution (début de partie) -> initialiser le plateau avec 5 jetons
// effet des Merveilles et des Jetons


// OTHER TASKS : 
// distribution -> rajouter les cartes Guildes
// instanciations -> rajouter les cartes Commerce et supprimer les doublons
// tours de jeu 
// début de jeu
// fin de jeu, compter les points, recommencer une partie


// SIDE QUESTS : 
// rendre Box singleton
// rendre Carte abstraite (non instanciable)
// rendre Joueur doubleton
