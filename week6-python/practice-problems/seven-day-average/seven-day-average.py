import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    prev_cases = {}
    for reg in reader:
        state = reg["state"]
        cases = int(reg["cases"])
        if state not in new_cases:
            new_cases[state] = [cases]
            prev_cases[state] = cases
        else:
            new_cases[state] += [cases - prev_cases[state]]
            prev_cases[state] = cases
        if len(new_cases[state]) > 14:
            new_cases[state] = new_cases[state][1:]
    return new_cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):

    for state in states:
        cur_week_avg = 0
        last_week_avg = 0
        daily_cases = new_cases[state]
        for cases in daily_cases[7:]:
            cur_week_avg += cases
        for cases in daily_cases[:7]:
            last_week_avg += cases
        cur_week_avg /= 7
        last_week_avg /= 7
        dif = cur_week_avg - last_week_avg
        try:
            dif /= last_week_avg
        except ZeroDivisionError:
            print("Error: division por cero.")
        print(f"{state} had a 7-day average of {round(cur_week_avg)} cases and a change of {round(dif * 100)}% compared to the last week.")


main()