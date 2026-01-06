# 🍽️ Simulation d’un Restaurant — Producteurs / Consommateurs

**C • Threads • Mutex • Sémaphores**

Ce projet simule le fonctionnement d’un restaurant dans un environnement concurrent.
Il met en œuvre le modèle **producteur–consommateur** en utilisant :

* des **threads POSIX** (serveurs et cuisiniers),
* des **mutex** pour protéger les sections critiques,
* des **sémaphores** pour la synchronisation,
* un **buffer circulaire** pour la file d’attente des commandes,
* un **système de logs HTML** consultable dans un navigateur.

---

## 🧱 Organisation du projet

```
.
├── commande.h / commande.c         # Structure Commande + affichage
├── interaction.h / interaction.c  # Saisie utilisateur
├── file.h / file.c                # Buffer circulaire (file d’attente)
├── serveur.h / serveur.c          # Threads serveurs (producteurs)
├── cuisinier.h / cuisinier.c      # Threads cuisiniers (consommateurs)
├── log.h / log.c                  # Système de logs HTML
├── globals.h / globals.c          # Mutex, sémaphores, compteurs globaux
└── main.c                         # Initialisation et orchestration
```

---

## 🖥️ Fonctionnement du programme

### 1️⃣ Initialisation

* Création des mutex et des sémaphores
* Initialisation de la file circulaire
* Préparation du fichier `logs.html`

### 2️⃣ Lancement des threads

* 2 threads **serveurs**
* `NB_CUISINIERS` threads **cuisiniers**

### 3️⃣ Serveurs (producteurs)

* Réservent un numéro de commande
* Demandent un plat à l’utilisateur
* Vérifient si un cuisinier est disponible (`sem_trywait`)
* Ajoutent la commande dans la file d’attente

### 4️⃣ Cuisiniers (consommateurs)

* Attendent une commande disponible
* Retirent la commande de la file
* Simulent la préparation (`sleep`)
* Journalisent la fin de la commande

### 5️⃣ Fin du programme

* Attente de la fin de tous les threads
* Destruction des mutex et sémaphores
* Affichage d’un résumé final

---

## 🔐 Synchronisation utilisée

| Ressource                | Type      | Rôle                                 |
| ------------------------ | --------- | ------------------------------------ |
| `mutex_file`             | Mutex     | Protège la file circulaire           |
| `mutex_compteur`         | Mutex     | Protège les compteurs globaux        |
| `mutex_affichage`        | Mutex     | Évite les affichages concurrents     |
| `mutex_saisie`           | Mutex     | Évite les saisies concurrentes       |
| `places_libres`          | Sémaphore | Nombre de places libres dans la file |
| `commandes_disponibles`  | Sémaphore | Nombre de commandes prêtes           |
| `cuisiniers_disponibles` | Sémaphore | Nombre de cuisiniers libres          |

---

## 📝 Exemple de log HTML

Le fichier `logs.html` contient des entrées telles que :

```html
<div class="log">
  <div class="time">[14:32:10]</div>
  <div class="msg">Serveur 1 a pris la commande #3 (pizza)</div>
</div>
```

---

## 🐧 Environnement d’exécution (Linux)

Ce projet doit être exécuté sous **Linux**, car il utilise :

* les threads POSIX (`pthread`),
* les sémaphores POSIX (`sem_t`),
* des appels système Unix (`sleep`, etc.).

### Environnements compatibles

* Ubuntu / Debian
* Fedora / Arch
* WSL (Windows Subsystem for Linux)
* Machines virtuelles Linux

---

## ⚙️ Compilation

Placez-vous dans le dossier du projet puis exécutez :

```bash
gcc -pthread *.c -o restaurant
```

### Explications

* `-pthread` : active la gestion des threads POSIX
* `*.c` : compile tous les fichiers sources
* `-o restaurant` : génère l’exécutable final

---

## ▶️ Exécution

Lancez simplement :

```bash
./restaurant
```

Au démarrage, le programme :

* initialise les mutex et sémaphores,
* crée les threads serveurs et cuisiniers,
* attend les saisies utilisateur,
* gère la file d’attente et la préparation,
* écrit toutes les actions dans `logs.html`.

---
