def insertion_sort(lista):
    for i in range(1, len(lista)):
        chave = lista[i]
        j = i-1
        while j >=0 and chave < lista[j] :
                lista[j+1] = lista[j]
                j -= 1
        lista[j+1] = chave
    return lista