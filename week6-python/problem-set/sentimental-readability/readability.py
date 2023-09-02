def main():
    text = input("Text: ")
    # count words, sentences and letters
    words = text.split(" ")
    words_count = len(words)
    sentence_delimiters = [".", "?", "!"]
    sentences_count = 0
    for char in text:
        if char in sentence_delimiters:
            sentences_count += 1
    letters_count = 0
    for char in text:
        if char.isalpha():
            letters_count += 1
    L = (letters_count / words_count) * 100
    S = (sentences_count / words_count) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    index = round(index)
    if index < 1:
        print(f"Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

main()