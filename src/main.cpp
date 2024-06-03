#include "../include/wonders.h"

#include <iostream>
#include <string>

int tests(){
    
    try {
    
    //Carte my_carte1 = Carte("Stables", type_batiment::Militaire, phase_jeu::AGE_I, {ressource::Argile, ressource::Argile, ressource::Bois, ressource::Bois, ressource::Bois}, 3) ;
    //my_carte1.setCoutRessource({ressource::Argile, ressource::Argile, ressource::Bois});
    //std::cout << my_carte1 << std::endl ; 

    Merveille my_wonder1 = Merveille("Le Mausolée", type_batiment::Merveille, phase_jeu::AGE_I, {ressource::Argile, ressource::Bois, ressource::Bois, ressource::Pierre, ressource::Papyrus}, 0, 0, 5);
    std::cout << my_wonder1 << std::endl;

    std::cout << "display missing ressources : " << std::endl;
    //displayRessources( my_wonder1.achetableRessource({{ressource::Bois, ressource::Bois, ressource::Verre, ressource::Papyrus, ressource::Papyrus}})) ;
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
    
    my_box1.getJoueur(0)->addBatiment(&my_batiment4);
    my_box1.getJoueur(0)->addBatiment(&my_batiment5);
    my_box1.getJoueur(0)->addBatiment(&my_batiment6);

    displayCards( my_box1.getJoueur(0)->getBatiments() );

    displayRessources( my_box1.getJoueur(0)->fetchRessource({ressource::Argile, ressource::Bois})) ;
    std::cout << my_box1.getJoueur(0)->possessBatiment("Montagne") << std::endl ;
    std::cout << my_box1.getJoueur(0)->achetableJoueur(my_batiment6.getCoutRessource()) << std::endl ;

    std::cout << "Fixed price p2: " << my_box1.getJoueur(1)->getFixedTrade(ressource::Argile) << std::endl ; 
    //my_box1.getJoueur(1)->setFixedTrade(ressource::Argile, 1);
    //std::cout << "Fixed price p2: " << my_box1.getJoueur(1)->getFixedTrade(ressource::Argile) << std::endl ;
    std::cout << "Trade price for p2: " << my_box1.getJoueur(1)->getTradePrice(ressource::Argile) << std::endl << std::endl ; 

    const Batiment mock_bat_1 = Batiment("Mock 1", type_batiment::Premiere, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Argile});
    const Batiment mock_bat_2 = Batiment("Mock 2", type_batiment::Premiere, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Argile});
    const Batiment mock_bat_3 = Batiment("Mock 3", type_batiment::Premiere, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Bois});
    const Batiment mock_bat_4 = Batiment("Mock 4", type_batiment::Premiere, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Bois});
    const Batiment mock_bat_5 = Batiment("Mock 5", type_batiment::Premiere, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Bois});
    //const Batiment mock_bat_6 = Batiment("Mock 6", type_batiment::Premiere, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Pierre});
    my_box1.getJoueur(1)->addBatiment(&mock_bat_1);
    my_box1.getJoueur(1)->addBatiment(&mock_bat_2);
    my_box1.getJoueur(1)->addBatiment(&mock_bat_3);
    my_box1.getJoueur(1)->addBatiment(&mock_bat_4);
    my_box1.getJoueur(1)->addBatiment(&mock_bat_5);
    //my_box1.getJoueur(1)->addBatiment(&mock_bat_6);

    std::cout << "batiment de p2 : " << std::endl ; 
    displayCards( my_box1.getJoueur(1)->getBatiments() );

    const Perk* perk_1 = new Perk_CoinPerCard(2, type_batiment::Premiere);
    Commerce commerce_1 = Commerce("Commerce I", type_batiment::Commerce, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Argile, ressource::Pierre, ressource::Bois}, "", perk_1);
    my_box1.getJoueur(1)->addBatiment(&commerce_1);
    std::cout << "argile fetch de p2: " ;
    displayRessources( my_box1.getJoueur(1)->fetchRessource({ressource::Argile}) ) ; 
    std::cout << std::endl ;

    std::cout << "trésor p2 before perk : " << my_box1.getJoueur(1)->getTresor() << std::endl;
    commerce_1.getPerk()->onCall(my_box1.getJoueur(1));
    std::cout << "trésor p2 after perk : " << my_box1.getJoueur(1)->getTresor() << std::endl;

    const Perk* perk_2 = new Perk_FixedTrade({ressource::Argile}, 1);
    Commerce commerce_2 = Commerce("Commerce II", type_batiment::Commerce, phase_jeu::AGE_I, {}, 0, 0, 0, {}, "", perk_2);
    std::cout << "Trade price for p2 before perk : " << my_box1.getJoueur(1)->getTradePrice(ressource::Argile) << std::endl ; 
    commerce_2.onBuild(my_box1.getJoueur(1));
    std::cout << "Trade price for p2 after perk : " << my_box1.getJoueur(1)->getTradePrice(ressource::Argile) << std::endl << std::endl ; 

    const Batiment mock_bat_7 = Batiment("Mock 7", type_batiment::Premiere, phase_jeu::AGE_I, {ressource::Argile, ressource::Bois, ressource::Pierre, ressource::Verre, ressource::Papyrus}, 0, 0, 0, {ressource::Pierre});
    Commerce commerce_3 = Commerce("Commerce III", type_batiment::Commerce, phase_jeu::AGE_I, {}, 0, 0, 0, {ressource::Argile, ressource::Bois, ressource::Pierre});
    my_box1.getJoueur(1)->addBatiment(&commerce_3);
    my_box1.getJoueur(1)->achetableJoueur(mock_bat_7.getCoutRessource());

    std::cout << "trésor p2 before guild : " << my_box1.getJoueur(1)->getTresor() << std::endl;
    const Guilde guilde_1 = Guilde("Guilde I", type_batiment::Guilde, phase_jeu::AGE_III, {}, 0, 1, 0, {type_batiment::Premiere}, false);
    guilde_1.onBuild(my_box1.getJoueur(1));
    std::cout << "trésor p2 after guild : " << my_box1.getJoueur(1)->getTresor() << std::endl;
    std::cout << "points de victoire granted by guild: " << guilde_1.ptVictoireFinJeu(my_box1.getJoueur(1)) << std::endl;
    
    //Perk* perk_3 = new Perk_PolyRessource({ressource::Argile, ressource::Pierre, ressource::Bois});
    //std::cout << "PERK 3 IS POLY RES ? " << perk_3->isPolyRes() << std::endl;
    //delete perk_3 ; 

    //delete perk_2 ; 
    //delete perk_1 ;

    my_wonder1.onBuild(my_box1.getJoueur(1));

    std::cout << std::endl ; 
    my_box1.getJoueur(0)->addTresor(10); my_box1.getJoueur(1)->addTresor(10);
    std::cout << "trésor p0 : " << my_box1.getJoueur(0)->getTresor() << " ; trésor p1 " << my_box1.getJoueur(1)->getTresor() << std::endl;
    my_box1.getPlateau()->movePion(0, 3);
    std::cout << "trésor p0 : " << my_box1.getJoueur(0)->getTresor() << " ; trésor p1 " << my_box1.getJoueur(1)->getTresor() << std::endl;
    my_box1.getPlateau()->movePion(1, 6);
    std::cout << "trésor p0 : " << my_box1.getJoueur(0)->getTresor() << " ; trésor p1 " << my_box1.getJoueur(1)->getTresor() << std::endl;
    my_box1.getPlateau()->movePion(0, 9);
    std::cout << "trésor p0 : " << my_box1.getJoueur(0)->getTresor() << " ; trésor p1 " << my_box1.getJoueur(1)->getTresor() << std::endl;
    std::cout << "points de victoire: " << my_box1.getPlateau()->pointsVictoire() << std::endl; 

    
    } catch(const GameException& e) {

        std::cerr << e.getInfo() << std::endl; 

    }

    return 0 ; 
    
}

