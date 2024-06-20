# Aucun n'import ne doit être fait dans ce fichier


def nombre_entier(n: int) -> str:
    return "S" * n + "0"
    return f*"{'S' * n}0"


def S(n: str) -> str:
    return "S" + n


def addition(a: str, b: str) -> str:
    if a == "0":
        return b
    return S(addition(a[1:], b))
    #return a[:-1] + b


def multiplication(a: str, b: str) -> str:
    if a == "0":
        return "0"
    return addition(multiplication(a[1:],b),b)


def facto_ite(n: int) -> int:
    pass


def facto_rec(n: int) -> int:
    pass


def fibo_rec(n: int) -> int:
    pass


def fibo_ite(n: int) -> int:
    pass


def golden_phi(n: int) -> int:
    pass


def sqrt5(n: int) -> int:
    pass


def pow(a: float, n: int) -> float:
    pass
