def resposta_1(grafo):
    predecessors = grafo.DFS_CFC()
    S = [[i] for i in range(grafo.qtdVertices())]

    for v in range(grafo.qtdVertices()):
        if predecessors[v] != -1:
            a = [y for x in [S[v], S[predecessors[v]]] for y in x]
            for i in a:
                S[i] = a
    output = []
    for row in S:
        if row not in output:
            output.append(row)

    for i in range(len(output)):
        print(','.join(map(grafo.rotulo, sorted(output[i]))))
