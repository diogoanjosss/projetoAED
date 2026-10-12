#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"


int checkExtension(const char *filename, const char *extension)
{
    const char *dot = strrchr(filename, '.');

    if (dot == NULL) {
        return 0;
    }

    return strcmp(dot, extension) == 0;
}


int main(int argc, char *argv[])
{
    FILE *questsFile;
    FILE *mapFile;
    FILE *positionFile;

    int numCities;
    int numLinks;

    int xMax;
    int yMax;


    int id;
    int x;
    int y;

    int *seen;

    Graph *graph;


    /* Validar o numero de argumentos */
    if (argc != 4) {
        return 0;
    }


    /* Validar as extensoes */
    if (!checkExtension(argv[1], ".quests") ||
        !checkExtension(argv[2], ".map") ||
        !checkExtension(argv[3], ".position")) {

        return 0;
    }


    /* Abrir os ficheiros */
    questsFile = fopen(argv[1], "r");
    mapFile = fopen(argv[2], "r");
    positionFile = fopen(argv[3], "r");


    /* Validar se os ficheiros foram abertos corretamente */
    if (questsFile == NULL ||
        mapFile == NULL ||
        positionFile == NULL) {

        if (questsFile != NULL)
            fclose(questsFile);

        if (mapFile != NULL)
            fclose(mapFile);

        if (positionFile != NULL)
            fclose(positionFile);

        return 0;
    }


    /* Ler o numero de cidades e ligacoes */
    if (fscanf(mapFile, "%d %d", &numCities, &numLinks) != 2) {

        fclose(questsFile);
        fclose(mapFile);
        fclose(positionFile);

        return 0;
    }


    /* Criar a representacao da rede */
    graph = createGraph(numCities, numLinks);

    if (graph == NULL) {

        fclose(questsFile);
        fclose(mapFile);
        fclose(positionFile);

        return 0;
    }


    /* Ler os limites do mapa */
    if (fscanf(positionFile, "%d %d", &xMax, &yMax) != 2) {

        destroyGraph(graph);

        fclose(questsFile);
        fclose(mapFile);
        fclose(positionFile);

        return 0;
    }


    /* Guardar os limites do mapa */
    setMapLimits(graph, xMax, yMax);


    /*
     * Criar um array auxiliar para verificar
     * quais cidades ja apareceram
     */
    seen = malloc(numCities * sizeof(int));

    if (seen == NULL) {

        destroyGraph(graph);

        fclose(questsFile);
        fclose(mapFile);
        fclose(positionFile);

        return 0;
    }


    /* Inicializar o array seen a 0 */
    for (int i = 0; i < numCities; i++) {
        seen[i] = 0;
    }


    /* Ler as posicoes das cidades */
    for (int i = 0; i < numCities; i++) {

        if (fscanf(positionFile, "%d %d %d", &id, &x, &y) != 3) {

            free(seen);
            destroyGraph(graph);

            fclose(questsFile);
            fclose(mapFile);
            fclose(positionFile);

            return 0;
        }


        /* Validar o ID da cidade */
        if (id < 1 || id > numCities) {

            free(seen);
            destroyGraph(graph);

            fclose(questsFile);
            fclose(mapFile);
            fclose(positionFile);

            return 0;
        }


        /* Verificar se a cidade ja apareceu */
        if (seen[id - 1] == 1) {

            free(seen);
            destroyGraph(graph);

            fclose(questsFile);
            fclose(mapFile);
            fclose(positionFile);

            return 0;
        }


        /* Validar as coordenadas */
        if (x < 0 || x > xMax ||
            y < 0 || y > yMax) {

            free(seen);
            destroyGraph(graph);

            fclose(questsFile);
            fclose(mapFile);
            fclose(positionFile);

            return 0;
        }


        /* Marcar esta cidade como encontrada */
        seen[id - 1] = 1;


        /* Guardar a posicao */
        setCityPosition(graph, id, x, y);
    }


    /* O array auxiliar ja nao e necessario */
    free(seen);


    /*
     * PROXIMO PASSO:
     * Ler as ligacoes do ficheiro .map
     *
     * Vamos utilizar:
     * city1
     * city2
     */


    destroyGraph(graph);

    fclose(questsFile);
    fclose(mapFile);
    fclose(positionFile);

    return 0;
}
