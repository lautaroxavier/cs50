from cs50 import SQL
import csv

# create database with this command
# cat schema.sql | sqlite3 prophecy.db

# open sql database
db = SQL("sqlite:///prophecy.db")

# load csv into a list of dictionaries
students_data = []
with open("students.csv") as datafile:
    reader = csv.DictReader(datafile)
    for row in reader:
        students_data.append(row)

# create a dictionary for each house with id, name and head
houses_names = []
houses = []
for student in students_data:
    if student["house"] not in houses_names:
        houses_names.append(student["house"])
        house = {"id": len(houses) + 1, "name": student["house"], "head": student["head"]}
        houses.append(house)

# create a dictionary for each student correspondence with each house
memberships = []
for student in students_data:
    membership = {"student_id": student["id"]}
    for house in houses:
        if house["name"] == student["house"]:
            membership["house_id"] = house["id"]
            break
    memberships.append(membership)

# insert the data in each sql table 
for student in students_data:
    db.execute("INSERT INTO students (id, student_name) VALUES (?, ?);", student["id"], student["student_name"])

for house in houses:
    db.execute("INSERT INTO houses (id, house_name, head) VALUES (?, ?, ?);", house["id"], house["name"], house["head"])

for membership in memberships:
    db.execute("INSERT INTO membership (student_id, house_id) VALUES (?, ?);", membership["student_id"], membership["house_id"])
