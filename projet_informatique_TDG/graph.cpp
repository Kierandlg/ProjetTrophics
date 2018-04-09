#include "graph.h"
#include <fstream>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to, int idx)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    m_box_edge.add_child(m_idx);
    m_idx.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_idx.set_message(std::to_string(idx));

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}




/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.

void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    //add_interfaced_vertex(0,50.0,300,300,"fourmi.jpg");

    /// boucle permettant d'afficher les sommets des graphes en fonction des différentes valeurs stockées dans les fichiers txt
    for( int i=0; i< m_sommet.size(); i++)
    {
        add_interfaced_vertex(m_sommet[i].m_id_sommet, m_sommet[i].m_quantite, m_sommet[i].m_coord_x, m_sommet[i].m_coord_y, m_sommet[i].m_picture);
    }

    /// boucle permettant d'afficher les arcs des graphes en fonction des différentes valeurs stockées dans les fichiers txt
    for( int i=0; i< m_arc.size(); i++)
    {
        add_interfaced_edge(m_arc[i].m_identifiant, m_arc[i].m_from, m_arc[i].m_to );
    }

    /// on a automatisé l'affichage comparé au code initial où tout était rentré en dur dans la fonction add_interfaced
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2], idx);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

/// SS permettant de charger nos graphes, avec choix de l'utilisateur entre les 3 graphes
void Graph::initialiser_graphe(int saisie)
{
    std::string nom_fichier;

    if(saisie == 1)
    {
        nom_fichier="graphe1.txt";
    }
    if(saisie == 2)
    {
        nom_fichier="graphe2.txt";
    }
    if(saisie == 3)
    {
        nom_fichier="graphe3.txt";
    }

    std::ifstream file (nom_fichier);     /// ouverture du fichier en mode lecture

    Vertex s;
    Edge a;

    if(file)            /// si l'ouverture a réussi
    {
        file >> m_nb_sommet;            /// récupération des données à l'intérieur du fichier

        for(int i=0; i< m_nb_sommet; i++)
        {
            file >> s.m_id_sommet >> s.m_quantite >> s.m_coord_x >> s.m_coord_y >> s.m_picture;
            m_sommet.push_back(s);
        }
        file >> m_nb_arc;

        for(int i=0; i< m_nb_arc; i++)
        {
            file >> a.m_identifiant >> a.m_from >> a.m_to;
            m_arc.push_back(a);
        }
    }

}

/// SS permettant de sauvegarder les changements dans les graphes (coordonnées, ajout ou retrait de sommet et d'arcs)
void Graph::sauvegarder_graphe(int saisie)
{
    std::string nom_fichier;

    if(saisie == 1)
    {
        nom_fichier="graphe1.txt";
    }
    if(saisie == 2)
    {
        nom_fichier="graphe2.txt";
    }
    if(saisie == 3)
    {
        nom_fichier="graphe3.txt";
    }


    std::ofstream file (nom_fichier, std::ios::out | std::ios::trunc);    ///ouverture du fichier en écriture, et efface le contenu s'il n'est pas vide
    std::map<int,Vertex>::iterator it1;
    std::map<int,Edge>::iterator it2;

    if(file)                /// si l'ouverture a réussi
    {
        file << m_nb_sommet << std::endl;

        for(it1 = m_vertices.begin(); it1 != m_vertices.end(); it1++ )
        {
            (*it1).second.m_coord_x= (*it1).second.m_interface->m_top_box.get_frame().pos.x;
            (*it1).second.m_coord_y= (*it1).second.m_interface->m_top_box.get_frame().pos.y;
            (*it1).second.m_picture= (*it1).second.m_interface->m_img.m_pic_name;
            file << (*it1).first <<" "<< (*it1).second.m_quantite <<" "<< (*it1).second.m_coord_x <<" "<< (*it1).second.m_coord_y <<" "<< (*it1).second.m_picture << std::endl;
        }
        file << m_nb_arc << std::endl;

        for(it2 = m_edges.begin(); it2 != m_edges.end(); it2++)
        {
            file << (*it2).first <<" "<< (*it2).second.m_from <<" "<< (*it2).second.m_to << std::endl;
        }
    }

}

/// Implémentation du getter sur le nombre de sommet pour pouvoir faire appel à lui
 int Graph::get_nb_sommet()
{
     return m_nb_sommet;
}

/// Implémentation du getter sur le nombre d'arc pour pouvoir faire appel à lui
int Graph::get_nb_arc()
{
    return m_nb_arc;
}

