#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <utility> // pair
#include <algorithm>
#include <random>
#include <cstdlib> // For abs()
#include <limits>
#include <exception>


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

class GameException : public std::exception {
	public:
		GameException(const std::string& i) :info(i) {}
        const char* what() const noexcept { return info.c_str(); }  
		std::string getInfo() const { return info; }
	private:
		std::string info;
};

void displayRessources(std::list<ressource> r);
void waitForInteraction() ;

template <typename T>
void displayPtVector(std::vector<const T*> c){
    for(auto iter = c.begin() ; iter != c.end() ; ++iter){
        std::cout << **iter << std::endl  ;
    }
    return;
}

template <typename T>
unsigned int askJoueur(std::vector<T> r){
    for( size_t i = 0 ; i < r.size() ; i++ ){
        std::cout << i << ". " << r[i] << std::endl;
    }
    std::cout << std::endl ; 

    unsigned int choice = r.size() ;

    std::cout << "0-" << r.size()-1 << " > " ;
    std::cin >> choice ;  

    while(choice >= r.size() || std::cin.fail() ){

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input
        
        std::cout << "0-" << r.size()-1 << " > " ;
        std::cin >> choice ;  
    }
    std::cout << std::endl;
    return choice ; 
}

template <typename T>
unsigned int askJoueur(std::vector<const T*> c){
    for( size_t i = 0 ; i < c.size() ; i++ ){
        std::cout << i << ". " ; 
        std::cout << *c[i] << std::endl ; 
    }

    unsigned int choice = c.size();

    std::cout << "0-" << c.size()-1 << " > " ;
    std::cin >> choice ; 

    while( choice >= c.size() || std::cin.fail()){

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input

        std::cout << "0-" << c.size()-1 << " > " ;
        std::cin >> choice ;

    }
    std::cout << std::endl;
    return choice ;
}

// FORWARD DECLARATION
class Joueur ; 
class Plateau ;
class Perk ;
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
        const std::list<ressource>& getCoutRessource() const { return cost_r ;}

        // SETTERS (inutile car objets constants)
        void setNom(std::string new_nom){ nom = new_nom ;}
        //void setType(type_batiment new_type) {type = new_type ;} //  attribut const
        void setAge(phase_jeu p){ c_age = p ;}
        void setCoutArgent(unsigned int new_cost_m) { cost_m = new_cost_m ;}
        void setRewardArgent(unsigned int new_argent) { argent = new_argent ;}
        void setPointVictoire(unsigned int new_pt_victoire) { pt_victoire = new_pt_victoire ;}
        void setCoutRessource(std::list<ressource> cost) ;

        // UTILS
        // retourne la liste des ressources manquante pour acheter la Carte

        virtual void affichage() const ;
        virtual void onBuild(Joueur& j) const = 0; // Joueur qui a construit la carte
    
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
        const std::list<ressource>& getProduction() const { return production ;}

        // SETTERS (inutiles car on utilise uniquement des pointeurs vers objets constants)
        void setChainage(std::string new_chain) { chained_by = new_chain;}
        void setProduction(std::list<ressource> new_prod) { production = new_prod ;}

        void affichage() const override ;
        void onBuild(Joueur& j) const override ; 


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

        void onBuild(Joueur& j) const override ;

    protected:

        const Perk* perk ;
};

class Merveille : public Commerce {
    public:
        Merveille(std::string nom, type_batiment type=type_batiment::Merveille, phase_jeu age=phase_jeu::AGE_I, std::list<ressource> cost_r = {}, unsigned int cost_m = 0, unsigned int argent = 0, unsigned int pt_victoire = 0, std::list<ressource> prod={}, std::string chained_by="", const Perk* perk=nullptr, bool b=false) : 
        Commerce(nom, type, age, cost_r, cost_m, argent, pt_victoire, prod, chained_by, perk), replay(b) {
            if(type!=type_batiment::Merveille){
                throw GameException("ERREUR: Merveille instanciée avec un type autre que Merveille");
            }
            if(chained_by != ""){
                throw GameException("ERREUR: une Merveille ne peut pas être chaîneée");
            }
        }; 

        //GETTERS
        bool getReplay() const { return replay ;}

        //SETTERS
        void setReplay(bool b) { replay = b ;}

    private:

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

        void onBuild(Joueur& j) const override ;

    private:
        void rewardArgent(Joueur& j) const ;
        std::list<type_batiment> affectation ; 
        bool usurier ; 
};


class Jeton {
    // classe inutile pour le moment mais on pourra faire une méthode static
    // pour vérifier que chaque jeton n'est instancié qu'une seule fois
    public:
        Jeton(jeton_progres id):id(id){

            auto it = std::find_if(instances.begin(), instances.end(), [id](const Jeton* j){
                return j->getId() == id;  
            });
            if(it == instances.end()){
                instances.push_back(this);
                return ;
            } else {
                throw GameException("ERREUR: Deux jetons identitiques instanciés");
            }
        }

