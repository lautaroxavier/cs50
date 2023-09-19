from flask import Flask, render_template, redirect, request
from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

sports_list = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee"
]


@app.route("/")
def index():
    return render_template("index.html", sports=sports_list)


@app.route("/register", methods=["POST"])
def register():
    #validar entrada
    name = request.form.get("name")
    sport = request.form.get("sport")
    if not name or sport not in sports_list:
        return render_template("failure.html")
    # guardar nuevo registro
    db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)
    # confirmar registro
    return redirect("/registrants")


@app.route("/registrants")
def registrants():
    registrants_list = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants_list)


@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")
