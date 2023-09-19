from flask import Flask, render_template, request

app = Flask(__name__)

colors = ["blue", "red"]


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        print("Form submitted!")
        color = request.form.get("color")
        if color in colors:
            return render_template("color.html", color=color)
    return render_template("index.html")

