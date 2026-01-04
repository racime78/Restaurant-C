# 🍽️ Simulation d’un Restaurant — Producteurs / Consommateurs (C, Threads, Mutex, Sémaphores)

Ce projet simule le fonctionnement d’un restaurant en environnement concurrent.  
Il met en œuvre le modèle **producteur–consommateur** avec :

- des **threads** (serveurs et cuisiniers),
- des **mutex** pour protéger les ressources critiques,
- des **sémaphores** pour gérer la synchronisation,
- un **buffer circulaire** pour la file d’attente des commandes,
- un **système de logs HTML** lisible dans un navigateur.

---

## 🧱 Organisation du projet

.
├── commande.h / commande.c         # Structure Commande + affichage
├── interaction.h / interaction.c  # Saisie utilisateur
├── file.h / file.c                # Buffer circulaire (file d’attente)
├── serveur.h / serveur.c          # Threads serveurs (producteurs)
├── cuisinier.h / cuisinier.c      # Threads cuisiniers (consommateurs)
├── log.h / log.c                  # Système de logs HTML
├── globals.h / globals.c          # Mutex, sémaphores, compteurs
└── main.c                         # Initialisation + orchestration


---

## 🖥️ Fonctionnement du programme

1. **Initialisation**
   - Création des mutex et sémaphores
   - Préparation du fichier `logs.html`

2. **Lancement des threads**
   - 2 serveurs
   - `NB_CUISINIERS` cuisiniers

3. **Serveurs**
   - Réservent un numéro de commande
   - Demandent un plat à l’utilisateur
   - Vérifient si un cuisinier est libre (`sem_trywait`)
   - Ajoutent la commande dans la file

4. **Cuisiniers**
   - Attendent une commande disponible
   - Retirent la commande
   - Simulent la préparation (sleep)
   - Loguent la fin de la commande

5. **Fin**
   - Attente de tous les threads
   - Destruction des ressources
   - Résumé final

---

## 🔐 Synchronisation utilisée

| Ressource              | Type        | Rôle |
|------------------------|-------------|------|
| `mutex_file`           | Mutex       | Protège la file circulaire |
| `mutex_compteur`       | Mutex       | Protège les compteurs globaux |
| `mutex_affichage`      | Mutex       | Empêche les affichages simultanés |
| `mutex_saisie`         | Mutex       | Empêche les saisies concurrentes |
| `places_libres`        | Sémaphore   | Nombre de places disponibles dans la file |
| `commandes_disponibles`| Sémaphore   | Nombre de commandes prêtes |
| `cuisiniers_disponibles`| Sémaphore  | Nombre de cuisiniers libres |

---

## 📝 Exemple de log HTML

Le fichier `logs.html` contient des entrées comme :

```html
<div class="log">
  <div class="time">[14:32:10]</div>
  <div class="msg">Serveur 1 a pris la commande #3 (pizza)</div>
</div>
```
