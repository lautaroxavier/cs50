from pyfiglet import Figlet
import sys
import random

def main():
    figlet = Figlet()
    fonts = figlet.getFonts()

    if len(sys.argv) == 1:
        random.seed()
        idx = random.randint(0, len(fonts) - 1)
        font = fonts[idx]

    if len(sys.argv) == 3:
        if sys.argv[1] not in ["-f", "--font"]:
            print("Invalid usage")
            sys.exit(1)
        if sys.argv[2] not in fonts:
            print("Invalid usage")
            sys.exit(1)
        font = sys.argv[2]

    figlet.setFont(font=font)
    s = input("Input: ")
    print("Output:")
    print(figlet.renderText(s))

main()