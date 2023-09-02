import csv
import sys

# ADN es una secuencia de nucleotidos
# nucleotidos tienen 4 bases posibles (ACGT)
# algunas porciones de la secuencia de nucleotidos tienen alta variacion genetica
# los STR son secuencias de bases de nucleotidos que se repiten varias veces
# para identificar el ADN de una persona se usan varias STR


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: dna.py <database> <sequence>")
        return
    # TODO: Read database file into a variable
    profile_list = []
    with open(sys.argv[1]) as db_file:
        db_reader = csv.DictReader(db_file)
        for profile in db_reader:
            profile_list.append(profile)
    str_list = list(profile_list[0].keys())
    str_list.remove("name")
    # TODO: Read DNA sequence file into a variable
    seq_file = open(sys.argv[2])
    sequence = seq_file.readline()
    # TODO: Find longest match of each STR in DNA sequence
    target_profile = {}
    for str in str_list:
        target_profile[str] = longest_match(sequence, str)
    # TODO: Check database for matching profiles
    for profile in profile_list:
        match = True
        for subseq in target_profile:
            target_length = int(target_profile[subseq])
            profile_length = int(profile[subseq])
            match = target_length == profile_length
            if not match:
                break
        if match:
            print(profile["name"])
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