        const jeton_progres getId() const { return id; }

    private:
        const jeton_progres id ;
        static std::vector<const Jeton*> instances ;
};

std::ostream& operator<<(std::ostream& f, const Jeton& c);

class Joueur {
    // pas responsable de la durée de vie de ses cartes

    public:

        Joueur(bool id, std::string nom) : id(id), nom(nom){

            reinitTradePrice();
        }

        unsigned int getId() const { return id ;}
        std::string getNom() const { return nom ; }

        Joueur& getAdversaire() const { return *adversaire ; }
        void setAdversaire(Joueur* j){ adversaire = j ;}

        const std::vector<const Batiment*>& getBatiments() const { return batiments; }
        const std::vector<const Jeton*>& getJetons() const { return jetons; }
        std::vector<const Batiment*> getBatimentsPerType(type_batiment t) const ;
        std::vector<const Merveille*> getInactiveMerveille() const ;
        std::vector<const Merveille*> getActiveMerveille() const ;

        void addCarte(const Carte& c); // gère le downcasting pour ajouter dans la bonne catégorie

        void addBatiment(const Batiment& c){batiments.push_back(&c);}
        void addMerveille(const Merveille& m){merveilles.push_back(&m);}
        void addJeton(const Jeton& j){jetons.push_back(&j);}
        void addGuilde(const Guilde& c){guildes.push_back(&c);}
        void destroyBatiment(const Batiment& c) ;

        unsigned int getTresor() const { return tresor ; }
        void setTresor(unsigned int t){tresor = t ;}
        void addTresor(unsigned int t){tresor += t;}
        void subTresor(unsigned int t){ if(tresor <= t){tresor = 0 ;} else { tresor -= t ;} }

        bool possessBatiment(std::string s) const;
        bool possessJeton(jeton_progres id) const;

        // achat
        std::list<ressource> achetableRessource(const std::list<ressource> cost) const;
        unsigned int achetableJoueur(const Carte& c) const ;
        std::vector<const Merveille*> buildableMerveilles() const ; 
        void activateMerveille(const Merveille& c); 
        void deleteLastMerveille() ;
        bool obtainable(const Carte& c) const ;

        // fetch military, fetch science
        std::list<ressource> fetchRessource(std::list<ressource> r) const ;
        unsigned int fetchPtVictoire(bool tiebreaker) const ;

        // utils pour les guildes et cartes commerces
        unsigned int getNumberActiveMerveilles() const ;
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

        // utils
        void displayJoueur() const ;
        void reinit();

        void operator<<(const Carte& c);

    private:

        Joueur* adversaire ;
        std::vector<const Jeton*> jetons ;
        std::vector<const Batiment*> batiments ;
        std::vector<const Guilde*> guildes ; 
        std::vector<const Merveille*> merveilles ;

        std::map<ressource, unsigned int> fixed_trade ;
        // prix fixé du commerce : 0 = non fixé, other than 0 = fixed price

        unsigned int tresor = 0 ;
        bool merveille_active[4] = {false, false, false, false};

        bool id ; // 0 or 1
        std::string nom ; 

};
class Perk { // ABSTRACT

    public: // PERK: ON CALL
    
        virtual void onCall(Joueur& j) const = 0 ; // PURE VIRTUAL
        // on prend en paramètre le joueur qui a construit la carte

        //~Perk(){} // vtable error paranoia ???
        //bool isPolyRes(); 

    private:

};

class Perk_CoinPerCard : public Perk {

    public: 
        Perk_CoinPerCard(Box& box, unsigned int coin, type_batiment card):coin(coin), card(card), box(box){}
        //~Perk_CoinPerCard(){};

        void onCall(Joueur& j) const override ;

    private: // perk settings
        void gainCoinPerCard(Joueur& j) const ;
        Box& box; 
        unsigned int coin ; // nombre de pièces que l'on gagne par carte
        type_batiment card ; // type de carte sur laquelle le calcul se base

}; 

class Perk_Destruction : public Perk { // requires player interaction
    public:
        Perk_Destruction(Box& box, type_batiment c);

        void onCall(Joueur& j) const override; 
    private:
        void destruction(Joueur& j) const ; 
        type_batiment card ; // type de Bâtiment autorisé à la destruction
        Box& box;
};

class Perk_FixedTrade : public Perk {

    public:
        Perk_FixedTrade(Box& box, std::list<ressource> res, unsigned int coin): res(res), coin(coin), box(box){}

        void onCall(Joueur& j) const override ; 
    private: // perk settings
        void setFixedTrade(Joueur& j) const ;
        std::list<ressource> res ; // ressource pour laquelle le prix de trade est fixé
        unsigned int coin ; // prix fixé
        Box& box ;

};

class Perk_Classic : public Perk { // PERKS W/O SETTINGS
// PICK JETONS
// FREE CONSTRUCTION FROM DEFAUSSE
// SACCAGE
    public: 
        Perk_Classic(Box& box, unsigned int id);

