import threading

def insertion_sort_threaded(lista):
    for i in range(1, len(lista)):
        t = threading.Thread(target=insert, args=(lista, i))
        t.start()
        t.join()
    return lista

def insert(lista, i):
    chave = lista[i]
    j = i-1
    while j >=0 and chave < lista[j] :
            lista[j+1] = lista[j]
            j -= 1
    lista[j+1] = chave