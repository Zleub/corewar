Usage:

./corewar [-t X -d X -v X -ncurse] -n champion -n champion ...

Explanations :</br>
    -t X : Enable tic_rate control such as usleep(800 * X). Normal: 100.</br>
	-d X : Stop VM after X cycles and dump memory.</br>
	-v 0 : No verbosity except errors</br>
	-v 1 : Verbosity on live only</br>
    -v 2 : Verbosity on instruction execution</br>
    -v 3 : Verbosity on update</br>
	-v 4 : Full verbosity on update</br>
Todo:

- crash on not .cor files
- total asm handle

- Un PC ("Program Counter"). C’est un registre spécial, qui contient juste l’adresse, dans la mémoire de la machine virtuelle, de la prochaine instruction à décoder
et exécuter.
- Un flag nommé carry, qui vaut 1 si la dernière opération a réussi.

- Le numéro du joueur est généré par la machine ou spécifié au lancement (-n 10 champions/bee_gees.cor)
- Tous les CYCLE_TO_DIE cycles, la machine doit s’assurer que chaque processus
a exécuté au moins un live depuis la dernière vérification.
- Si au cours d’une de ces vérifications on se rend compte qu’il y a eu au moins NBR_LIVE exécutions de live depuis la dernière vérification en date, on décrémente CYCLE_TO_DIE de CYCLE_DELTA unités.
- Quand il n’y a plus de processus en vie, la partie est terminée.
- Le gagnant est le dernier joueur qui a été rapporté comme étant en vie. La machine va ensuite afficher : "le joueur x(nom_champion) a gagne", où x est le numéro du joueur et nom_champion le nom de son champion.
- Si on n’a pas décrémenté CYCLE_TO_DIE depuis MAX_CHECKS vérifications,
on le décrémente.
