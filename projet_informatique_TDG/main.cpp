#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    ///déclaration des variables utilisées pour les différentes saisies dans la main
    int saisie;
    int s;
    int a;
    int sortie;
    int save;
    int ind=-1;
    int somm_dep;
    int somm_ar;
    int weight;
    int valeur;
    std::string image;


    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");


    do
    {

        /// parmi 3 graphes à appeler

        std::cout << " Selectionner votre graphe ( 1 a 3) : " << std::endl;
        std::cout << "1 pour savane " << std::endl;
        std::cout << "2 pour aquatique " << std::endl;
        std::cout << "3 pour jungle " << std::endl;
        std::cin >> saisie;
        std::cout<<std::endl;
        std::cout<<"Commandes"<<std::endl;
        std::cout<<"A pour supprimer arc"<<std::endl;
        std::cout<<"S pour supprimer sommet"<<std::endl;
        std::cout<<"N pour ajouter arc"<<std::endl;
        std::cout<<"ESP pour ajouter sommet"<<std::endl;
        std::cout<<std::endl;

        Graph g;
        g.initialiser_graphe(saisie);
        g.make_example();

        /// Vous gardez la main sur la "boucle de jeu"
        /// ( contrairement à des frameworks plus avancés )
        while ( !key[KEY_ESC] )
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();

            ///boucle de jeu
            ///proposition à l'utilisateur de supprimer un arc
            if(key[KEY_A])
            {
                std::cout<<"Quel arc a supprimer ? "<<std::endl;
                std::cin>>a;
                g.enlever_arc(a);
            }

            ///proposition à l'utilisateur de supprimer un sommet
            if(key[KEY_S])
            {
                std::cout<<"Quel sommet a supprimer ? "<<std::endl;
                std::cin>>s;
                g.enlever_sommet(s);
            }

            ///proposition à l'utilisateur d'ajouter un arc
            if(key[KEY_N])
            {
                do
                {
                    std::cout<<"Rentrer l'indice du nouvel arc"<<std::endl;
                    std::cin>>ind;
                    if(ind<g.get_nb_arc())
                    {
                        std::cout<<"indice d'arc deja existant"<<std::endl;
                    }
                }
                while(ind>0 && ind<g.get_nb_arc());
                std::cout<<"Rentrer l'indice du sommet de depart (sommet present sur le graphe utilise)"<<std::endl;
                std::cin>>somm_dep;
                std::cout<<"Rentrer l'indice du sommet d'arrive (sommet present sur le graphe utilise)"<<std::endl;
                std::cin>>somm_ar;
                std::cout<<"Rentrer le poids de l'arc"<<std::endl;
                std::cin>>weight;
                g.ajouter_arc(ind,somm_dep,somm_ar,weight);
            }

            ///proposition à l'utilisateur d'ajouter un sommet
            if(key[KEY_SPACE])
            {
                do
                {
                    std::cout<<"Rentrer l'indice du nouveau sommet (superieur aux indices deja presents sur le graphe)"<<std::endl;
                    std::cin>>ind;
                    if(ind<g.get_nb_sommet())
                    {
                        std::cout<<"indice de sommet deja existant"<<std::endl;
                    }
                }
                while(ind>0 && ind<g.get_nb_sommet());
                std::cout<<"Rentrer la valeur de la population"<<std::endl;
                std::cin>>valeur;
                std::cout<<"Rentrer le nom de l'animal avec .jpg a la fin, parmi la liste suivante :"<<std::endl;
                std::cout<<"anaconda    babouin    buffle   chimpanze   crevette    elephant"<<std::endl;
                std::cout<<"espadon    fourmi   gazelle     gnou    guepard     hippopotame"<<std::endl;
                std::cout<<"hyene    jaguar     leopard     lion    mante_religieuse    matiere_orga"<<std::endl;
                std::cout<<"mygale   papillon   pelican     phacochere    phasme    phytoplancton"<<std::endl;
                std::cout<<"poisson     requin    tamanoir   tatou   vegetal   zebre    zooplancton_carni   zooplancton_herbi"<<std::endl;
                std::cin>>image;
                g.ajouter_sommet(ind,valeur, 0,0,image);

            }

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();

        }

        //g.ToutesComposantesConnexes();

        ///proposition à l'utilisateur de sauvegarder ses actions lorsqu'il veut quitter le graphe(hors de la boucle de jeu Escape donc)
        std::cout<<"Voulez vous sauvegarder ?"<<std::endl;
        std::cout<<"1-oui"<<std::endl;
        std::cout<<"0-non"<<std::endl;
        std::cin>>save;

        if(save==1)
        {
            g.sauvegarder_graphe(saisie);
            save=0;
        }
        ///proposition à l'utilisateur de quitter le programme ou bien de retourner au menu pour sélectionner un autre graphe
        std::cout<<"Voulez vous quitter le programme ?"<<std::endl;
        std::cout<<"1-oui"<<std::endl;
        std::cout<<"0-non (retour a la selection des graphes)"<<std::endl;
        std::cin>>sortie;

    }
    while(sortie!=1);

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


