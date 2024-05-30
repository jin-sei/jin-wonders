#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <algorithm>
#include <random>


//enum class ressource {Papyrus, Verre, Pierre, Argile, Bois};
//enum class symbole_scientifique {Roue, Compas, Pilon, Tablette, Lyre, Mesure, Telescope};

enum class type_batiment {Militaire, Scientifique, Manufacture, Premiere, Civil, Commerce, Guilde, Merveille};
enum class jeton_progres{Agriculture, Architecture, Economie, Loi, Maconnerie, Mathematiques,Philosophie, Strategie, Theologie, Urbanisme};
enum class phase_jeu {START=0, AGE_I=1, AGE_II=2, AGE_III=3, END=4};

enum class ressource {Bouclier, Papyrus, Verre, Pierre, Argile, Bois, Roue, Compas, Pilon, Tablette, Lyre, Mesure, Telescope};
// toutes les ressources génériques sont centralisées dans cet enum : 
// Boucliers, Matières Premières, Produits Manufacturés, Symbols Scientifiques

std::set<ressource> getMatierePremiere();
std::set<ressource> getProduitManufacture();
std::set<ressource> getRessource();
std::set<ressource> getSymboleScientifique();

std::string tostringRessources(ressource r);
std::string tostringType(type_batiment t);
std::string tostringAge(phase_jeu p);

phase_jeu& operator++(phase_jeu& phase);

class GameException {
	public:
		GameException(const std::string& i) :info(i) {}
		std::string getInfo() const { return info; }
	private:
		std::string info;
};

class Carte {
    public: 

        Carte(std::string nom, type_batiment type, phase_jeu age=phase_jeu::AGE_I, std::list<ressource> cost_r = {}, unsigned int cost_m = 0, unsigned int argent = 0, unsigned int pt_victoire = 0);

        // GETTERS
        std::string getNom() const { return nom ; }
        type_batiment getType() const { return type ;}
        phase_jeu getAge() const { return c_age ; }
        unsigned int getCoutArgent() const { return cost_m ; }
        unsigned int getRewardArgent() const { return argent ; }
        unsigned int getPointVictoire() const { return pt_victoire ;}
        std::list<ressource> getCoutRessource() const { return cost_r ;}

        // SETTERS
        void setNom(std::string new_nom){ nom = new_nom ;}
        //void setType(type_batiment new_type) {type = new_type ;} //  attribut const
        void setAge(phase_jeu p){ c_age = p ;}
        void setCoutArgent(unsigned int new_cost_m) { cost_m = new_cost_m ;}
        void setRewardArgent(unsigned int new_argent) { argent = new_argent ;}
        void setPointVictoire(unsigned int new_pt_victoire) { pt_victoire = new_pt_victoire ;}
        void setCoutRessource(std::list<ressource> cost) ;

        // UTILS
        bool achetableRessource(std::list<ressource> buy) const ; 
    
    protected : 

        bool checkTypeRessources(std::list<ressource> cost_r, std::set<ressource> subset) const;
        // vérifier que les ressources entrées appartiennent à la bonne catégorie

    private:
        std::string nom ;
        const type_batiment type ;
        phase_jeu c_age ; 
        std::list<ressource> cost_r ; // cout en ressources
        unsigned int cost_m ; // cout en argent

        unsigned int argent ;
        unsigned int pt_victoire ;
};

std::ostream& operator<<(std::ostream& f, Carte c);

class Batiment : public Carte { 
    // Civil, Scientifique, Militaire, Ressources
    public:

        Batiment(
            std::string nom, type_batiment type, phase_jeu age=phase_jeu::AGE_I,
            std::list<ressource> cost_r={}, unsigned int cost=0, 
            unsigned int argent=0, unsigned int pt_victoire=0,

            std::list<ressource> production={}, std::string chained_by=""
            );
        
        // GETTERS
        std::string getChainage() const { return chained_by;}
        std::list<ressource> getProduction() const { return production ;}

        // SETTERS
        void setChainage(std::string new_chain) { chained_by = new_chain;}
        void setProduction(std::list<ressource> new_prod) { production = new_prod ;}


    private:
        std::list<ressource> production ;
        std::string chained_by ; 
};

