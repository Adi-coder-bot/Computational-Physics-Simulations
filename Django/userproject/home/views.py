from django.shortcuts import render, redirect
from django.contrib.auth.models import User
from django.contrib.auth import authenticate, login, logout

# Password for user Harry is HARRY$$$***000

def index(request):
    if request.user.is_anonymous:
        return redirect('login')
    
    else:
        return render(request, 'index.html')

def loginUser(request):
    if request.method == 'POST':
        name = request.POST.get('name')
        password = request.POST.get('password')
        user = authenticate(username = name, password = password)

        if user is not None:
            login(request, user)
            return redirect('index')
        
        else:
            return render(request, 'login.html', {'error': 'Invalid Credentials'})
        
    else:
        return render(request, 'login.html')
        
def logoutUser(request):
    logout(request)
    return redirect('login')