        void onCall(Joueur& j) const override;
    private:
        void saccage(Joueur& j) const ; // 0
        void freeConstructionFromDefausse(Joueur& j) const; // 2
        void pickJeton(Joueur& j) const; // 1
        unsigned int id ;
        Box& box;
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

        

        // UTILS
        void displayLayout() const ;
        bool isEmpty() const ; // all elements are picked
        unsigned int getLayoutSize() const; // counts non 0 and non 4 slots in age 2D vector
        unsigned int getVectorSize() const; // counts non nullptr elements in cards vector
        const std::vector<const Carte*>& getCards() const { return cards ;}

        // GESTION GLOBALE
        void switchAge(phase_jeu p);
        void reinit();
        void inputCards(std::vector<const Carte*> deck);

        // NEW ARCHITECTURE FOR LAYOUT (guaranteed not to be a mess by yours truly)

        // check integrity of the structures
        void checkMatching() const { 
            if( this->getLayoutSize() != this->getVectorSize() ){ 
                throw GameException("ERREUR : unmatched matrix ("+std::to_string(this->getLayoutSize())+") and vector ("+std::to_string(this->getVectorSize())+")" ); 
            }
        }

        // turn 2D Vector age into 1D
        std::vector<int> unroll() const ;
        unsigned int coordsToIndex(unsigned int x, unsigned int y) const ;
        std::pair<unsigned int, unsigned int> indexToCoords(unsigned int i) const ;
        unsigned int availableToAll(unsigned int i) const ; // the i-th available card is located at cards[availableToAll(i)]

        // returns a vector of visible cards (or only available if bool==true)
        std::vector<const Carte*> getVisibleCards(bool available_only) const;

        // removes the Card from the Layout (must be available)
        const Carte& removeCard(unsigned int x, unsigned int y); // coordonates from the 2D Vector
        const Carte& removeCard(unsigned int i); // index in Available Cards

        // read Card from the Layout (must be visible)
        const Carte& seeCard(unsigned int x, unsigned int y) const; // coordonates from the 2D Vector
        const Carte& seeCard(unsigned int i) const; // index in Visible Cards


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
        const std::vector<const Batiment*>& getAllBatiments() const { return all_batiments; }
        const std::vector<const Carte*>& getDefausse() const { return defausse ;}
        const std::vector<const Jeton*>& getUnusedJetons() const { return unused_jetons;}

        // GESTION DU JEU
        void gameLoop(); 
        void newAge();
        void reinitAll(); // on clear tout et on reviens au début du Jeu
        void setupAll(); // on prépare la partie
        void construireCarte(Joueur& j, const Carte& c);

        // UTILS
        Joueur& getCurrentJoueur() const { return *current ;}
        void switchCurrent() { current = &current->getAdversaire(); }
        void endgame() { phase = phase_jeu::AGE_III ; newAge() ;}
    
    protected:

        // SINGLETON
        static const Box& getInstance();


    private:

        void distributeCards(phase_jeu p); // utilisée dans newAge();
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

        std::vector<const Carte*> defausse ;
        std::vector<const Jeton*> unused_jetons ;

        // SINGLETON 
        Box(const Box& b) = delete; 
        Box& operator=(const Box&) = delete;

        static bool constructed;  

        /*
        struct Handler {
            Box* box = nullptr ;
            ~Handler() { delete box ; };
        };

        static Handler shell ;
        */
};

class Plateau { // le plateau est responsable du layout qu'il gère

    public:

        friend Box; 

        Plateau();
        ~Plateau();

        // GETTERS
        Layout* getLayout() const { return layout; }
        int getPionMilitaire() const { return pion_militaire; }
        const std::vector<const Jeton*>& getJetons() const { return jetons; }
        void addJeton(const Jeton& j) { jetons.push_back(&j); }

        const Jeton& takeJeton(unsigned int index);
        // renvoie le pointeur vers l'object jeton et le supprime du Plateau

        void displayPlateau() const ;
        // display le pion militaire, les jetons progrès et le layout 

        void movePion(bool id, unsigned int avance);
        // déplace le pion sur le plateau en utilisant l'ID du Joueur
        
        bool victoireMilitaire() const { return (pion_militaire == -9 || pion_militaire == 9); }
        // check victoire Militaire
        
        bool joueurDominant() const { return pion_militaire > 0 ;}
        // joueur qui a avancé le plus le pion vers la capitale ennemie
        
        unsigned int pointsVictoire() const ; 
        // retourne le nombre de points de victoire à attribuer au joueur dominant

        void reinit() ; 
        // clear & reinit all attributes
        

    private:

        Layout* layout ;

        int pion_militaire = 0 ; // between -9 and +9
        // se déplace vers le positif pour le joueur1, vers le négatif pour le joueur 0
        unsigned int saccage[4] = {2, 5, 2, 5};
        // 0 | 1 ; 2 | 3 ; 4 ; 5 | 6 ; 7 ; 8 | 9 

        std::vector<const Jeton*> jetons ;
        
};