int main(){

    tests() ;
    std::cout << std::endl << "7 WONDERS DUEL" << std::endl << "--------------" << std::endl  << std::endl ;
    /*
    Box my_box = Box() ; 
    my_box.allCardsCreation();
    my_box.newAge();

    my_box.getPlateau()->getLayout()->displayLayout();
    displayCards( my_box.getPlateau()->getLayout()->getCards() ); 

    my_box.newAge();

    my_box.getPlateau()->getLayout()->displayLayout();
    displayCards( my_box.getPlateau()->getLayout()->getCards() ); 

    my_box.newAge();

    my_box.getPlateau()->getLayout()->displayLayout();
    displayCards( my_box.getPlateau()->getLayout()->getCards() ); 
    */

    //displayCards( my_box.getAllBatiments() );

    return 0 ;
}

// NILS TO DO :

// CURRENT :


// NEXT : 


// MAIN QUESTS : 
// effet des Jetons
// distribution (début de partie) -> initialiser le plateau avec 5 jetons


// OTHER TASKS : 
// implémenter un système pour communiquer simplement avec le joueur (choix...) : prendre en compte l'IA
// interactions avec le joueur (perks notamment)
// tours de jeu 
// début de jeu
// fin de jeu, compter les points, recommencer une partie


// SIDE QUESTS : 
// écrire une documentation et expliquer les choix de développement
// enhanced console display (Layout, Plateau)

// rendre Box singleton
// rendre Joueur doubleton
// méthode static pour track les instances Jeton
