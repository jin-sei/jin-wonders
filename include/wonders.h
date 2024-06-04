#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <random>
#include <cstdlib> // For abs()


enum class type_batiment {Militaire, Scientifique, Manufacture, Premiere, Civil, Commerce, Guilde, Merveille};
enum class jeton_progres{Agriculture, Architecture, Economie, Loi, Maconnerie, Mathematiques,Philosophie, Strategie, Theologie, Urbanisme};
enum class phase_jeu {START=0, AGE_I=1, AGE_II=2, AGE_III=3, END=4};
enum class ressource {Bouclier=0, Papyrus=1, Verre=2, Pierre=3, Argile=4, Bois=5, Telescope=6, Roue=7, Cadran=8, Pilon=9, Compas=10, Plume=11, Balance=12};
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

void displayRessources(std::list<ressource> r);
unsigned int askJoueur(std::vector<std::string> r);

class GameException {
	public:
		GameException(const std::string& i) :info(i) {}
		std::string getInfo() const { return info; }
	private:
		std::string info;
};

// FORWARD DECLARATION
class Perk ;
class Joueur ;
class Plateau ; 
class Box ;

class Carte { // ABSTRACT 

    // une fois créée par le contrôlleur Box (qui les gère),
    // les cartes sont immutables et toujours manipulés avec des pointeurs const

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
        std::list<ressource> achetableRessource(std::list<ressource> buy) const ; 
        // retourne la liste des ressources manquante pour acheter la Carte

        virtual void affichage() const ;
        virtual void onBuild(Joueur* j) const = 0; // Joueur qui a construit la carte
    
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

std::ostream& operator<<(std::ostream& f, const Carte& c);

template <typename T>
void displayFromPointerVector(std::vector<const T*> c){
    for(auto iter = c.begin() ; iter != c.end() ; ++iter){
        std::cout << **iter << std::endl  ;
    }
    return;
}

template <typename T>
const T* chooseFromPointerVector(std::vector<const T*> c){
    for( size_t i = 0 ; i < c.size() ; i++ ){
        std::cout << i << ". " ; 
        std::cout << *c[i] << std::endl << std::endl ; ; 
    }

    unsigned int choice = c.size();
    while( choice >= c.size() ){
        std::cout << "0-" << c.size()-1 << " > " ;
        std::cin >> choice ; 
    }
    return c[choice] ;
}

class Batiment : public Carte {
    // Civil, Scientifique, Militaire, Ressources
    public:

        Batiment(
            std::string nom, type_batiment type, phase_jeu age=phase_jeu::AGE_I,
            std::list<ressource> cost_r={}, unsigned int cost=0,
            unsigned int argent=0, unsigned int pt_victoire=0,

            std::list<ressource> prod={}, std::string chained_by=""
            );
        
        // GETTERS
        std::string getChainage() const { return chained_by;}
        std::list<ressource> getProduction() const { return production ;}

        // SETTERS
        void setChainage(std::string new_chain) { chained_by = new_chain;}
        void setProduction(std::list<ressource> new_prod) { production = new_prod ;}

        void affichage() const override ;
        void onBuild(Joueur* j) const override ; 


    private:
        std::list<ressource> production ;
        std::string chained_by ; 
};

class Commerce : public Batiment {
    // RESPONSABLE DE SA PERK !!!
    public:

        Commerce(std::string nom, type_batiment type, phase_jeu age=phase_jeu::AGE_I, std::list<ressource> cost_r={}, unsigned int cost=0, unsigned int argent=0, unsigned int pt_victoire=0, std::list<ressource> prod={}, std::string chained_by="", const Perk* perk=nullptr);
        ~Commerce();
        
        const Perk* getPerk() const { return perk; }

        void onBuild(Joueur* j) const override ;

    protected:

        const Perk* perk ;
};

class Merveille : public Commerce {
    public:
        Merveille(std::string nom, type_batiment type=type_batiment::Merveille, phase_jeu age=phase_jeu::AGE_I, std::list<ressource> cost_r = {}, unsigned int cost_m = 0, unsigned int argent = 0, unsigned int pt_victoire = 0, std::list<ressource> prod={}, std::string chained_by="", const Perk* perk=nullptr, bool b=false, Carte* f=nullptr) : 
        Commerce(nom, type, age, cost_r, cost_m, argent, pt_victoire, prod, chained_by, perk), replay(b), feed(f) {
            if(type!=type_batiment::Merveille){
                throw GameException("ERREUR: Merveille instanciée avec un type autre que Merveille");
            }
            if(chained_by != ""){
                throw GameException("ERREUR: une Merveille ne peut pas être chaîneée");
            }
        }; 

        //GETTERS
        bool getReplay() const { return replay ;}
        const Carte* getFeed() const { return feed ;}
        bool isFed() const { return feed != nullptr; }

        //SETTERS
        void setReplay(bool b) { replay = b ;}

        //void onBuild(Joueur* j) const override ; // Calls onBuild commerce

    private:

        const Carte* feed ;
        bool replay ;
};

class Guilde : public Carte {
    public:
        Guilde(
            std::string nom, type_batiment type, phase_jeu age=phase_jeu::AGE_I,
            std::list<ressource> cost_r={}, unsigned int cost=0,
            unsigned int argent=0, unsigned int pt_victoire=0,

            std::list<type_batiment> affectation={}, bool usurier=false
            );

        unsigned int ptVictoireFinJeu(const Joueur* j) const ;
        void rewardArgent(Joueur* j) const ;

        void onBuild(Joueur* j) const override ;

    private:
        std::list<type_batiment> affectation ; 
        bool usurier ; 
};


class Jeton {
    // classe inutile pour le moment mais on pourra faire une méthode static
    // pour vérifier que chaque jeton n'est instancié qu'une seule fois
    public:
        Jeton(jeton_progres id):id(id){}
        const jeton_progres getId() const { return id; }
    private:
        const jeton_progres id ; 
};

std::ostream& operator<<(std::ostream& f, const Jeton& c);

class Joueur {
    // pas responsable de la durée de vie de ses cartes

    public:

        Joueur(bool id) : id(id){

            reinitTradePrice();
        }

        unsigned int getId() const { return id ;}

        Joueur* getAdversaire() const { return adversaire ; }
        void setAdversaire(Joueur* j){ adversaire = j ;}

        std::vector<const Batiment*> getBatiments() const { return batiments; }
        std::vector<const Batiment*> getBatimentsPerType(type_batiment t) const ; 
        std::vector<const Jeton*> getJetons() const { return jetons; }

        void addBatiment(const Batiment* c){batiments.push_back(c);}
        void addJeton(const Jeton* j){jetons.push_back(j);}

        unsigned int getTresor() const { return tresor ; }
        void setTresor(unsigned int t){tresor = t ;}
        void addTresor(unsigned int t){tresor += t;}
        void subTresor(unsigned int t){ if(tresor <= t){tresor = 0 ;} else { tresor -= t ;} }

        bool possessBatiment(std::string s) const;
        bool possessJeton(jeton_progres id) const;

        // achat
        std::list<ressource> achetableRessource(std::list<ressource> cost) const;
        unsigned int achetableJoueur(const Carte* c) const ;

        // fetch military, fetch science
        std::list<ressource> fetchRessource(std::list<ressource> r) const ;
        unsigned int fetchPtVictoire(bool tiebreaker) const ;

        // utils pour les guildes et cartes commerces
        unsigned int getNumberActiveWonders() const ;
        unsigned int getNumberBatiment(type_batiment t) const ;

        // méthodes pour les jetons de progrès
        unsigned int getNumberUniqueSymbols() const ;
        unsigned int getNumberPairs() const ;
        bool allowJetonPick() const { return getNumberPairs() > jetons.size() ;}
        bool victoireScientifique() const { 
            return ((getNumberUniqueSymbols() + static_cast<int>(possessJeton(jeton_progres::Loi))) >= 6) ; 
        }

        // méthodes pour Trade
        unsigned int getFixedTrade(ressource r) const ;
        void setFixedTrade(ressource r, unsigned int price);
        unsigned int getTradePrice(ressource r) const ;
        void reinitTradePrice();

        void reinit();

    private:

        Joueur* adversaire ;
        std::vector<const Jeton*> jetons ;
        std::vector<const Batiment*> batiments ;
        std::vector<const Guilde*> guildes ; 
        std::vector<const Merveille*> merveilles ;

        std::map<ressource, unsigned int> fixed_trade ;
        // prix fixé du commerce : 0 = non fixé, other than 0 = fixed price

        unsigned int tresor = 0 ;

        bool id ; // 0 or 1

};

class Perk { // ABSTRACT

    public: // PERK: ON CALL
    
        virtual void onCall(Joueur* j) const = 0 ; // PURE VIRTUAL
        // on prend en paramètre le joueur qui a construit la carte

        //~Perk(){} // vtable error paranoia ???
        //bool isPolyRes(); 

    private:

};

class Perk_CoinPerCard : public Perk {

    public: 
        Perk_CoinPerCard(unsigned int coin, type_batiment card):coin(coin), card(card){}
        //~Perk_CoinPerCard(){};

        void gainCoinPerCard(Joueur* j) const ;
        void onCall(Joueur* j) const override ;

    private: // perk settings
        unsigned int coin ; // nombre de pièces que l'on gagne par carte
        type_batiment card ; // type de carte sur laquelle le calcul se base

}; 

class Perk_Destruction : public Perk { // requires player interaction
    public:
        Perk_Destruction(type_batiment c);

        void destruction(Joueur* j) const ; 
        void onCall(Joueur* j) const override; 
    private:
        type_batiment card ; // type de Bâtiment autorisé à la destruction
};

class Perk_FixedTrade : public Perk {

    public:
        Perk_FixedTrade(std::list<ressource> res, unsigned int coin): res(res), coin(coin){}

