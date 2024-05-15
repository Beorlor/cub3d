# cub3D

## Introduction

Ce projet s'inspire du jeu Wolfenstein 3D et vous permettra de créer une représentation graphique 3D réaliste de l'intérieur d'un labyrinthe en utilisant les principes du ray-casting.

## Structure du Répertoire

```css
cub3D/
├── src/
│   ├── main.c
│   ├── init.c
│   ├── parser.c
│   ├── renderer.c
│   ├── events.c
│   ├── utils.c
│   └── cleanup.c
├── include/
│   ├── cub3d.h
│   ├── defines.h
│   └── structs.h
├── assets/
│   ├── textures/
│   └── maps/
├── libft/
│   ├── libft.h
│   ├── *.c
│   └── Makefile
├── Makefile
└── README.md
```

## Fichiers Source et leur Rôle

1. **main.c**
    - Point d'entrée du programme.
    - Initialisation générale et boucle principale.

2. **init.c**
    - Initialisation des structures de données, configuration initiale, et chargement des ressources.

3. **parser.c**
    - Analyse du fichier `.cub`, vérification de la validité de la carte et chargement des textures et couleurs.

4. **renderer.c**
    - Gestion du rendu 3D avec ray-casting.
    - Dessin des murs, du plafond et du sol.

5. **events.c**
    - Gestion des entrées utilisateur (clavier, souris).
    - Mouvement et rotation du point de vue.

6. **utils.c**
    - Fonctions utilitaires pour le projet (gestion des erreurs, fonctions mathématiques supplémentaires, etc.).

7. **cleanup.c**
    - Libération des ressources allouées et fermeture propre du programme.

## Fichiers d'En-tête

1. **cub3d.h**
    - Inclusion des bibliothèques nécessaires et des autres fichiers d'en-tête.
    - Prototypes des fonctions principales.

2. **defines.h**
    - Définitions des constantes, des macros et des identifiants pour les textures et les couleurs.

3. **structs.h**
    - Déclarations des structures de données utilisées dans le programme (e.g., `t_player`, `t_map`, `t_image`, etc.).

## Structure des Données

1. **t_player**
    - Position (x, y)
    - Direction (dx, dy)
    - Plan de la caméra (camera plane)

2. **t_map**
    - Largeur et hauteur de la carte
    - Tableau 2D représentant la carte (matrice de caractères)

3. **t_image**
    - Pointeur vers l'image (données de l'image)
    - Dimensions de l'image
    - Adresse des pixels

4. **t_game**
    - Pointeur vers la fenêtre (MLX)
    - Pointeur vers l'image à afficher
    - Instance de `t_player`
    - Instance de `t_map`
    - Couleurs du plafond et du sol
    - Textures des murs

## Makefile

Le `Makefile` doit contenir les règles suivantes :

- `all` : Compile le programme principal.
- `clean` : Supprime les fichiers objets.
- `fclean` : Supprime les fichiers objets et les exécutables.
- `re` : Effectue un nettoyage complet et recompile le programme.
- `bonus` : Compile les fichiers de la partie bonus.

## Détails de l'Implémentation

1. **Initialisation (init.c)**
    - Initialiser la bibliothèque MiniLibX.
    - Créer une nouvelle fenêtre.
    - Charger les textures et configurer les couleurs du plafond et du sol.
    - Initialiser la position et la direction du joueur.

2. **Parsing du fichier .cub (parser.c)**
    - Lire et valider le fichier de configuration.
    - Charger les textures et vérifier les chemins d'accès.
    - Configurer la carte et vérifier qu'elle est entourée de murs.

3. **Rendu (renderer.c)**
    - Implémenter l'algorithme de ray-casting pour rendre la vue 3D.
    - Dessiner les murs avec les textures correspondantes.
    - Dessiner le plafond et le sol.

4. **Gestion des événements (events.c)**
    - Implémenter les contrôles de déplacement (W, A, S, D) et de rotation (flèches gauche et droite).
    - Gérer la fermeture de la fenêtre avec ESC ou le clic sur la croix rouge.

5. **Nettoyage (cleanup.c)**
    - Libérer toutes les ressources allouées (textures, images, structures).
    - Fermer proprement la fenêtre et quitter le programme.

## Conclusion

Cette architecture modulaire permet de bien séparer les différentes responsabilités du programme, facilitant ainsi le développement, le débogage et l'ajout de nouvelles fonctionnalités. En suivant cette structure, vous devriez être en mesure de créer un ray-caster performant et facilement extensible.
