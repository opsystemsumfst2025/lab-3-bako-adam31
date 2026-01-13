# Makefile a 3. Labor feladataihoz
# Használat:
#   make all        - Minden feladat fordítása
#   make feladat_01 - Csak az első feladat
#   make clean      - Tisztítás

CC = gcc
CFLAGS = -Wall -Wextra
PTHREAD_FLAGS = -pthread

# Feladatok céljai
TARGETS = feladat_01/fork_test \
          feladat_02/zombie_demo \
          feladat_03/shared_mem \
          feladat_04/shared_mem_sem \
          hazi/ping_pong

# Alapértelmezett cél
all: $(TARGETS)

# 1. Feladat: Fork alapok
feladat_01: feladat_01/fork_test

feladat_01/fork_test: feladat_01/fork_test.c
	$(CC) $(CFLAGS) $< -o $@

# 2. Feladat: Zombie és wait
feladat_02: feladat_02/zombie_demo

feladat_02/zombie_demo: feladat_02/zombie_demo.c
	$(CC) $(CFLAGS) $< -o $@

# 3. Feladat: Shared memory
feladat_03: feladat_03/shared_mem

feladat_03/shared_mem: feladat_03/shared_mem.c
	$(CC) $(CFLAGS) $< -o $@

# 4. Feladat: Szemaforok
feladat_04: feladat_04/shared_mem_sem

feladat_04/shared_mem_sem: feladat_04/shared_mem_sem.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

# Házi: Ping-Pong
hazi: hazi/ping_pong

hazi/ping_pong: hazi/ping_pong.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

# Tisztítás
clean:
	rm -f $(TARGETS)

# Phony célok (nem fájlnevek)
.PHONY: all clean feladat_01 feladat_02 feladat_03 feladat_04 hazi
