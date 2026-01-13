# Házi feladat: Ping-Pong 🏓

## Cél

Szigorú **sorrendiség** kikényszerítése folyamatok között két szemaforral.

## Feladat

Írj egy programot, ahol a szülő és a gyerek felváltva írja ki a "PING" és "PONG" szavakat!

### Szabályok:

1. A szülő ír "PING"-et
2. Ezután a gyerek ír "PONG"-ot
3. Majd megint a szülő ír "PING"-et
4. És így tovább... (pl. 10-szer)

**Kimenet:**
```
PING
PONG
PING
PONG
PING
PONG
...
```

## Megoldási ötlet

Használj **két szemafort**:

- `sem_parent` - kezdőérték: **1** (a szülő indíthat)
- `sem_child` - kezdőérték: **0** (a gyerek vár)

### Pszeudokód a szülőnek:

```
10-szer ismételd:
    sem_wait(sem_parent)   // Várd meg, hogy te jöhess
    printf("PING\n")
    sem_post(sem_child)    // Engedd el a gyereket
```

### Pszeudokód a gyereknek:

```
10-szer ismételd:
    sem_wait(sem_child)    // Várd meg, hogy te jöhess
    printf("PONG\n")
    sem_post(sem_parent)   // Engedd vissza a szülőt
```

## Tesztelés

Ha jól írtad meg, a kimenet **MINDIG** szabályos ping-pong lesz, soha nem keveredik!

## Bónusz kihívások (opcionális)

1. **Számozott kimenet:** Írd ki, hogy "PING #1", "PONG #1", "PING #2", stb.
2. **N folyamat:** Mi lenne, ha nem 2, hanem 3 folyamat vált egymást? (Ping-Pong-Boom)
3. **Késleltetés:** Tegyél be `usleep(100000)` hívásokat (0.1 sec), hogy lassított videóban lásd!

---

## Fordítás

```bash
gcc ping_pong.c -o ping_pong -pthread
./ping_pong
```
 
**Jó munkát!** Ez az egyik legklasszikusabb szinkronizációs feladat. 🎯
