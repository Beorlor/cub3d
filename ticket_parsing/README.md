# EXEMPLE

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

		1111111111111111111111111
		1000000000110000000000001
        1011000001110000000000001
		1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

# Faire un parsing robuste

## Cahier des charges :

Ne dois jamais segfault meme si input random
Enregistrer Toute les informations du .cub
Exit toujours sans leaks
Bien gerer toutes les erreurs

## Tips

Malloc une map carrer meme si la map ne lai pas (trouver x et y max)
Gerer les espaces pour la map (exterieur)
Verifier validiter de la map (aucun espace nest coller a un 0 dans ses 8 cases autour) + a un starting point qui est N S W E

Pour bien exit sans leaks quand on declare une variable mais quelle est pas encore malloc, la mettre explicitement a NULL comme ca on pourra la free dans crash si jamais pas encore definie
(Solution pas magique car on ne pourra dereferencer mais ca evitera deja quelque soucis)

## Erreur de map

Validiter du fichier .cub
1er ligne start avec NO puis un ' ' puis save toute la ligne jusquau '\n'
SO pareil
WE pareil
EA pareil
ligne 5 only authorize (\t \n ' ' ect...)
F int,int,int (compris entre 0 et 255)
C
ligne 8 only authorize (\t \n ' ' ect...)
MAP (a partir de la rien dautoriser hors ' ' 1 0)
fin de la map quand une ligne commence par \n, apres cela aucun char autoriser hors \n

Message a afficher en cas de probleme d'input

Il manque North/South/East/West/Floor/Ceiling/Map pour accepter la map

Manque un espace entre North/South/East/West/Floor/Ceiling et leur valeur

Path invalide pour North/South/East/West

Valeur RGB invalide pour Floor/Ceiling

Manque une ligne vide entre les textures et les couleurs (ligne 5)

Manque une ligne vide entre les couleurs et la map (ligne 8)

Map invalide, Char interdit dans la map ( /1/0)

Map invalide, la map doit etre entourer de mur (tips sur lalgo de graph)

Aucun char autoriser apres la fin de la map (apres une premiere ligne vide post map)

(il en manque peut etre, le but est de jamais segfault, tout check, bien tout save)

## Struct

```c
typedef enum e_texture_index {
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
} e_texture_index;

typedef struct s_texture {
    char *paths[4]; // utilise l'enum e_texture_index pour indexer
} t_texture;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_map {
    char **map;
    int width;
    int height;
} t_map;

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
} t_player;

typedef struct s_game {
    t_texture textures;
    t_color floor;
    t_color ceiling;
    t_map map;
    t_player player;
} t_game;
```
