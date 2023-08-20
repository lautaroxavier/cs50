greeting = input("Greeting: ")
for i in range(len(greeting)):
    if greeting[i] == " ":
        continue
    if greeting[i:i+5].lower() == "hello":
        print("$0")
        break
    elif greeting[i].lower() == "h":
        print("$20")
        break
    else:
        print("$100")
        break
