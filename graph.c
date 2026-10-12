#include <stdlib.h>
#include "graph.h"


Graph *createGraph(int numCities, int numLinks)
{
    Graph *graph;

    /* Reservar memoria para o Graph */
    graph = malloc(sizeof(Graph));

    if (graph == NULL) {
        return NULL;
    }


    /* Guardar informacao geral da rede */
    graph->numCities = numCities;
    graph->numLinks = numLinks;

    /* Os limites ainda nao foram lidos */
    graph->xMax = 0;
    graph->yMax = 0;


    /* Reservar memoria para as cidades */
    graph->cities = malloc(numCities * sizeof(City));

    if (graph->cities == NULL) {
        free(graph);
        return NULL;
    }


    return graph;
}


void destroyGraph(Graph *graph)
{
    if (graph == NULL) {
        return;
    }

    free(graph->cities);
    free(graph);
}


void setMapLimits(Graph *graph, int xMax, int yMax)
{
    graph->xMax = xMax;
    graph->yMax = yMax;
}


void setCityPosition(Graph *graph, int id, int x, int y)
{
    graph->cities[id - 1].id = id;
    graph->cities[id - 1].x = x;
    graph->cities[id - 1].y = y;
}
