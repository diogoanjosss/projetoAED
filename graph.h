
#ifndef GRAPH_H
#define GRAPH_H


typedef struct {
    int id;
    int x;
    int y;
} City;


typedef struct {
    int numCities;
    int numLinks;
     int xMax;
    int yMax;
    City *cities;
} Graph;


/* Funcoes do Graph */
Graph *createGraph(int numCities, int numLinks);

void destroyGraph(Graph *graph);

void setCityPosition(Graph *graph, int id, int x, int y);

void setMapLimits(Graph *graph, int xMax, int yMax);

#endif
