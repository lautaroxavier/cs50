height = -1
while height not in range(1, 9):
    try:
        height = int(input("Height: "))
    except:
        continue

height = int(height)
for i in range(height):
    for _ in range(height - i - 1):
        print(" ", end="")

    for _ in range(i + 1):
        print("#", end="")

    print("  ", end="")

    for _ in range(i + 1):
        print("#", end="")
    print()
