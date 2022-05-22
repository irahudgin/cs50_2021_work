import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    # Complete the implementation of index in such a way that it
    # displays an HTML table summarizing, for the user currently logged in,
    # which stocks the user owns,
    # the numbers of shares owned,
    # the current price of each stock,
    # and the total value of each holding
    # (i.e., shares times price).
    # Also display the user’s current cash balance along with a grand total (i.e., stocks’ total value plus cash).


    # Odds are you’ll want to execute multiple SELECTs. Depending on how you implement your table(s), you might find GROUP BY HAVING SUM and/or WHERE of interest.
    # Odds are you’ll want to call lookup for each stock.

    stockinfo = db.execute("SELECT * FROM owned WHERE users_id = ?", session['user_id'])
    cashinfo = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])

    totals = 0
    for stock in stockinfo:
        totals = totals + round((stock['price']*stock['shares']), 2)

    if request.method == "POST":
        cashtoadd = float(request.form.get("cash"))
        cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])

        newcash = cashtoadd + float(cash[0]['cash'])

        db.execute("UPDATE users SET cash=? WHERE id=?", newcash, session['user_id'])

        return redirect("/")

    return render_template("index.html", stockinfo=stockinfo, cashinfo=cashinfo, round=round, totals=totals, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # checks for valid symbol and shares
        symbol = request.form.get("symbol")
        stockinfo = lookup(symbol)
        shares = request.form.get("shares")

        if symbol == '':
            return apology("Enter a stock")
        elif stockinfo == None and not symbol == '':
            return apology("invalid symbol")

        if shares[0] == "-":
            return apology("Shares must be positive")
        elif not shares.isdecimal():
            return apology("Shares must be whole number")
        elif shares == "0":
            return apology("Invalid shares")

        intshares = int(shares)

        # TODO
        # store cash from users in var
        usercashdict = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])
        usercash = usercashdict[0]['cash']

        # store money required in var as intshares * stockinfo['price']
        cashrequired = intshares * stockinfo['price']
        updatedusercash = round((usercash - cashrequired), 2)

        if updatedusercash < 0:
            return apology("Lacking cash for transaction")

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedusercash, session['user_id'])
        db.execute("INSERT INTO transactions (users_id, stock, shares, price, time, name) VALUES (?, ?, ?, ?, ?, ?)", session['user_id'], stockinfo['symbol'], intshares, stockinfo['price'], datetime.now(), stockinfo['name'])
        db.execute("INSERT INTO owned (users_id, symbol, name, shares, price, time) VALUES (?, ?, ?, ?, ?, ?)", session['user_id'], stockinfo['symbol'], stockinfo['name'], intshares, stockinfo['price'], datetime.now())

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    stockhistories = db.execute("SELECT * FROM transactions WHERE users_id=?", session['user_id'])
    return render_template("history.html", stockhistories=stockhistories, usd=usd)


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
        stocksymbol = request.form.get("symbol")
        stockinfo = lookup(stocksymbol)

        if stockinfo == None:
            return apology("Invalid symbol")
        elif stocksymbol == '':
            return apology("Need to input stock")

        return render_template("quoted.html", stockinfo=stockinfo, usd=usd)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmpassword = request.form.get("confirmation")

        # checks for blank and password matching
        if username == '':
            return apology("must enter username")
        elif password == '':
            return apology("must enter password")
        elif not password == confirmpassword:
            return apology("passwords must match")

        # checks if username already exists in database
        checkuser = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(checkuser) > 0:
            return apology("username already exists")

        # enters username and hashed password into db
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", username, generate_password_hash(password))

        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbols = db.execute("SELECT symbol FROM owned WHERE users_id = ?", session['user_id'])
    if request.method == "POST":
        symbol = request.form.get("symbol")
        strshares = request.form.get("shares")
        shares_owned = db.execute("SELECT shares FROM owned WHERE symbol=? AND users_id=?", symbol, session['user_id'])
        stockinfo = lookup(symbol)

        # Checks if shares entered are integer
        if not strshares.isdecimal():
            return apology("Shares must be whole number")

        # Checks for shares owned vs shares requested to sell
        intshares = int(request.form.get("shares"))
        if intshares > shares_owned[0]['shares']:
            return apology("Not enough shares owned")
        elif intshares < 1:
            return apology("Shares must be Greater than 0")

        db.execute("INSERT INTO transactions (users_id, stock, shares, price, time, name) VALUES (?, ?, ?, ?, ?, ?)", session['user_id'], stockinfo['symbol'], -abs(intshares), stockinfo['price'], datetime.now(), stockinfo['name'])

        updateshares = shares_owned[0]['shares'] - intshares

        if updateshares == 0:
            # Delete owned stock from owned
            db.execute("DELETE FROM owned WHERE users_id=? AND symbol=?", session['user_id'], symbol)
            # Establish and set new cash amount from sold stock
            cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])
            newcash = cash[0]['cash'] + (intshares * stockinfo['price'])
            db.execute("UPDATE users SET cash=? WHERE id=?", newcash, session['user_id'])
        else:
            # Set updated shares in owned and new cash in users datatables
            cash = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])
            newcash = cash[0]['cash'] + (intshares * stockinfo['price'])

            db.execute("UPDATE owned SET shares=? WHERE users_id=? AND symbol=?", updateshares, session['user_id'], symbol)
            db.execute("UPDATE users SET cash=? WHERE id=?", newcash, session['user_id'])

        return redirect("/")
    return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
