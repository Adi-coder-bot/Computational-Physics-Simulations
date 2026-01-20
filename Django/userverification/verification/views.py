from django.shortcuts import render, redirect
from verification.models import database
from django.contrib import messages

# Create your views here.
def signup(request):

    type = [
        {'name':'name', 'label':'Name', 'type':'text'},
        {'name':'number', 'label':'Phone Number', 'type':'text'},
        {'name':'email', 'label':'Email', 'type':'email'},
        {'name':'password', 'label':'Password', 'type':'password'},
    ]

    if request.method =="POST":
        name = request.POST.get("name")
        number = request.POST.get("number")
        email = request.POST.get("email")
        password = request.POST.get("password")

        if len(number) < 10 or len(number) > 10:
            messages.error(request, "The number entered is invalid")
            return redirect("signup")

        database.objects.create(name = name, number = number, email = email, password = password)
        return redirect("login")
    

    return render(request, 'signup.html', {'N':{'name':'signup', 'heading':'Sign Up'}, 'typ':type, 't':'signup'})

def login(request):
    type = [
        {'name':'email', 'label':'Email', 'type':'email'},
        {'name':'password', 'label':'Password', 'type':'password'},
    ]

    if request.method == "POST":
        Email = request.POST.get("email")
        Password = request.POST.get("password")

        try:
            user = database.objects.get(email = Email)
            if user.password == Password:
                response = [
                    {'name':'Name:- ', 'value':user.name},
                    {'name':'Phone Number:- ', 'value':user.number},
                ]

                return render(request, 'signup.html', {'response':response, 't':'login'})
            else:
                response = 'invalid email or password. try again...'
                messages.error(request, "Invalid password. Try again...")

        except database.DoesNotExist:
            messages.error(request, "User not found")

    return render(request, 'signup.html', {'N':{'name':'login', 'heading':'Login'}, 'typ':type, 't':'signup'})
