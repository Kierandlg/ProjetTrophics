#include <iostream>
#include <fstream>
#include <string>
#include <allegro.h>
#include <time.h>

#include "Sommet.h"
#include "Animal.h"
#include "Ressource.h"
#include "Graphe.h"

using namespace std;

void sauvegarde_a(Sommet *a);
void sauvegarde_r(Ressource *a);
void crea_ani(Graphe *graphe, int choixduso);
void crea_res(Graphe *graphe);
void adjacence(Graphe *graphe);
void crea_arc(Sommet *sommet);

void sauvegarde_graphe(Graphe *graphe);

//allegro
void initalleg();
int creationsommet(Graphe *graphe);
void tabdecommande();
void affichage(Sommet *a);

void lecturefichier(Graphe *graphe);



int main()
{
    Graphe *graphe=new Graphe;

    initalleg();
    tabdecommande();

    while (!key[KEY_ESC]){
        textprintf_ex(screen,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        textprintf_ex(screen,font,60,350,makecol(0,255,0),makecol(0,0,0),"%d",graphe->getnbsommets());
        int choixdusommet=0;
        choixdusommet=creationsommet(graphe);

        if(choixdusommet!=0){
            crea_ani(graphe,choixdusommet);
        }
        //lecturefichier(graphe);
        rest(20);
    }
    readkey();

    return 0;
}
END_OF_MAIN();



void sauvegarde_a(Sommet *a){

    ofstream monFlux("test.txt", ios::app); //app pour ajouter a la suite

    if(monFlux)  //On teste si tout est OK
    {
        monFlux << a->getnumani() << endl;
        monFlux << a->getposx()   << endl;
        monFlux << a->getposy()   << endl;
        monFlux << a->getqtn()    << endl;
        monFlux.close();
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}

void crea_ani(Graphe *graphe, int choixduso){


    srand(time(NULL));

    int xnouv=rand()%800;
    int ynouv=rand()%522;



    if(choixduso==1){
        Sommet *a = new Sommet;
        std::string name = "jaguar";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(1);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==2){
        Sommet *a = new Sommet;
        std::string name = "mygale";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(2);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==3){
        Sommet *a = new Sommet;
        std::string name = "mante";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(3);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==4){
        Sommet *a = new Sommet;
        std::string name = "papillon";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(4);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==5){
        Sommet *a = new Sommet;
        std::string name = "pelican";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(5);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==6){
        Sommet *a = new Sommet;
        std::string name = "phasme";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(6);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==7){
        Sommet *a = new Sommet;
        std::string name = "tamanoir";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(7);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==8){
        Sommet *a = new Sommet;
        std::string name = "tatou";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(8);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }

    if(choixduso==9){
        Sommet *a = new Sommet;
        std::string name = "vegetal";
        a->setnom(name);
        a->setposx(xnouv);
        a->setposy(ynouv);
        a->setnumani(9);
        graphe->setnbsommets();
    sauvegarde_a(a);
    sauvegarde_graphe(graphe);
    delete(a);
    }
}

void adjacence(Graphe *graphe){
    int **adja;
    int nColonnes=graphe->getnbsommets();
    int nLignes=graphe->getnbsommets();

    adja = new int* [ nLignes ];
    for (int i=0; i < nLignes; i++){
    adja[i] = new int[ nColonnes ];}

    for (int i=0; i < nLignes; i++) {
        for (int j=0; j < nColonnes; j++){
            cout << adja[i][j] << " ";
        }
        cout << endl;
    }
}

void crea_arc(Sommet *sommet){
    int choix=0;
    int choix2=0;
    int sommetvise;
    cout << "Voulez vous créé une liaison depuis ce sommet? (1 si oui 2 sinon)";
    cin  >> choix;
    if(choix==1){
        while(choix2!=1){
            cout << "Quel est le sommet visé?";
            cin  >> sommetvise;
        }
    }
}

void initalleg(){
    srand(time(NULL));
    allegro_init();
    install_mouse();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1080,622,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}

int creationsommet(Graphe *graphe){

    int verif=0;
    int onempechelasortie=0;
    int choixdusommet;


    if (mouse_b & 1  && mouse_x>=910 && mouse_x<=1070 && mouse_y>=10 && mouse_y<=50){
        rectfill(screen,820,0,900,360,makecol(50,150,0));

        line(screen,820,40,900,40,makecol(255,255,255));
        textprintf_ex(screen,font,830,15,makecol(0,0,0),-1,"Jaguar");
        line(screen,820,80,900,80,makecol(255,255,255));
        textprintf_ex(screen,font,830,55,makecol(0,0,0),-1,"Mygale");
        line(screen,820,120,900,120,makecol(255,255,255));
        textprintf_ex(screen,font,830,95,makecol(0,0,0),-1,"Mante-R");
        line(screen,820,160,900,160,makecol(255,255,255));
        textprintf_ex(screen,font,830,135,makecol(0,0,0),-1,"Papillon");
        line(screen,820,200,900,200,makecol(255,255,255));
        textprintf_ex(screen,font,830,175,makecol(0,0,0),-1,"Pelican");
        line(screen,820,240,900,240,makecol(255,255,255));
        textprintf_ex(screen,font,830,215,makecol(0,0,0),-1,"Phasme");
        line(screen,820,280,900,280,makecol(255,255,255));
        textprintf_ex(screen,font,830,255,makecol(0,0,0),-1,"Tamanoir");
        line(screen,820,320,900,320,makecol(255,255,255));
        textprintf_ex(screen,font,830,295,makecol(0,0,0),-1,"Tatou");
        textprintf_ex(screen,font,830,335,makecol(0,0,0),-1,"Vegetation");

        verif=1;
    }


    if(verif==1)
    {
        while(onempechelasortie!=1)
        {
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=0 && mouse_y<=40)
            {
                choixdusommet=1;
                onempechelasortie=1;

            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=40 && mouse_y<=80)
            {
                choixdusommet=2;
                onempechelasortie=1;
            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=80 && mouse_y<=120)
            {
                choixdusommet=3;
                onempechelasortie=1;
            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=120 && mouse_y<=160)
            {
                choixdusommet=4;
                onempechelasortie=1;
            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=160 && mouse_y<=200)
            {
                choixdusommet=5;
                onempechelasortie=1;
            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=200 && mouse_y<=240)
            {
                choixdusommet=6;
                onempechelasortie=1;
            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=240 && mouse_y<=280)
            {
                choixdusommet=7;
                onempechelasortie=1;
            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=280 && mouse_y<=320)
            {
                choixdusommet=8;
                onempechelasortie=1;
            }
            if(mouse_b & 1  && mouse_x>=820 && mouse_x<=900 && mouse_y>=320 && mouse_y<=360)
            {
                choixdusommet=9;
                onempechelasortie=1;
            }

        }
    }
    rectfill(screen,820,0,899,360,makecol(0,0,0));
    line(screen,900,0,900,622,makecol(255,255,255));
    return(choixdusommet);
}

void tabdecommande(){
    // TABLEAU DE COMMANDE
    int blanc = makecol(255,255,255);
    int noir  = makecol(0,0,0);

    textprintf_ex(screen,font,10,20,blanc,-1,"Creation Graphe");
    line(screen,900,0,900,622,blanc);

    rectfill(screen,910,10,1070,50,blanc);
    textprintf_ex(screen,font,920,25,noir,-1,"Ajouter sommet");
}

void affichage(Sommet *a){

    BITMAP *image;

    if(a->getnumani()==1){
    image=load_bitmap("jaguar.bmp",NULL);
    }

    if(a->getnumani()==2){
    image=load_bitmap("mygale.bmp",NULL);
    }

    if(a->getnumani()==3){
    image=load_bitmap("mante.bmp",NULL);
    }

    if(a->getnumani()==4){
    image=load_bitmap("papillon.bmp",NULL);
    }

    if(a->getnumani()==5){
    image=load_bitmap("pelican.bmp",NULL);
    }

    if(a->getnumani()==6){
    image=load_bitmap("phasme.bmp",NULL);
    }

    if(a->getnumani()==7){
    image=load_bitmap("tamanoir.bmp",NULL);
    }

    if(a->getnumani()==8){
    image=load_bitmap("tatou.bmp",NULL);
    }

    if(a->getnumani()==9){
    image=load_bitmap("vegetal.bmp",NULL);
    }


    if (!image)
    {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    blit(image,screen,0 , 0, a->getposx(), a->getposy(), image->w, image->h);
}

void lecturefichier(Graphe *graphe){

/// LECTURE GRAPHE
    ifstream fichier1("graphe.txt", ios::in);  // on ouvre en lecture
    int nombredesommet;
    if(fichier1)
    {
        fichier1 >> nombredesommet;
        graphe->settersommets(nombredesommet);
        fichier1.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }



/// LECTURE SOMMETS
    int compteur=0;

    while(compteur!=graphe->getnbsommets())
    {
        ifstream fichier("test.txt", ios::in);  // on ouvre en lecture

        if(fichier)
        {
            Sommet *a = new Sommet;

            int n;
            int x;
            int y;
            int q;

            fichier >> n >> x >> y >> q;

            a->setnumani(n);
            a->setposx(x);
            a->setposy(y);
            a->setqtn(q);

            fichier.close();
            affichage(a);
            delete(a);

            compteur=compteur+1;
        }
        else
        {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }
    }
}

void sauvegarde_graphe(Graphe *graphe){
    ofstream Flux("graphe.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

    if(Flux)
    {
        Flux << graphe->getnbsommets() << endl;
        Flux.close();
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

}