        void setFixedTrade(Joueur* j) const ;
        void onCall(Joueur* j) const override ; 
    private: // perk settings
        std::list<ressource> res ; // ressource pour laquelle le prix de trade est fixé
        unsigned int coin ; // prix fixé

};

class Perk_Classic : public Perk { // PERKS W/O SETTINGS
// PICK JETONS
// FREE CONSTRUCTION FROM DEFAUSSE
// SACCAGE
    public: 
        Perk_Classic(unsigned int id, const Box* box);

        void saccage(Joueur* j) const ; // 0
        void freeConstructionFromDefausse(Joueur* j) const; // 2
        void pickJeton(Joueur* j) const; // 1

        void onCall(Joueur* j) const override;
    private:
        unsigned int id ;
        const Box* box ; 
};

/* 

// La Perk PolyRessource est abandonnée
// On considère à la place que si un bâtiment de Commerce ou une Merveille produit des ressources,
// il s'agit d'une poly ressource

class Perk_PolyRessource : public Perk {
    public:
        Perk_PolyRessource(std::list<ressource> res):res(res){}

        std::list<ressource> getPolyRessources() const ;
        void onCall(Joueur* j) const override ; 
    private:
        std::list<ressource> res;
};
*/

class Layout {

// 0 : inexistante
// 1 : carte visible et accessible
// 2 : carte visible
// 3 : carte cachée
// 4 : inexistante (mais anciennement occupée)

    public:

        void inputCards(std::vector<const Carte*> deck);
        void displayLayout();
        //void displayCards();
        std::list<int> getAvailableSlots();
        bool isEmpty();
        unsigned int getLayoutSize();
        unsigned int getVectorSize();
        std::vector<const Carte*> getCards() const { return cards ;}
        
        void switchAge(phase_jeu p);

        const Carte* pickSlot(int i, int j);
        // update le layout, retourne la Carte choisie et update cards
        // seulement pour les slots 1 

        unsigned int getBatimentFromLayout(int i, int j);
        // retourne l'int de la position de la Carte dans cards à partir de i et j
        // pour toutes les cartes du layout 

        void reinit();

    private:

        void updateLayout();

        std::vector<const Carte*> cards ;
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

class Box { 
    // responsable de toutes les Cartes, Jetons, Merveilles
    // SHOULD BE SINGLETON

    public:

        Box();
        ~Box();

        // GETTERS
        Plateau* getPlateau() const { return plateau ;}
        Joueur* getJoueur(bool x) const { return x ? joueur1 : joueur0 ;}
        std::vector<const Batiment*> getAllBatiments() const { return all_batiments; }

        // GESTION DU JEU
        void newAge();
        void reinitAll(); // on clear tout et on reviens au début du Jeu
        void setupAll(); // on prépare la partie

        // UTILS
        Joueur* getCurrentJoueur() const { return current ;}
        void switchCurrent() { current = current->getAdversaire(); }


    private:

        void distributeCards(phase_jeu p); // utilisée dans newAge
        void allCardsCreation(); // dans instance.cpp, utilisée par le constructeur

        void choixMerveilles(); // called by setup()
        void setupJetons(); // called by setup();

        Plateau* plateau ; 

        Joueur* joueur0 ; Joueur* joueur1 ;
        Joueur* current ;

        phase_jeu phase ;

        std::vector<const Jeton*> all_jetons ;
        std::vector<const Batiment*> all_batiments ;
        std::vector<const Guilde*> all_guildes ;
        std::vector<const Merveille*> all_merveilles ;

        std::vector<const Carte*> defausse ; // NOT USED YET
        std::vector<const Jeton*> unused_jetons ; 
};

class Plateau {
    public:
        // le plateau est responsable du layout qu'il gère

        Plateau(Box* box);
        ~Plateau();

        // GETTERS
        Layout* getLayout() const { return layout; }
        int getPionMilitaire() const { return pion_militaire; }
        std::vector<const Jeton*> getJetons() const { return jetons; }
        void addJeton(const Jeton* j) { jetons.push_back(j); }

        const Jeton* takeJeton(jeton_progres id);
        // renvoie le pointeur vers l'object jeton et le supprime du Plateau

        void movePion(bool id, unsigned int avance);
        // déplace le pion sur le plateau en utilisant l'ID du Joueur
        
        bool victoireMilitaire() const { return (pion_militaire == -9 || pion_militaire == 9); }
        // check victoire Militaire
        
        bool joueurDominant() const { return box->getJoueur( pion_militaire > 0 )->getId() ; }
        // joueur qui a avancé le plus le pion vers la capitale ennemie
        
        unsigned int pointsVictoire() const ; 
        // retourne le nombre de points de victoire à attribuer au joueur dominant

        void reinit() ; 
        // clear & reinit all attributes
        

    private:

        Layout* layout ;
        Box* box ; 

        int pion_militaire = 0 ; // between -9 and +9
        // se déplace vers le positif pour le joueur1, vers le négatif pour le joueur 0
        unsigned int saccage[4] = {2, 5, 2, 5};
        // 0 | 1 ; 2 | 3 ; 4 ; 5 | 6 ; 7 ; 8 | 9 

        std::vector<const Jeton*> jetons ;
        
};