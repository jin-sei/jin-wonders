#include "wonders.h"

void Box::allCardsCreation(){

    // 23 cartes Âge I
    // 23 cartes Âge II
    // 20 cartes Âge III
    // 7 cartes Guilde
    // 12 cartes Merveille

    all_batiments.push_back( new Batiment(
            "Chantier", 
            type_batiment::Premiere, 
            phase_jeu::AGE_I,
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bois}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Commerce(
        "Depot d'Argile", 
        type_batiment::Commerce,
        phase_jeu::AGE_I,
        {}, // coût en ressources
        3, // coût en argent
        0, // récompense en argent
        0, // points de victoire
        {}, // production
        "", // chaînage
        new Perk_FixedTrade({ressource::Argile}, 1) // perk
    ));

    all_batiments.push_back( new Commerce(
        "Depot de Pierre", 
        type_batiment::Commerce,
        phase_jeu::AGE_I,
        {}, // coût en ressources
        3, // coût en argent
        0, // récompense en argent
        0, // points de victoire
        {}, // production
        "", // chaînage
        new Perk_FixedTrade({ressource::Pierre}, 1) // perk
    ));

    all_batiments.push_back( new Commerce(
        "Depot de Bois", 
        type_batiment::Commerce,
        phase_jeu::AGE_I,
        {}, // coût en ressources
        3, // coût en argent
        0, // récompense en argent
        0, // points de victoire
        {}, // production
        "", // chaînage
        new Perk_FixedTrade({ressource::Bois}, 1) // perk
    ));

    all_batiments.push_back( new Commerce(
        "Taverne", 
        type_batiment::Commerce,
        phase_jeu::AGE_I,
        {}, // coût en ressources
        0, // coût en argent
        4, // récompense en argent
        0, // points de victoire
        {}, // production
        "", // chaînage
        nullptr // perk
    ));

    all_batiments.push_back( new Batiment(
            "Exploitation", 
            type_batiment::Premiere, 
            phase_jeu::AGE_I,
            {}, // Liste des ressource nécéssaires
            1, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bois}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Bassin argileux", 
            type_batiment::Premiere, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Argile}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Cavite", 
            type_batiment::Premiere, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            1, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Argile}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Gisement", 
            type_batiment::Premiere, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Pierre}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Mine", 
            type_batiment::Premiere, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            1, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Pierre}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Verrerie", 
            type_batiment::Manufacture, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            1, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Verre}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Presse", 
            type_batiment::Manufacture, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            1, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Verre}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Tour de garde", 
            type_batiment::Militaire, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Atelier", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_I, 
            {ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            1, // Points de victoire
            {ressource::Compas}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "apothicaire", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_I, 
            {ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            1, // Points de victoire
            {ressource::Roue}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));




    all_batiments.push_back( new Batiment(
            "Ecuries", 
            type_batiment::Militaire, 
            phase_jeu::AGE_I, 
            {ressource::Bois}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Caserne", 
            type_batiment::Militaire, 
            phase_jeu::AGE_I, 
            {ressource::Argile}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Palissade", 
            type_batiment::Militaire, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            2, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Scriptorium", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            2, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Plume}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Officine", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            2, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Pilon}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Theatre", 
            type_batiment::Civil, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            3, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Autel", 
            type_batiment::Civil, 
            phase_jeu::AGE_I, 
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            3, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));


    all_batiments.push_back( new Batiment(
            "Bains", 
            type_batiment::Civil, 
            phase_jeu::AGE_I, 
            {ressource::Pierre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            3, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Commerce(
        "Brasserie", 
        type_batiment::Commerce,
        phase_jeu::AGE_II,
        {}, // coût en ressources
        6, // coût en argent
        0, // récompense en argent
        0, // points de victoire
        {}, // production
        "", // chaînage
        nullptr // perk
    ));

    all_batiments.push_back( new Commerce(
        "Forum", 
        type_batiment::Commerce,
        phase_jeu::AGE_II,
        {ressource::Argile}, // coût en ressources
        3, // coût en argent
        0, // récompense en argent
        0, // points de victoire
        {ressource::Papyrus, ressource::Verre}, // production
        "", // chaînage
        nullptr // perk
    ));

    all_batiments.push_back( new Commerce(
        "Caravanserail", 
        type_batiment::Commerce,
        phase_jeu::AGE_II,
        {ressource::Verre, ressource::Papyrus}, // coût en ressources
        2, // coût en argent
        0, // récompense en argent
        0, // points de victoire
        {ressource::Argile, ressource::Bois, ressource::Pierre}, // production
        "", // chaînage
        nullptr // perk
    ));

    all_batiments.push_back( new Commerce(
        "Douanes", 
        type_batiment::Commerce,
        phase_jeu::AGE_II,
        {}, // coût en ressources
        4, // coût en argent
        0, // récompense en argent
        0, // points de victoire
        {}, // production
        "", // chaînage
        new Perk_FixedTrade({ressource::Papyrus, ressource::Verre}, 1) // perk
    ));

    all_batiments.push_back( new Batiment(
            "Scierie", 
            type_batiment::Premiere, 
            phase_jeu::AGE_II, 
            {}, // Liste des ressource nécéssaires
            2, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bois,ressource::Bois}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Briqueterie", 
            type_batiment::Premiere, 
            phase_jeu::AGE_II, 
            {}, // Liste des ressource nécéssaires
            2, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Argile,ressource::Argile}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Carriere", 
            type_batiment::Premiere, 
            phase_jeu::AGE_II, 
            {}, // Liste des ressource nécéssaires
            2, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Pierre,ressource::Pierre}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Soufflerie", 
            type_batiment::Manufacture, 
            phase_jeu::AGE_II, 
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Verre}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Sechoir", 
            type_batiment::Manufacture, 
            phase_jeu::AGE_II, 
            {}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Papyrus}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Muraille", 
            type_batiment::Militaire, 
            phase_jeu::AGE_II, 
            {ressource::Pierre, ressource::Pierre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Tribunal", 
            type_batiment::Civil, 
            phase_jeu::AGE_II, 
            {ressource::Bois, ressource::Bois, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            5, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Haras", 
            type_batiment::Militaire, 
            phase_jeu::AGE_II, 
            {ressource::Argile, ressource::Bois}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "Ecuries" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Baraquements", 
            type_batiment::Militaire, 
            phase_jeu::AGE_II, 
            {}, // Liste des ressource nécéssaires
            3, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "Caserne" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Champ de tir", 
            type_batiment::Militaire, 
            phase_jeu::AGE_II, 
            {ressource::Pierre, ressource::Bois, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Place d'arme", 
            type_batiment::Militaire, 
            phase_jeu::AGE_II, 
            {ressource::Argile, ressource::Argile, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Bibliotheque", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_II, 
            {ressource::Pierre, ressource::Bois, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            2, // Points de victoire
            {ressource::Plume}, // Liste des ressource produites par le bâtiment
            "Scriptorium" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Dispensaire", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_II, 
            {ressource::Argile, ressource::Argile, ressource::Pierre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            2, // Points de victoire
            {ressource::Pilon}, // Liste des ressource produites par le bâtiment
            "Officine" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Ecole", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_II, 
            {ressource::Bois, ressource::Papyrus, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            1, // Points de victoire
            {ressource::Roue}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Laboratoire", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_II, 
            {ressource::Bois, ressource::Verre, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            1, // Points de victoire
            {ressource::Compas}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Statue", 
            type_batiment::Civil, 
            phase_jeu::AGE_II, 
            {ressource::Argile, ressource::Argile}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            4, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "Theatre" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Temple", 
            type_batiment::Civil, 
            phase_jeu::AGE_II, 
            {ressource::Bois, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            4, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "Autel" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Aqueduc", 
            type_batiment::Civil, 
            phase_jeu::AGE_II, 
            {ressource::Pierre, ressource::Pierre, ressource::Pierre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            5, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "Bains" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Rostres", 
            type_batiment::Civil, 
            phase_jeu::AGE_II, 
            {ressource::Pierre, ressource::Bois}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            4, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Commerce(
        "Chambre de Commerce", 
        type_batiment::Commerce,
        phase_jeu::AGE_III,
        {ressource::Papyrus, ressource::Papyrus}, // coût en ressources
        0, // coût en argent
        0, // récompense en argent
        3, // points de victoire
        {}, // production
        "", // chaînage
        new Perk_CoinPerCard(3, type_batiment::Manufacture) // perk
    ));

    all_batiments.push_back( new Commerce(
        "Port", 
        type_batiment::Commerce,
        phase_jeu::AGE_III,
        {ressource::Bois, ressource::Verre, ressource::Papyrus}, // coût en ressources
        0, // coût en argent
        0, // récompense en argent
        3, // points de victoire
        {}, // production
        "", // chaînage
        new Perk_CoinPerCard(2, type_batiment::Premiere) // perk
    ));

    all_batiments.push_back( new Commerce(
        "Armurerie", 
        type_batiment::Commerce,
        phase_jeu::AGE_III,
        {ressource::Pierre, ressource::Pierre, ressource::Verre}, // coût en ressources
        0, // coût en argent
        0, // récompense en argent
        3, // points de victoire
        {}, // production
        "", // chaînage
        new Perk_CoinPerCard(1, type_batiment::Militaire) // perk
    ));

    all_batiments.push_back( new Commerce(
        "Phare", 
        type_batiment::Commerce,
        phase_jeu::AGE_III,
        {ressource::Argile, ressource::Argile, ressource::Verre}, // coût en ressources
        0, // coût en argent
        0, // récompense en argent
        3, // points de victoire
        {}, // production
        "Taverne", // chaînage
        new Perk_CoinPerCard(1, type_batiment::Commerce) // perk
    ));

    all_batiments.push_back( new Commerce(
        "Arène", 
        type_batiment::Commerce,
        phase_jeu::AGE_III,
        {ressource::Argile, ressource::Pierre, ressource::Bois}, // coût en ressources
        0, // coût en argent
        0, // récompense en argent
        3, // points de victoire
        {}, // production
        "Brasserie", // chaînage
        new Perk_CoinPerCard(2, type_batiment::Merveille) // perk
    ));

    all_batiments.push_back( new Batiment(
            "Arsenal", 
            type_batiment::Militaire, 
            phase_jeu::AGE_III, 
            {ressource::Argile, ressource::Argile, ressource::Argile, ressource::Bois, ressource::Bois}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Pretoire", 
            type_batiment::Militaire, 
            phase_jeu::AGE_III, 
            {}, // Liste des ressource nécéssaires
            8, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Academie", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_III, 
            {ressource::Pierre, ressource::Bois, ressource::Verre, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            3, // Points de victoire
            {ressource::Cadran}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Etude", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_III, 
            {ressource::Bois, ressource::Bois, ressource::Verre, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            3, // Points de victoire
            {ressource::Cadran}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Palace", 
            type_batiment::Civil, 
            phase_jeu::AGE_III, 
            {ressource::Argile, ressource::Pierre, ressource::Bois, ressource::Verre, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            7, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Hotel de ville", 
            type_batiment::Civil, 
            phase_jeu::AGE_III, 
            {ressource::Pierre, ressource::Pierre, ressource::Pierre, ressource::Bois, ressource::Bois}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            7, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Obelisque", 
            type_batiment::Civil, 
            phase_jeu::AGE_III, 
            {ressource::Pierre, ressource::Pierre, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            5, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Fortifications", 
            type_batiment::Militaire, 
            phase_jeu::AGE_III, 
            {ressource::Pierre, ressource::Pierre, ressource::Argile, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "Palissade" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Atelier de siege", 
            type_batiment::Militaire, 
            phase_jeu::AGE_III, 
            {ressource::Bois, ressource::Bois, ressource::Bois, ressource::Verre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "Champ de tir" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Cirque", 
            type_batiment::Militaire, 
            phase_jeu::AGE_III, 
            {ressource::Argile, ressource::Argile, ressource::Pierre, ressource::Pierre}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            0, // Points de victoire
            {ressource::Bouclier, ressource::Bouclier}, // Liste des ressource produites par le bâtiment
            "Place d'arme" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Universite", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_III, 
            {ressource::Argile, ressource::Verre, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            2, // Points de victoire
            {ressource::Telescope}, // Liste des ressource produites par le bâtiment
            "Ecole" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Observatoire", 
            type_batiment::Scientifique, 
            phase_jeu::AGE_III, 
            {ressource::Pierre, ressource::Papyrus, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            2, // Points de victoire
            {ressource::Telescope}, // Liste des ressource produites par le bâtiment
            "Laboratoire" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Jardins", 
            type_batiment::Civil, 
            phase_jeu::AGE_III, 
            {ressource::Argile, ressource::Argile, ressource::Bois, ressource::Bois}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            6, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "Statue" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Pantheon", 
            type_batiment::Civil, 
            phase_jeu::AGE_III, 
            {ressource::Argile, ressource::Bois, ressource::Papyrus, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            6, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "Temple" // Bâtiment chaîné
    ));

    all_batiments.push_back( new Batiment(
            "Senat", 
            type_batiment::Civil, 
            phase_jeu::AGE_III, 
            {ressource::Argile, ressource::Argile, ressource::Pierre, ressource::Papyrus}, // Liste des ressource nécéssaires
            0, // Coût en argent
            0, // Récompense en argent
            5, // Points de victoire
            {}, // Liste des ressource produites par le bâtiment
            "Rostres" // Bâtiment chaîné
    ));

    // MOCK CARDS TO TEST THE GAME : TO BE REMOVED
    /*
    phase_jeu p = phase_jeu::AGE_I ;

    for(size_t i = 0 ; i < 66 ; i++){

        if( i < 23 ){ p = phase_jeu::AGE_I ; }
        else if ( i < 46 ){ p = phase_jeu::AGE_II ;  }
        else if ( i < 66 ){ p = phase_jeu::AGE_III ; }

        //const Batiment* new_bat = new new Batiment(...)
        all_batiments.push_back(  new new Batiment("Bâtiment Civil "+std::to_string(i+1), type_batiment::Civil, p) ));

    }
    */

}