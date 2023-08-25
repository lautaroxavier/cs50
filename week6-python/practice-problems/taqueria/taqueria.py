menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

def main():
    total = 0
    while True:
        try:
            print("Item: ", end="")
            item = input()
            item = item.title()
            if item in menu:
                total += menu[item]
                format_total = "{:.2f}".format(total)
                print(f"Total: ${format_total}")
        except EOFError:
            break
    print()
    format_total = "{:.2f}".format(total)
    print(f"Total: ${format_total}")


main()