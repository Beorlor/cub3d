### Ticket Jira: Initialisation de cub3D

**Résumé :**
L'objectif de ce ticket est de définir les tâches nécessaires pour initialiser le projet cub3D. Cela inclut la mise en place des structures de données, la configuration initiale, et le chargement des ressources. Le ticket Init est petit et sert de transition avec le prochain ticket, qui portera sur le parsing détaillé.

---

**Titre :** Initialisation du projet cub3D

**Description :**

L'initialisation du projet cub3D est une étape cruciale qui comprend la configuration des données de base, l'initialisation des ressources graphiques et la préparation du jeu pour le rendu et les interactions utilisateur. Le ticket Init sera incomplet, à l'inverse du ticket parsing, il faudra tout le long revenir dans Init, que ce soit pour la minimap, le raycasting ou autre, car je n'ai pas encore défini cette partie. Si ce message est toujours là, c'est que je n'ai toujours pas défini plus loin les autres parties.

Les exemples de code et de structure sont de l'aide pour demarrer, en aucun cas une certitude

Le ticket Init est petit, il sert de transition avec le prochain ticket, donc j'ai réfléchi aux différentes erreurs à traiter, il peut en manquer. Voici un exemple de toutes les erreurs qui doivent être traitées dans le ticket parsing ou init :

"Not a .cub file"  
"Not an .xpm file"  
"Invalid floor/ceiling RGB color(s)"  
"Invalid floor RGB color"  
"Invalid ceiling RGB color"  
"Map description is either wrong or incomplete"  
"Invalid character in map"  
"Map has more than one player"  
"Invalid RGB value (min: 0, max: 255)"  
"Missing texture(s)"  
"Invalid texture(s)"  
"Missing color(s)"  
"Missing map"  
"Map is not at least 3 lines high"  
"Map is not surrounded by walls"  
"Map is not the last element in file"  
"Invalid player position"  
"Map has no player position (expected N, S, E ou W)"  
"Could not allocate memory"  
"Could not start mlx"  
"Could not create mlx window"  
"Could not create mlx image"  

Tu peux les écrire différemment mais pense à les #define comme ça ils sont réutilisables.

Il faut init la minilibx, charger les textures.

**Tâches :**

1. **Initialisation de la bibliothèque MiniLibX**
    - Importer et initialiser MiniLibX.
    - Créer une nouvelle fenêtre pour l'affichage.
    - Gérer les erreurs possibles lors de l'initialisation.

    ```c
    void init_mlx(t_game *game) {
        game->mlx = mlx_init();
        if (!game->mlx)
            exit_with_error(ERROR_MLX_START);
        game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "cub3D");
        if (!game->win)
            exit_with_error(ERROR_MLX_WINDOW);
    }
    ```

2. **Chargement des textures et des couleurs**
    - Charger les textures pour les murs (Nord, Sud, Est, Ouest) à partir des chemins spécifiés dans le fichier de configuration.
    - Configurer les couleurs du plafond et du sol à partir des valeurs RGB spécifiées.
    - Gérer les erreurs de chargement.

    ```c
    void load_textures(t_game *game) {
        for (int i = 0; i < 4; i++) {
            game->textures[i].img = mlx_xpm_file_to_image(game->mlx, game->texture_paths[i], &game->textures[i].width, &game->textures[i].height);
            if (!game->textures[i].img)
                exit_with_error(ERROR_INVALID_TEXTURES);
            game->textures[i].addr = (int *)mlx_get_data_addr(game->textures[i].img, &game->textures[i].pixel_bits, &game->textures[i].size_line, &game->textures[i].endian);
        }
    }
    ```

3. **Initialisation de la carte**
    - Allouer la mémoire pour la carte du labyrinthe.
    - Lire et stocker la carte du fichier `.cub`.

    ```c
    void init_map(t_game *game, const char *map_path) {
        // Lire et analyser le fichier .cub pour initialiser la carte
        // Stocker les dimensions de la carte
        game->map.width = ...; // Calculer la largeur de la carte
        game->map.height = ...; // Calculer la hauteur de la carte
        // Allouer la mémoire pour la carte
        game->map.map = malloc(sizeof(char *) * game->map.height);
        if (!game->map.map)
            exit_with_error(ERROR_MEMORY_ALLOCATION);
        for (int i = 0; i < game->map.height; i++) {
            game->map.map[i] = malloc(sizeof(char) * game->map.width);
            if (!game->map.map[i])
                exit_with_error(ERROR_MEMORY_ALLOCATION);
        }
        // Remplir la carte avec les données du fichier .cub
    }
    ```

4. **Initialisation du joueur**
    - Définir la position initiale et la direction du joueur en fonction des paramètres du fichier de configuration.
    - Configurer le plan de la caméra pour le rendu 3D.

    ```c
    void init_player(t_game *game) {
        // Définir la position initiale du joueur
        game->player.pos_x = ...;
        game->player.pos_y = ...;
        // Définir la direction initiale du joueur
        game->player.dir_x = ...;
        game->player.dir_y = ...;
        // Configurer le plan de la caméra
        game->player.plane_x = ...;
        game->player.plane_y = ...;
    }
    ```

5. **Initialisation des structures de données**
    - Définir et allouer la mémoire pour les structures de données nécessaires (textures, couleurs, carte, joueur, etc.).

    ```c
    void init_structures(t_game *game) {
        init_mlx(game);
        load_textures(game);
        init_map(game, map_path);
        init_player(game);
    }
    ```

6. **Gestion des erreurs**
    - Implémenter une gestion robuste des erreurs pour s'assurer que le programme quitte proprement en cas de problème (textures manquantes, valeurs RGB incorrectes, etc.).
    - Assurer qu'il n'y a pas de fuites de mémoire.

    ```c
    void exit_with_error(const char *error_message) {
        perror(error_message);
        exit(EXIT_FAILURE);
    }
    ```

### Définition des structures nécessaires :

```c
typedef enum e_texture_index {
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
} e_texture_index;

typedef struct s_texture {
    void    *img;
    int     *addr;
    int     pixel_bits;
    int     size_line;
    int     endian;
    int     width;
    int     height;
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
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_game {
    void        *mlx;
    void        *win;
    int         win_height;
    int         win_width;
    t_map       map;
    t_player    player;
    t_texture   textures[4];
    t_color     floor;
    t_color     ceiling;
    char        *texture_paths[4];
} t_game;
```