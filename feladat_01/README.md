# 1. Feladat: A sejtosztódás

## Cél

Megérteni, hogyan működik a `fork()` rendszerhívás, és hogy a kód két helyen fut egyszerre.

## Feladat

Írd meg a `fork_test.c` programot, ami bemutatja a folyamat-klónozást!

### Mit kell tenned?

1. Írd ki a program PID-jét a `fork()` előtt
2. Hívd meg a `fork()` rendszerhívást
3. Ellenőrizd a visszatérési értéket:
   - Ha negatív: hiba történt
   - Ha 0: te vagy a gyerek folyamat
   - Ha pozitív: te vagy a szülő (a szám a gyerek PID-je)
4. Írd ki mindkét folyamat adatait (PID, PPID)

 

## Fordítás és futtatás

```bash
gcc fork_test.c -o fork_test
./fork_test
```

## Kérdések gondolkodásra

1. Mi történik, ha a `printf`-et a `fork()` **elé** rakjuk? Hányszor jelenik meg?
2. Mi történik, ha **utána** rakjuk?
3. Miért lehet, hogy keveredik a kimenet a terminálon?

## Hasznos függvények

- `getpid()` - visszaadja az aktuális folyamat PID-jét
- `getppid()` - visszaadja a szülő folyamat PID-jét
- `fork()` - új folyamat létrehozása

---

**Tipp:** Futtasd le többször! A folyamatok ütemezése változhat, így a kimenet sorrendje is.
