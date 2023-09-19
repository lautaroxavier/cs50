from flask import Flask, render_template, request

# crear una instancia de Flask con el archivo actual
app = Flask(__name__)

# codigo a ejecutar cuando el usuario visita "/", la pagina por defecto del sitio
# la funcion puede tener cualquier nombre
@app.route("/", methods=["GET", "POST"])
def index():
    # requests.args es un diccionario con las claves y valores que envio el usuario
    # el metodo .get() tiene como primer argumento la clave del valor que quiero obtener 
    # y el segundo argumento es el valor que devuelve si la clave no existe
    # name = request.args.get("name", "anonimo")
    # busca el archivo en templates/
    # los argumentos sucesivos son placeholder=nombre_variable
    # el placeholder se coloca como {{ placeholder }} en la plantilla ubicada en templates/
    # return render_template("index.html", name=name)
    if request.method == "GET":
        return render_template("index.html")
    elif request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "world"))
