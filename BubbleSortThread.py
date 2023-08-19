import threading

def bubble_sort_threaded(lista):
    n = len(lista)
    for i in range(n):
        threads = []
        for j in range(0, n-i-1):
            t = threading.Thread(target=swap, args=(lista, j))
            t.start()
            threads.append(t)
        for t in threads:
            t.join()
    return lista

def swap(lista, j):
    if lista[j] > lista[j+1]:
        lista[j], lista[j+1] = lista[j+1], lista[j]