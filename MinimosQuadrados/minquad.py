import numpy as np
import matplotlib.pyplot as plt

dados = np.loadtxt('minQuad.dat')
x = dados[:, 0]

# Funções para montar a matriz X
def potencia(x, y):
    # y = a * x^b -> log(y) = log(a) + b * log(x)
    X = np.column_stack((np.log(x), np.ones_like(x)))
    Y = np.log(y)
    return X, Y

def exponencial(x, y):
    # y = a * exp(b * x) -> log(y) = log(a) + b * x
    X = np.column_stack((x, np.ones_like(x)))
    Y = np.log(y)
    return X, Y

def poli2(x, y):
    # y ≈ ax² + bx + c
    X = np.column_stack((x**2, x, np.ones_like(x)))
    return X, y

def linear(x, y):
    # y ≈ ax + b
    X = np.column_stack((x, np.ones_like(x)))
    return X, y

def poli3(x, y):
    # y ≈ ax³ + bx² + cx + d
    X = np.column_stack((x**3, x**2, x, np.ones_like(x)))
    return X, y

# Modelos
modelos = {
    2: ('2y(x)=ax^b', potencia),
    3: ('3a*exp(b*x)', exponencial),
    4: ('4ax^2+bx+c', poli2),
    5: ('5ax+b', linear),
    6: ('6ax^3+bx^2+cx+d', poli3),
}

resultados = []

for modelo in range(2, 7):
    nome, montar = modelos[modelo]
    y = dados[:, modelo - 1]

    X, Y = montar(x, y)

    # Resolve mínimos quadrados
    coef = np.linalg.solve(X.T @ X, X.T @ Y)
    resultados.append((modelo, nome, coef, y))

fig, axes = plt.subplots(3, 2, figsize=(12, 12))
axes = axes.flatten()

for i, (modelo, nome, coef, y_real) in enumerate(resultados):
    ax = axes[i]

    # Calcula o ajuste
    if modelo == 2:  # potência
        a, b = np.exp(coef[1]), coef[0]
        y_fit = a * x**b

    elif modelo == 3:  # exponencial
        a, b = np.exp(coef[1]), coef[0]
        y_fit = a * np.exp(b * x)

    elif modelo == 4:  # polinômio grau 2
        a, b, c = coef
        y_fit = a*x**2 + b*x + c

    elif modelo == 5:  # linear
        a, b = coef
        y_fit = a*x + b

    elif modelo == 6:  # polinômio grau 3
        a, b, c, d = coef
        y_fit = a*x**3 + b*x**2 + c*x + d

    # Plota
    ax.scatter(x, y_real, s=12, label='Dados')
    ax.plot(x, y_fit, 'r--', label='Ajuste')
    ax.set_title(nome)
    ax.grid(True)
    ax.legend()

fig.delaxes(axes[5]) # Remove o subplot sobrando

plt.tight_layout()
plt.show()
