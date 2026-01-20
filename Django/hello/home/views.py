from django.shortcuts import render, HttpResponse
from datetime import datetime
from home.models import Contact
from django.contrib import messages

# Create your views here.
def index(request):
    # return HttpResponse("This is a Home Page.")
    context = {
        'variable1' : 'Aditya is Great',
        'variable2' : 'Varun is great'
    }
    return render(request, 'index.html', context)

def about(request):
    return render(request, 'about.html')
    # return HttpResponse("This is a About Page.")

def services(request):
    return render(request, 'services.html')
    # return HttpResponse("This is a Services Page.")

def contact(request):
    if request.method == "POST":
        name = request.POST.get('name')
        age = request.POST.get('age')
        phone = request.POST.get('phone')
        email = request.POST.get('email')
        contact = Contact(name = name, age = age, phone = phone, email = email, date = datetime.today())
        contact.save()
        messages.success(request, 'Profile details updated.')
    return render(request, 'contact.html')
    # return HttpResponse("This is a Contact Page.")