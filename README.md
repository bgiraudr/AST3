# AST3_C

## Présentation :

A Switch To The Top est un jeu prévu pour fx-cg50 (90+E). Ou vous pouvez changer la gravité afin de traverser un niveau.
Ceci est une adaptation utilisant Gint de Lephenixnoir pour avoir un jeu plus plaisant et fluide.

## Comment installer :

- Glisser le fichier AST3.g3a dans votre calculatrice.
- Lancer le jeu directement depuis le menu principal.

## Éditer le jeu :

Clone ce dépot :
`$ git clone https://gitea.planet-casio.com/Tituya/AST3_C && cd AST3_C`

Pour ouvrir l'éditeur de niveau (Python et Pygame obligatoire).
`$ ./editor.sh`

Pour compiler le jeu (fxsdk + gint obligatoire).
`$ fxsdk build-cg`

Appliquer le formatage au code après vos modifications.
`$ clang-format -style=file -i src/* include*`
