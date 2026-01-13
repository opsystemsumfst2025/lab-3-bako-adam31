# 4. Feladat: Szinkronizáció szemaforokkal

## Cél

A race condition problémájának megoldása **POSIX szemaforok** segítségével.

## Mi az a szemafor?

A szemafor egy **szinkronizációs primitív**, ami biztosítja, hogy egyszerre csak egy folyamat (vagy szál) léphessen be egy kritikus szakaszba.

### Két alapművelet:

- **`sem_wait()`**: "Szeretnék belépni a kritikus szakaszba"  
  *(Ha foglalt, várakozik. Ha szabad, csökkenti a számlálót és belép.)*

- **`sem_post()`**: "Kilépek a kritikus szakaszból"  
  *(Növeli a számlálót, jelezve, hogy szabaddá vált.)*

## Mutex szemafor

Ha a szemafor kezdőértéke **1**, akkor úgy viselkedik, mint egy **mutex** (mutual exclusion lock).

```c
sem_wait(&mutex);   // LOCK
// ... kritikus szakasz ...
sem_post(&mutex);   // UNLOCK
```

## Feladat

Vedd az előző feladat kódját (shared memory + counter), és védd a `counter++` műveletet szemaforral!

### Lépések:

1. Hozz létre egy `SharedData` struktúrát, ami tartalmazza a `counter`-t ÉS a szemafort
2. Inicializáld a szemafort `sem_init(&mutex, 1, 1)` hívással:
   - `1` = process-shared (nem thread!)
   - `1` = kezdőérték (nyitott állapot)
3. Minden `counter++` előtt hívd meg a `sem_wait()`-et
4. Utána pedig a `sem_post()`-ot

Most az eredmény **mindig 200 000 lesz**! 🎉

## Fordítás

```bash
gcc shared_mem_sem.c -o shared_mem_sem -pthread
```

A `-pthread` flag azért kell, mert a POSIX szemaforok a `pthread` library-hoz tartoznak.

## Kérdések

1. Mi történne, ha elfelejtjük a `sem_post()`-ot?  
   *(Deadlock! A másik folyamat örökké várakozna.)*

2. Miért kell a szemafort is a shared memory-ban tárolni?

3. Mennyivel lassabb lett a program a szinkronizáció miatt?  
   *(Próbáld ki `time ./shared_mem_sem` vs `time ./shared_mem`)*

---

**Tanulság:** A szinkronizáció helyességet ad, de teljesítményt vesz el. Érdemes csak ott használni, ahol tényleg kell!
