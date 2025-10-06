import random

def mediana_ponderada(elementos, pesos):
    alvo_peso = sum(pesos)/2
    return _mediana_passo_recursivo(elementos, pesos, alvo_peso)

def _mediana_passo_recursivo(elementos, pesos, alvo_peso):
    if len(elementos) == 1:
        return elementos[0]

    pivo = random.choice(elementos)
    
    menores, iguais, maiores = [], [], []
    pesos_menores, pesos_iguais, pesos_maiores = [], [], []

    for elem, peso in zip(elementos, pesos):
        if elem < pivo:
            menores.append(elem)
            pesos_menores.append(peso)
        elif elem == pivo:
            iguais.append(elem)
            pesos_iguais.append(peso)
        else:
            maiores.append(elem)
            pesos_maiores.append(peso)
    
    soma_pesos_menores = sum(pesos_menores)
    soma_pesos_iguais = sum(pesos_iguais)

    if soma_pesos_menores < alvo_peso <= soma_pesos_menores + soma_pesos_iguais:
        return pivo
    elif soma_pesos_menores >= alvo_peso:
        return _mediana_passo_recursivo(menores, pesos_menores, alvo_peso)
    else:
        novo_alvo = alvo_peso - soma_pesos_menores - soma_pesos_iguais
        return _mediana_passo_recursivo(maiores, pesos_maiores, novo_alvo)

class Cidade:
    def __init__(self, x, y, peso):
        self.x = x
        self.y = y
        self.peso = peso
    
    def coordenadas(self):
        return (self.x, self.y)
    
def localizacao_otima(cidades):
    coord_x = [cidade.x for cidade in cidades]
    coord_y = [cidade.y for cidade in cidades]
    pesos = [cidade.peso for cidade in cidades]
    
    soma_p = sum(pesos)
    pesos_normalizados = [p/soma_p for p in pesos]
    
    print("Calculando a mediana ponderada para as coordenadas X...")
    print(f"  Coordenadas X: {coord_x}")
    print(f"  Pesos: {pesos}\n")
    
    x_otimo = mediana_ponderada(coord_x, pesos_normalizados)
    
    print("Calculando a mediana ponderada para as coordenadas Y...")
    print(f"  Coordenadas Y: {coord_y}")
    print(f"  Pesos: {pesos}\n")
    
    y_otimo = mediana_ponderada(coord_y, pesos_normalizados)
    
    return (x_otimo, y_otimo)

if __name__ == "__main__":
    c_a = Cidade(x=1, y=8, peso=450000) # Capital A
    c_b = Cidade(x=10, y=2, peso=450000) # Capital B
    c_c = Cidade(x=5, y=5, peso=50000) # Vila do Meio
    
    cidades = [c_a, c_b, c_c]
    
    for index,cidade in enumerate(cidades):
        print(f"Cidade {index+1}")
        print(f"Coordenadas: {cidade.coordenadas()}")
        print(f"Habitantes: {cidade.peso}")
        print()
    
    print(
    f"A localização ótima para a agência postal é: {localizacao_otima(cidades)}"
    )
    
    