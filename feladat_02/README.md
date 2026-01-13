# 2. Feladat: Zombi-vadászat

## Cél

Megérteni a **zombie folyamatok** problémáját és a `wait()` rendszerhívás szükségességét.

## Mi az a zombie folyamat?

Amikor egy gyerek folyamat befejeződik, de a szülő nem kérdezi le az exit státuszt, a gyerek "zombivá" válik. Nem foglal memóriát, de a process table-ben ott marad a bejegyzése.

A `ps aux` kimenetben **`Z`** státusszal jelenik meg (pl. `<defunct>`).

## 1. rész: Készíts zombit!

Módosítsd a `zombie_demo.c` fájlt úgy, hogy:

1. A gyerek folyamat alszik 2 másodpercig, majd kilép
2. A szülő **NE** hívja meg a `wait()`-et
3. A szülő alszik 10 másodpercig (hogy legyen idő megfigyelni)

Fordítás után **két terminált nyiss**:
- Az egyikben futtasd a programot: `./zombie_demo`
- A másikban nézd meg a folyamatokat: `ps aux | grep defunct`

Látni fogsz egy `<defunct>` bejegyzést!

## 2. rész: Megoldás

Módosítsd a kódot, hogy a szülő meghívja a `wait(NULL)` függvényt a gyerek befejezése után.

```c
#include <sys/wait.h>

// ...
wait(NULL); // Megvárja a gyerek folyamatot és eltakarítja
```

Most már nem lesz zombie!

## Fordítás és futtatás

```bash
gcc zombie_demo.c -o zombie_demo
./zombie_demo
```

Másik terminálban (a futás közben):
```bash
ps aux | grep Z
# vagy
ps aux | grep defunct
```

## Kérdések

1. Mi történik, ha a szülő hamarabb kilép, mint a gyerek?  
   *Tipp: a gyerek PID 1-re (init/systemd) kerül adoptálásra*

2. Miért fontos a `wait()` egy hosszú ideig futó szerverben?

---

**Megjegyzés:** Modern rendszereken a `systemd` vagy `init` automatikusan adoptálja az árva folyamatokat.
