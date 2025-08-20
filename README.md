# README — cpp-insecure-app (FR/EN)

> **⚠️ Usage labo uniquement.** Ne compilez/exécutez jamais ce binaire sur des machines sensibles.

---

## FR — Présentation rapide

Petit binaire C++ avec de multiples vulnérabilités mémoire et mauvaises pratiques.

**CWE ciblées** : CWE‑120/121 (buffer overflow), CWE‑134 (format string), CWE‑78 (command injection), CWE‑415/416 (double free / UAF), CWE‑457 (uninitialized), CWE‑377 (tmp file prédictible), CWE‑732 (perms laxistes), CWE‑786 (out‑of‑bounds in `sprintf`), CWE‑330 (PRNG faible via `rand()`), CWE‑22 (path traversal lecture), CWE‑401 (memory leak), CWE‑798 (secret en dur).

### Construction

```bash
cd cpp-insecure-app
cmake -S . -B build
cmake --build build
./build/insecure_cpp
```

### Démonstrations (calibrage)

À l’exécution, choisissez l’option demandée :

* **1 Overflow** : entrez une chaîne >16 chars pour déclencher l’overflow dans `scanf/strcpy`.
* **2 Format string** : tapez `%x%x%x` pour afficher la pile (CWE‑134).
* **3 Command** : saisissez `whoami` (CWE‑78).
* **4 Double free** / **5 UAF** : chemins de corruption mémoire (analyseurs statiques les signalent sans exécution).
* **7 Tmp + 777** : crée `/tmp/insecure_cpp.tmp` et applique `chmod 777` (CWE‑377/732).
* **8 sprintf** : déclenche dépassement via `sprintf`.
* **9 rand token** : montre token prévisible (CWE‑330).
* **10 read** : essayez `../../etc/hosts` (CWE‑22).
* **11 leak** : fuite 1 MiB (CWE‑401).

### Conseils SAST

* **Ne remplacez pas** `scanf`/`strcpy` par leurs variantes sûres.
* Conservez `system()` et évitez d’ajouter des flags de durcissement au code source (les SAST regardent le code, pas l’ASLR/PIE).

### SCA optionnelle (Conan)

Ajoutez un `conanfile.txt` avec `libcurl/7.76.1` pour déclencher une alerte CVE (use‑after‑free). L’installation réelle de la lib n’est pas obligatoire pour la plupart des SCA (lecture manifeste).

### Scans types

```bash
semgrep --config p/ci --error cpp-insecure-app
snyk code test cpp-insecure-app
```

---

## EN — Quick overview

Tiny C++ program with classic memory issues and insecure patterns. Build & usage are the same as FR. See calibrations above to feed SAST.