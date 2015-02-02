Usage:

./corewar [-ncurse] -n champion -n champion ...

Todo:

- crash on not .cor files
- total asm handle

Chaque processus aura à sa disposition les éléments suivants, qui lui sont propres :
- REG_NUMBER registres qui font chacun une taille de REG_SIZE octets.
- Un PC ("Program Counter"). C’est un registre spécial, qui contient juste l’adresse,
dans la mémoire de la machine virtuelle, de la prochaine instruction à décoder
et exécuter.
- Un flag nommé carry, qui vaut 1 si la dernière opération a réussi.

- Le numéro du joueur est généré par la machine ou spécifié au lancement
- Tous les CYCLE_TO_DIE cycles, la machine doit s’assurer que chaque processus
a exécuté au moins un live depuis la dernière vérification.