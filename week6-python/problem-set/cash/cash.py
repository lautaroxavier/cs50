import cs50

change = cs50.get_float("Change owed: ")
while change < 0:
    change = cs50.get_float("Change owed: ")

quarter = 0.25
dime = 0.10
nickel = 0.05
penny = 0.01

answer = 0

while round((change - quarter), 2) >= 0:
    change -= quarter
    change = round(change, 2)
    answer += 1

while round((change - dime), 2) >= 0:
    change -= dime
    change = round(change, 2)
    answer += 1

while round((change - nickel), 2) >= 0:
    change -= nickel
    change = round(change, 2)
    answer += 1

while round((change - penny), 2) >= 0:
    change -= penny
    change = round(change, 2)
    answer += 1

print(answer)