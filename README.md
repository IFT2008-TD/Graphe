# IFT-2008: Travaux dirigés

## Travail dirigé 4: les graphes

### Instructions

- Créez le projet dans votre environnement de développement.
  - Le plus simple, sur la VM du cours et CLion, dans la fenêtre *New Projet* choisissez *Get from VCS* puis indiquez l'adresse du dépôt git: https://IFT2008-TD/Graphe.git

### Description de la classe

Cette classe doit représenter un graphe dirigé ou orienté. Elle contient donc un ensemble de *sommets* reliés entre
eux par des *arêtes* ayant une direction bien définie. Ainsi, si les sommets sont représentés par des nombres
entiers, l'arête reliant les sommets 1 à 2 sera notée (1,2). Cette arête est distincte de l'arête (2,1).  

Chaque sommet est repéré par une *clé* qui doit être unique, et qui sert à identifier le sommet.  Cette clé 
peut être d'un type arbitraire: nombre entier, objet string, ou autre.

Dans le cas d'une arête (a, b), a est le sommet de départ et b est le sommet d'arrivée.
De plus, dans le cas d'un graphe *pondéré*, chaque arête peut-être dotée d'un poids qui est un nombre réel. Si le 
graphe n'est pas pondéré, on considérera que tous les poids valent 1.0.


### Interface de la classe

La classe Graphe doit permettre de réaliser les opérations suivantes :

- Construction : on doit pouvoir construire un graphe contenant un nombre déterminé de sommets, sans arête.  Par-défaut ce constructeur crée un graphe vide, ne contenant aucun sommet ni arête.
- ajouterUnSommet(cle): cette méthode permet d'ajouter un sommet au graphe. Si la clé existe, la méthode doit échouer d'une manière raisonnable.
- ajouterUneArete(cleDepart, cleArrivee): cette méthode permet d'ajouter une arête au graphe, du sommet de départ au sommet d'arrivée. Si l'arête existe, doit échouer.  Si une des clés n'existe pas, doit aussi échouer.
- sommetExiste(cle): cette méthode permet de vérifier la présence d'un sommet ayant une clé donnée.
- areteExiste(cleDepart, cleArrivee): cette méthode permet de vérifier la présence d'une arête de départ vers arrivée.
- degreEntree(cleArrivee): cette méthode compte le nombre d'arêtes terminant sur cleArrivee.
- degreSortie(cleDepart): cette méthode compte le nombre d'arêtes partant de cleDepart.
- taille: cette méthode retourne le nombre de sommets dans le graphe.
- enumererSommetsAPartirDe(cleDepart): cette méthode retourne une liste de tous les sommets vers lesquels cleDepart possède une arête.
- enumererSommetsVers(cleArrivee): cette méthode retourne une liste de tous les sommets ayant une arête vers cleArrivee.

### Invariant de la classe

La classe Graphe doit respecter en tout temps les conditions de validité suivantes:
- Chaque sommet est unique
- Chaque arête est unique
- Toutes les clés présentes dans toutes les arêtes doivent être elles-mêmes un des sommets du Graphe.  En d'autres terme une arête ne peut avoir un départ ou une arrivée inexistante.

### Modèle d'implantation

Bande de petits chanceux!!!  Il n'y a aucun modèle suggéré!  C'est à vous de prendre les décisions de design 
afin de respecter le cahier des charges!  Par-contre, pour vous épargner du travail, je vous fournis une liste
de tests unitaires.  Votre mission est de faire fonctionner les tests...

