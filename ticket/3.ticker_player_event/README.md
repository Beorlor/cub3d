### Ticket Jira: Gestion des Entrées Clavier et Souris (Avec Rotation de Vue)

**Résumé :**
L'objectif de ce ticket est de mettre en place la gestion des entrées clavier et souris pour le projet cub3D, y compris la rotation de la vue avec le déplacement de la souris. Il est crucial de s'assurer que les touches du clavier fonctionnent de manière continue tant qu'elles sont enfoncées, et que la vue peut être contrôlée par les mouvements de la souris.

---

**Titre :** Gestion des Entrées Clavier et Souris (Avec Rotation de Vue)

**Description :**

La gestion des entrées clavier et souris est essentielle pour permettre au joueur de naviguer et interagir avec le jeu de manière fluide et réactive. Dans cub3D, il est nécessaire de vérifier continuellement l'état des touches afin que les actions se répètent tant qu'elles sont maintenues enfoncées. De plus, la vue doit pouvoir être contrôlée par les mouvements de la souris pour une expérience de jeu plus immersive.

**Tâches :**

1. **Définir les touches et les actions associées**
    - Déterminer les touches du clavier nécessaires pour les déplacements et les actions du joueur.
    - Définir les actions de la souris.

```
    #define KEY_W 13
    #define KEY_A 0
    #define KEY_S 1
    #define KEY_D 2
    #define KEY_LEFT 123
    #define KEY_RIGHT 124
    #define MOUSE_LEFT_CLICK 1
```

2. **Initialiser l'état des touches et de la souris**
    - Créer une structure ou un tableau pour maintenir l'état des touches (pressée ou relâchée) et la position de la souris.

```
    typedef struct s_input {
        int keys[256];
        int mouse_left_pressed;
        int mouse_x;
        int mouse_y;
        int last_mouse_x;
        int last_mouse_y;
    } t_input;

    void init_input(t_input *input) {
        for (int i = 0; i < 256; i++)
            input->keys[i] = 0;
        input->mouse_left_pressed = 0;
        input->mouse_x = 0;
        input->mouse_y = 0;
        input->last_mouse_x = 0;
        input->last_mouse_y = 0;
    }
```

3. **Mettre en place des fonctions de gestion des événements**
    - Utiliser les fonctions de MiniLibX pour détecter les pressions et les relâchements de touches ainsi que les mouvements de la souris.
    - Mettre à jour l'état des touches et de la souris en conséquence.

```
    int key_press(int keycode, t_input *input) {
        if (keycode >= 0 && keycode < 256)
            input->keys[keycode] = 1;
        return (0);
    }

    int key_release(int keycode, t_input *input) {
        if (keycode >= 0 && keycode < 256)
            input->keys[keycode] = 0;
        return (0);
    }

    int mouse_press(int button, int x, int y, t_input *input) {
        if (button == MOUSE_LEFT_CLICK)
            input->mouse_left_pressed = 1;
        return (0);
    }

    int mouse_release(int button, int x, int y, t_input *input) {
        if (button == MOUSE_LEFT_CLICK)
            input->mouse_left_pressed = 0;
        return (0);
    }

    int mouse_move(int x, int y, t_input *input) {
        input->mouse_x = x;
        input->mouse_y = y;
        return (0);
    }
```

4. **Configurer la boucle principale pour gérer les entrées en continu**
    - Dans la boucle principale du jeu, vérifier continuellement l'état des touches et appliquer les actions correspondantes tant qu'elles sont enfoncées.
    - Utiliser les mouvements de la souris pour la rotation de la vue.

```
    void handle_input(t_game *game, t_input *input) {
        if (input->keys[KEY_W])
            move_forward(game);
        if (input->keys[KEY_S])
            move_backward(game);
        if (input->keys[KEY_A])
            strafe_left(game);
        if (input->keys[KEY_D])
            strafe_right(game);
        if (input->keys[KEY_LEFT])
            rotate_left(game);
        if (input->keys[KEY_RIGHT])
            rotate_right(game);

        // Rotation de la vue avec la souris
        int delta_x = input->mouse_x - input->last_mouse_x;
        if (delta_x != 0) {
            double rotation_speed = 0.05;
            double old_dir_x = game->player.dir_x;
            game->player.dir_x = game->player.dir_x * cos(-delta_x * rotation_speed) - game->player.dir_y * sin(-delta_x * rotation_speed);
            game->player.dir_y = old_dir_x * sin(-delta_x * rotation_speed) + game->player.dir_y * cos(-delta_x * rotation_speed);
            double old_plane_x = game->player.plane_x;
            game->player.plane_x = game->player.plane_x * cos(-delta_x * rotation_speed) - game->player.plane_y * sin(-delta_x * rotation_speed);
            game->player.plane_y = old_plane_x * sin(-delta_x * rotation_speed) + game->player.plane_y * cos(-delta_x * rotation_speed);
        }
        input->last_mouse_x = input->mouse_x;
        input->last_mouse_y = input->mouse_y;
    }

    void game_loop(t_game *game, t_input *input) {
        while (game->running) {
            handle_input(game, input);
            render_frame(game);
            mlx_loop_hook(game->mlx, &game_loop, game);
        }
    }
```

5. **Liaison des gestionnaires d'événements**
    - Associer les fonctions de gestion des événements aux événements correspondants de MiniLibX.

```
    void setup_hooks(t_game *game, t_input *input) {
        mlx_hook(game->win, 2, 1L<<0, key_press, input);
        mlx_hook(game->win, 3, 1L<<1, key_release, input);
        mlx_hook(game->win, 4, 1L<<2, mouse_press, input);
        mlx_hook(game->win, 5, 1L<<3, mouse_release, input);
        mlx_hook(game->win, 6, 1L<<6, mouse_move, input);
    }
```

6. **Tester et Déboguer**
    - Tester les différentes entrées pour s'assurer qu'elles sont détectées et traitées correctement.
    - Déboguer les problèmes potentiels et s'assurer que le jeu répond de manière fluide aux entrées utilisateur.

**Tips :**
- Utiliser un tableau de taille fixe pour les touches (256) car cela couvre toutes les touches possibles du clavier.
- Assurer une vérification robuste des indices de touche pour éviter les débordements de tableau.
- Utiliser des fonctions de déplacement et de rotation pour modulariser le code et le rendre plus lisible et maintenable.
- La rotation de la vue avec la souris peut être ajustée en modifiant la valeur de rotation_speed.

### Définition des structures nécessaires :

```
typedef struct s_input {
    int keys[256];
    int mouse_left_pressed;
    int mouse_x;
    int mouse_y;
    int last_mouse_x;
    int last_mouse_y;
} t_input;

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
    int         running;
    t_input     input;
} t_game;
```
