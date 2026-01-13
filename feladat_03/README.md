# 3. Feladat: Versenyhelyzet (Race Condition)

## Cél

Megérteni, hogy a `fork()` után a folyamatok **külön memóriaterületet** kapnak, és hogy mi történik, ha közös memóriát használnak **szinkronizáció nélkül**.

## A probléma

Ha a szülő és a gyerek is módosít egy közös változót, **versenyhelyzet** (race condition) alakul ki. A művelet kimenetele függ attól, hogy a CPU melyik folyamatot ütemezi éppen.

## Shared Memory (`mmap`)

A `mmap()` függvénnyel közös memóriaterületet tudunk lefoglalni. A `MAP_SHARED | MAP_ANONYMOUS` flagekkel a folyamatok megoszthatják ezt a területet.

## Feladat

Hozz létre egy `counter` változót shared memory-ban. Mind a szülő, mind a gyerek 100 000-szer növeli ezt a számot.

**Elvárás:** 200 000  
**Valóság:** ~140 000 - 190 000 (véletlenszerű!)

### Miért?

A `counter++` művelet **nem atomi**! Valójában három lépés:

1. Olvasás: `temp = counter`
2. Növelés: `temp = temp + 1`
3. Írás: `counter = temp`

Ha a két folyamat egyszerre hajtja végre, elvesznek frissítések.

## Fordítás és futtatás

```bash
gcc shared_mem.c -o shared_mem
./shared_mem
```

Futtasd le többször! Az eredmény minden alkalommal más lesz.

## Kérdések

1. Miért nem pontosan 200 000 az eredmény?
2. Mi lenne a megoldás? *(Tipp: következő feladat!)*
3. Mi történne, ha csak 10-szer növelnénk a countert? És 1 000 000-szor?

---

**Tanulság:** A közös memória önmagában nem elég. Kell egy szinkronizációs mechanizmus!
