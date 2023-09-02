# amex 15 digitos
# mastercard 16 digitos
# visa 13 o 16 digitos
# amex empieza con 34 o 37
# mastercard empieza con 51, 52, 53, 54 o 55
# visa empieza con 4

# algoritmo de luhn
    # multiplicar los digitos impares por 2
    # sumar los digitos de los productos
    # sumar los digitos pares
    # chequear que la suma total sea multiplo de 10

def main():
    card = input("Number: ")
    if (not luhns_algorithm(card)):
        print("INVALID")
        return
    if (is_amex(card)):
        print("AMEX")
        return
    if (is_visa(card)):
        print("VISA")
        return
    if (is_mastercard(card)):
        print("MASTERCARD")
        return
    print("INVALID")

def is_amex(card):
    if (len(card) != 15):
        return False
    if (card[:2] not in ["34", "37"]):
        return False
    return True

def is_visa(card):
    if (len(card) != 13 and len(card) != 16):
        return False
    if (card[0] != "4"):
        return False
    return True

def is_mastercard(card):
    if (len(card) != 16):
        return False
    if (int(card[:2]) not in [51, 52, 53, 54, 55]):
        return False
    return True

def luhns_algorithm(card_number):
    sum = 0
    card_number = card_number[::-1]
    # multiplicar digitos impares por 2 y sumar los digitos de los productos
    for i in range(1, len(card_number), 2):
        prod = int(card_number[i]) * 2
        sum += sumar_digitos(prod)
    for j in range(0, len(card_number), 2):
        sum += int(card_number[j])
    return sum % 10 == 0

def sumar_digitos(num):
    suma = 0
    for digit in str(num):
        suma += int(digit)
    return suma

main()