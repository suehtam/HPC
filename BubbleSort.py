import random
import time
tempo_inicial = time.time()
def bubble_sort(lista):
    n = len(lista)
    for i in range(n):
        for j in range(0, n-i-1):
            if lista[j] > lista[j+1]:
                lista[j], lista[j+1] = lista[j+1], lista[j]
    return lista
entrada = [random.randint(0, 10000) for _ in range(5000)]
print(bubble_sort(entrada))
tempo_final = time.time()
print(f"{tempo_final - tempo_inicial} segundos")