class Guilde : public Carte {
    public:
    private:
        type_batiment affectation ; 
        bool usurier ; 
};

class Commerce : public Batiment {
    public:
    private:
};

class Merveille : public Carte {
    public:
        Merveille(std::string nom, type_batiment type=type_batiment::Merveille, phase_jeu age=phase_jeu::AGE_I, std::list<ressource> cost_r = {}, unsigned int cost_m = 0, unsigned int argent = 0, unsigned int pt_victoire = 0, bool b=false) : Carte(nom, type, age, cost_r, cost_m, argent, pt_victoire), replay(b) {
            if(type!=type_batiment::Merveille){
                throw GameException("Merveille instanciée avec un type autre que Merveille");
            }
        }; 

        //GETTERS
        bool getReplay() const { return replay ;}

        //SETTERS
        void setReplay(bool b) { replay = b ;}

    private:
        bool replay ; 
};

class Jeton {
    public:
    private:
        jeton_progres id ; 
};

class Joueur {
    public:

        void setAdversaire(Joueur* j){ adversaire = j ;}

    private:

        Joueur* adversaire ;

};

class Layout {

// 0 : inexistante
// 1 : carte visible et accessible
// 2 : carte visible
// 3 : carte cachée
// 4 : inexistante (mais anciennement occupée)

    public:

        void inputCards(std::vector<Carte*> deck);
        void displayLayout();
        void displayCards();
        std::list<int> getAvailableSlots();
        bool isEmpty();
        unsigned int getLayoutSize();
        unsigned int getVectorSize();
        std::vector<Carte*> getCards() const { return cards ;}
        
        void switchAge(phase_jeu p);

        Carte* pickSlot(int i, int j);
        // update le layout, retourne la Carte choisie et update cards
        // seulement pour les slots 1 

        unsigned int getBatimentFromLayout(int i, int j);
        // retourne l'int de la position de la Carte dans cards à partir de i et j
        // pour toutes les cartes du layout 

    private:

        void updateLayout();

        std::vector<Carte*> cards ;
        std::vector<std::vector<int>> age = ageI ; 

        const std::vector<std::vector<int>> ageI { // AGE I
            {2, 2, 0, 0, 0, 0},
            {3, 3, 3, 0, 0, 0},
            {2, 2, 2, 2, 0, 0},
            {3, 3, 3, 3, 3, 0},
            {1, 1, 1, 1, 1, 1},
        };

        const std::vector<std::vector<int>> ageII = { // AGE II
            {2, 2, 2, 2, 2, 2},
            {0, 3, 3, 3, 3, 3},
            {0, 0, 2, 2, 2, 2},
            {0, 0, 0, 3, 3, 3},
            {0, 0, 0, 0, 1, 1},
        };

        const std::vector<std::vector<int>> ageIII = { // AGE III
            {2, 2, 0, 0, 0},
            {3, 3, 3, 0, 0},
            {2, 2, 2, 2, 0},
            {0, 3, 0, 3, 0},
            {0, 2, 2, 2, 2},
            {0, 0, 3, 3, 3},
            {0, 0, 0, 1, 1},
        };
};

class Plateau {
    public:
        // le plateau est responsable du layout qu'il gère

        Plateau();
        ~Plateau();
        Layout* getLayout() const { return layout; }

    private:

        Layout* layout ;

        int pion_militaire = 0 ; // between -9 and +9
        unsigned int saccages[4] = {5, 2, 2, 5};

        std::list<Jeton> jeton ;
        
};

class Box { 
    // responsable de toutes les Cartes, Jetons, Merveilles
    // SHOULD BE SINGLETON

    public:

        Box();
        ~Box();

        void allCardsCreation();
        void displayAllCards(); 
        void newAge();
        void distributeCards(phase_jeu p);

        Plateau* getPlateau() const { return plateau ;}

    private:

        Plateau* plateau ; 

        Joueur* joueur1 ; 
        Joueur* joueur2 ;

        phase_jeu phase ;

        std::list<Jeton*> all_jetons ;
        std::list<Carte*> all_batiments ;
        std::list<Merveille*> all_merveilles ;

        std::list<Batiment*> defausse ; 
};
