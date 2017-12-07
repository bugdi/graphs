# Graphs

Dieses Program ist meine große Hausaufgabe für das Lehrfach 'Grundlagen der Programmierung'.

Ich habe den Dijkstra-Algorithmus implementiert, und auch eine Program mit graphisches Benutzeroberfläche geschrieben, damit man eine Graph zeichnen kann. Die programm wurde in C geschrieben.

Dieses Projekt ist auf [Github](https://github.com/bugdi/graphs) aufgeladet.

# Dokumentazion für die Programmierer

Filestruktur

Name        | Funkzion
-----       | -----
algorithms  | Implementazion von Dijkstra 
draw        | SDL, Zeichnung
file        | Filemanagement
graph       | Implementazion von den Graphen 
loop        | 'main loop'
main.c      | Eintrittspunkt, Initalizierung
vector_math | Hilfsfunkzionen für Vector-Arthimetik
window      | WIN32 API

## algoritmus

```c
struct vertex_set {
	int vertex;
	struct vertex_set* next;
} typedef vertex_set_t;
```
Diese Struktur bildet in eine verkettete Liste, und wird als eine Menge von Knoten benutzt

```c
struct dist_item {
	int distance;
	int last_vertex;
	int is_endless;
} typedef dist_item_t;
```
Beim Algorithmus von Dijkstra wird eine Tabelle hergestellt, die die Distanz von dem Startpunkt enthält. Diese Struktur bildet eine Zelle von dieser Tabelle.

```c
int in_set(vertex_set_t* set, int vertex);
```
Testet ob die Knote `vertex` in der Menge `set` ist.


```c
void run_dijkstra(Graph* graph, int start, int end);
```
Läuft den Algorithmus auf den Graph `graph` und zeigt die kürzeste Weg von `start` bis `end`

## draw

```c
void fill_circle(int x, int y, int radius, int r, int g, int b, int a);
```
Füllt eine Kreis im Punkt (`x`, `y`) mit radius `radius` mit dem Färbe definiert von `r`, `g`, `b`, `a` 

```c
int load_global_font(const char* path);
```
Festgelegt die benutzte Schrifttyp

```c
int create_edge_text_info();
int update_edge_text_info(int edge);
int update_all_edge_text_info();
```
Erschafft/updatet Informazionen die wichtig sind um eine/alle Kante zu zeichnen (zB Textur)

## file.h

```c
int save_graph(Graph* graph, const char* path);
```
Speichert die Graph `graph` im File `path`

```c
Graph* load_graph(const char* path);
```

Ladet eine Graph von `path`

## graph.h

```c
struct {
	int x;
	int y;
} typedef Vertex;
```
Definiert eine Knote

```c
struct {
	int v1;
	int v2;
	int weight;
} typedef Edge;
```
Definiert eine Kante

```c
struct {
	SDL_Texture* texture;
	SDL_Rect rect;
	unsigned length;
	int highlight; //dijkstra
} typedef EdgeTextInfo;
```
Speichert interne Informazionen über eine Kante

```c
struct {
	int numberOfVertices;
	int numberOfEdges;
	Vertex* vertices;
	Edge* edges;
	EdgeTextInfo* edgeInfo;
	int flags;
} typedef Graph;
```
Definiert eine Graph

```c
Graph* create_graph(int numOfVertices, int numOfEdges, int flags, ... /* edges*/ );
```
Herstellt eine Graph mit `numOfVertices` Knoten, `numOfEdges` Kanten.
`flag` ist nicht benutzt.
Die Kanten werden zwischen die Knoten, die als Argument gegeben werden.

```c
void destroy_graph(Graph* graph);
```
Löscht die Graph `graph`.

```c
void append_vertex(Graph* graph, int x, int y);
```
Addiert eine Knote zum Graph

```c
void append_edge(Graph* graph, int v1, int v2);
```
Addiert eine Kante zum Graph

```c
void delete_vertex(Graph* graph, int i);
```
Löscht eine Knote vom Graph

```c
void delete_edge(Graph* graph, int edge);
```
Löscht eine Kante vom Graph

```c
void delete_edges_of_vertex(Graph* graph, int vertex)
```
Löscht alle Kanten der Knote `vertex` in Graph `graph`

## loop

```c
extern SDL_Window* gWindow;
```
Eine globale Variable für das SDL Window

```c
extern Graph* gGraph;
```
Globale Variable für die Graph

```c
extern SDL_Renderer* gRenderer;
```
Renderer von SDL

```c
void draw();
```
Dieses Funkzion zeigt die Graph auf den Bildschirm

```c
void gameInit();
```
Initaliziert die Program

```c
void gameClose();
```
Schließt die Program

```c
void update(SDL_Event e);
```
Handelt die Benutzerinput

```c
int is_between(double num, double min, double max);
```
Testet ob `num` ist zwischen `min` und `max`.

```c
double distance(int x0, int y0, int x1, int y1);
```
Gibt zurüch die Distanz zwischen de Punkt (`x0`, `y0`) und (`x1`, `y1`)

```c
Vector2d intersect_vertex_and_vector(Vertex a, Vertex b, Vector2i c, Vector2i d);
```
Kalkuliert den Schnitt einer Knote und einer Vektor

```c
void update_weight(int input)
```
Handelt die Eingabe der Kosten einer Kante

```c
void remove_hightlight()
```
Löscht die Markierung der kürzesten Weg

## main

```c
int init()
```
Initaliziert SDL

```c
void close()
```
Uninitaliziert SDL

```c
int main(int argc, char** argv)
```
Eintrittspunkt des Programs


## vector_math

```c
struct {
	int x;
	int y;
} typedef Vector2i;
```
Vektor mit integer-Koordinaten

```c
struct {
	double x;
	double y;
} typedef Vector2d;
```
Vektor mit double-Koordinaten

```c
Vector2d intersect_lines(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
```
Kalkuliert den Schnitt zweier Linien