# corewar
projet de groupe em plusieur parties
## assembleur
l'executable asm prend en parametre un fichier .s de pseudo assembleur pour le compiler en .cor.

## corewar

machine virtuelle dans laquelle vont s'affronter 1 à 4 joueurs (.cor) avec un mode verbose (-v) qui va ecrire sur l'entree standard les differantes opperations, et un mode ncurse (-n) qui va afficher la memoire de la machine virtuelle en temps réel

le dernier joueur aà avoir executer l'action "live" (0x01) gagne la partie

voici un exemple d'utilisation :
```
./corewar -p 1 gnahahaaa.cor -p 2 ../champs/Octobre_Rouge_V4.2.cor -n
```
![alt-text](https://github.com/joplevy/corewar/blob/master/screenshot.png)

## le joueur

le fichier gnahahaaa.s est notre joueur. Il est basique mais plutot simple à comprendre.

le dossier champs contient d'autres joueurs écrit par d'autres personnes de 42 pour faire de notre corewar une veritable arène de combat sanglant