/// SS permettant d'enlever un arc au graphe en cours d'utilisation
void Graph::enlever_arc(int eidx)
{
    /// référence vers le Edge à enlever

    Edge &remed=m_edges.at(eidx);

    std::cout << "arc supprimee " << eidx << " / sommets" << remed.m_from << "->" << remed.m_to  << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2

    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés

    if (m_interface && remed.m_interface)

    {
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe

        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to

    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !

    m_edges.erase( eidx );

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2

    //std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    //std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    //std::cout << m_edges.size() << std::endl;

    m_nb_arc=m_nb_arc-1;        /// on baisse d'1 la valeur de m_nb_arc car on a enlevé un arc au graphe
}

/// SS permettant d'enlever un sommet au graphe en cours d'utilisation
void Graph::enlever_sommet(int eidx)
{
    Vertex &remed=m_vertices.at(eidx);

    if(m_interface && remed.m_interface)
    {
        m_interface->m_main_box.remove_child(remed.m_interface->m_top_box);

        for(int i=0; i< m_vertices[eidx].m_in.size(); i++)
        {
            if(!m_vertices[eidx].m_in.empty())
            {
                enlever_arc(m_vertices[eidx].m_in[i]);
            }
        }

        for(int i=0; i<m_vertices[eidx].m_out.size(); i++)
        {
            if(!m_vertices[eidx].m_out.empty())
            {
                enlever_arc(m_vertices[eidx].m_out[i]);
            }
        }
    }

    m_vertices.erase(eidx);
    m_nb_sommet=m_nb_sommet-1;            /// on baisse d'1 la valeur de m_nb_sommet car on a enlevé un sommet au graphe
}


std::vector<int> Graph::UneComposanteConnexe(int s, std::vector<std::vector<int>> adjacence)
{
    std::vector<int> c1(m_nb_sommet, 0);
    std::vector<int> c2(m_nb_sommet, 0);
    std::vector<int> c(m_nb_sommet, 0);
    std::vector<int> marques(m_nb_sommet, 0);
    int ajoute=1;


    std::vector<std::vector<int>> trans;
    std::vector<int> mat(m_nb_sommet,0);

    c1[s]=1;
    c2[s]=1;

    for(int i=0; i<m_nb_sommet; i++)
    {
        trans.push_back(mat);
    }

    for(int i=0; i<m_nb_sommet; i++)
    {
        for(int j=0; j<m_nb_sommet; j++)
        {
            trans[j][i]=adjacence[i][j];
        }
    }

 /*   for(int i=0;i<m_nb_sommet;i++){
        for (int j=0;j<m_nb_sommet;j++){
            std::cout<<trans[i][j];
        }
        std::cout<<std::endl;

    }
      std::cout<<std::endl;*/



    while(ajoute)
    {

        ajoute=0;

        for(int i=0; i<m_nb_sommet; i++)
        {
            if(!marques[i] && c1[i])
            {
                marques[i]=1;
                for(int j=0; j<m_nb_sommet; j++)
                {
                    if(adjacence[i][j] && !marques[j])
                    {
                        c1[j]=1;
                        ajoute=1;
                    }
                }
            }
        }
    }
    for(int i=0; i<m_nb_sommet; i++)
    {
        marques[i]=0;

    }
    ajoute=1;

    while(ajoute)
    {

        ajoute=0;

        for(int i=0; i<m_nb_sommet; i++)
        {
            if(!marques[i] && c2[i])
            {
                marques[i]=1;
                for(int j=0; j<m_nb_sommet; j++)
                {
                    if(trans[i][j] && !marques[j])
                    {
                        c2[j]=1;
                        ajoute=1;
                    }
                }
            }
        }
    }





for(int i=0; i<m_nb_sommet; i++)
    {
        c[i]=c1[i]&c2[i];


    }
    c[s]=0;
    return c;



}

void Graph::ToutesComposantesConnexes(){

      std::vector<std::vector<int>> adjacence;
    std::vector<int> mat(m_nb_sommet,0);

    std::vector<std::vector<int>> tabc;
    std::vector<int> marques(m_nb_sommet,0);


    for(int i=0; i<m_nb_sommet; i++)
    {
        adjacence.push_back(mat);
        tabc.push_back(mat);
    }



    for(int i=0; i<m_nb_sommet; i++)
    {
        for(int j=0; j<m_nb_sommet; j++)
        {
            for(int k=0; k<m_edges.size(); k++)
            {
                if(m_edges[k].m_from==i && m_edges[k].m_to==j)
                {
                    adjacence[i][j]=1;
                }
            }
        }
    }

   /* for(int i=0;i<m_nb_sommet;i++){
        for(int j=0;j<m_nb_sommet;j++){
            std::cout<<adjacence[i][j];

        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;*/

    for(int i=0; i<m_nb_sommet;i++){
        if(!marques[i]){
            tabc[i]=UneComposanteConnexe(i,adjacence);
            marques[i]=1;
        }

    }
 for(int i=0;i<m_nb_sommet;i++){
        for(int j=0;j<m_nb_sommet;j++){
                std::cout<<tabc[i][j];

        }
        std::cout<<std::endl;

}
}

/// SS permettant d'ajouter un arc au graphe en cours d'utilisation
void Graph::ajouter_arc(int ind_arc,int  somm_dep,int somm_ar,int weight)
{
            m_nb_arc= m_nb_arc +1;              /// on augmente d'1 la valeur de m_nb_arc car on a ajouté un arc au graphe
            add_interfaced_edge(ind_arc, somm_dep,somm_ar,weight);          ///fonction permettant d'afficher cet arc sur l'interface graphique
}

/// SS permettant d'ajouter un sommet au graphe en cours d'utilisation
void Graph::ajouter_sommet(int ind_somm, int valeur, int x, int y ,std::string nom_image)
{
        m_nb_sommet = m_nb_sommet +1;           /// on augmente d'1 la valeur de m_nb_sommet car on a ajouté un sommet au graphe
        add_interfaced_vertex(ind_somm,valeur,x,y,nom_image,0);         ///fonction permettant d'afficher ce sommet sur l'interface graphique

}

