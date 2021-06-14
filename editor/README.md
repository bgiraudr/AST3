# AST3_C

## Éditeur :

Pour ouvrir (python3 + pygame): 
`$ ./editor.sh`

## Commande :

- Q niveau précédent (Numéro de salle affiché en haut à gauche)
- D niveau suivant
- Z augmenter temps avant apparition blocs + (temps affiché en haut à gauche)
- S baisser temps avant apparition blocs +
- R augmenter temps avant disparition blocs - (temps affiché en haut à gauche)
- F baisser temps avant disparition blocs -
- T augmenter le nombre de switch possibles dans le niveau (nécessite le bloc d'activation)
- G baisser le nombre de switch possibles dans le niveau
- SHIFT changer le sens de la gravité par défaut (gravité affichée en haut à gauche)
- TAB Afficher le design des blocs non activé
- A supprime le bloc bloqué dans la main. 
- N pour reset la pièce en entier

Click gauche : tourner parmis les blocs
Click droit : supprimer le bloc

Click molette centrale sur un bloc : bloquer ce bloc dans la main, permet de placer plusieurs fois le même bloc rapidement. (bloc bloqué affiché en haut)
Click gauche après molette : placer le bloc

## Sauvegarde :

L'éditeur sauvegarde automatiquement les niveaux à chaques actions. 

`$ ./build.sh` pour construire l'application depuis ces niveaux.

Tituya
