import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = rows[0]["cash"]
    total_balance = cash
    portfolio = db.execute("SELECT symbol, SUM(quantity) as quantity FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    for stock in portfolio:
        stock["price"] = (lookup(stock["symbol"]))["price"]
        stock["price"] = stock["price"]
        stock["total_value"] = stock["price"] * stock["quantity"]
        total_balance += stock["total_value"]
    cash = round(cash, 2)
    total_balance = round(total_balance, 2)
    return render_template("index.html", portfolio=portfolio, cash=cash, total=total_balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("that's not a number")
        if shares < 1:
            return apology("Only positive numbers")
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("Stock not found")
        price = stock_info["price"]
        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if len(rows) != 1:
            return apology("user not found")
        cash = rows[0]["cash"]
        total_price = price * shares
        if cash < total_price:
            return apology("Not enough funds")
        cash -= total_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, quantity, stock_price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, shares, price)
        
        return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT symbol, quantity, stock_price, timestamp FROM transactions WHERE user_id = ?", session["user_id"])
    transactions.reverse()
    return render_template("history.html", transactions=transactions)


@app.route("/add", methods=["POST"])
@login_required
def add():
    """Add money to account"""
    amount = request.form.get("amount")
    try:
        amount = int(amount)
    except ValueError:
        return apology("Not a valid amount")
    if amount <= 0:
        return apology("Not a valid amount")
    rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = rows[0]["cash"]
    cash += amount
    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
    return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        response = lookup(request.form.get("symbol"))
        if not response:
            return apology("Stock not found")
        return render_template("quoted.html", symbol=response["symbol"], price=response["price"])
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("Username not valid")
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("Username already exists")
        password = request.form.get("password")
        if not password:
            return apology("Not a valid password")
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("The passwords don't match")
        hash_password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_password)
        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT symbol, shares FROM (SELECT symbol, SUM(quantity) as shares FROM transactions WHERE user_id = ? GROUP BY symbol) WHERE shares > 0", session["user_id"])
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol or not shares:
            return apology("Invalid input")
        try:
            shares = int(shares)
        except ValueError:
            return apology("Not a number")
        if shares < 0:
            return apology("The number of shares must be a positive integer")
        for stock in stocks:
            if stock["symbol"] == symbol and stock["shares"] >= shares:
                price = (lookup(symbol))["price"]
                rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
                cash = rows[0]["cash"]
                cash += price * shares
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
                db.execute("INSERT INTO transactions (user_id, symbol, quantity, stock_price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, -1 * shares, price)
                return redirect("/")
        return apology("Error selling shares")
    
    return render_template("sell.html", stocks=stocks)
