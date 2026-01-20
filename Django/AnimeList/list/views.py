from django.shortcuts import render, redirect
from list.models import userdata, animes, UserAnime
from django.contrib import messages
from django.db import IntegrityError
from django.http import JsonResponse
from urllib.parse import unquote

#username:- Aditya
#password:- A??#1??4

# Create your views here.
def Homepage(request, version = "Login"):

    sections = []

    Sign_up = {'name':'Sign Up','url':'Sign_up', 'qualities':[{'name':'name', 'type':'text', 'heading':'Name'}, {'name':'email', 'type':'email', 'heading':'Email'}, {'name':'password', 'type':'password', 'heading':'Password'}, {'name':'DP', 'type':'file', 'heading':'Profile Picture'}]} 
    Login = {'name':'Login','url':'Login', 'qualities':[{'name':'email', 'type':'email', 'heading':'Email'}, {'name':'password', 'type':'password', 'heading':'Password'}]} 

    if version == "Login":
        Ver = Login
        if request.method == "POST":
            Email = request.POST.get("email")
            Password = request.POST.get("password")

            try:
                user = userdata.objects.get(email = Email)
                if user.password == Password:
                    request.session['userid'] = user.id
                    sections = [
                        {'heading':'Currently Watching', 'animelist':UserAnime.objects.filter(user = user, status = "CW")},
                        {'heading':'Plan to Watch', 'animelist':UserAnime.objects.filter(user = user, status = "PW")},
                        {'heading':'Completed Watching', 'animelist':UserAnime.objects.filter(user = user, status = "C")},
                    ]
                    messages.success(request, "Login Successful!")
                    return render(request, "homepage.html", {'sections': sections, 'version':Ver, 'user':user})
                else:
                    messages.error(request, "The Password is incorrect. Try again")
                    return redirect("Homepage")
                
            except userdata.DoesNotExist:
                messages.error(request, "The email entered doesn't exist. Try again")
                return redirect("Homepage")
        else:
            user = None
            if 'userid' in request.session:
                try:
                    user = userdata.objects.get(id = request.session['userid'])
                    sections = [
                        {'heading':'Currently Watching', 'animelist':UserAnime.objects.filter(user = user, status = "CW")},
                        {'heading':'Plan to Watch', 'animelist':UserAnime.objects.filter(user = user, status = "PW")},
                        {'heading':'Completed Watching', 'animelist':UserAnime.objects.filter(user = user, status = "C")},
                    ]
                except userdata.DoesNotExist:
                    user = None
            return render(request, "homepage.html", {'sections':sections, 'version':Ver, 'user':user})


    elif version == "Sign_up":
        Ver = Sign_up

        if request.method == "POST":
            Name = request.POST.get("name")
            Email = request.POST.get("email")
            Password = request.POST.get("password")
            DP = request.FILES.get("DP")

            try:
                userdata.objects.create(
                    name = Name,
                    email = Email,
                    password = Password,
                    userimage = DP
                )
                messages.success(request, "Account Created Successfully!")
                return redirect("Homepageform", version = "Login")

            except IntegrityError:
                messages.error(request, "Multiple users with same email, try another email.")
                return redirect("Homepageform", version = "Sign_up")
        else:
            return render(request, "homepage.html", {'sections':sections, 'version': Ver, 'user':None})
        
def logout(request):
    request.session.flush()
    return redirect("Homepage")
                
def search_anime(request):
    query = request.GET.get("name", "")

    results = []
    if query:
        matches = animes.objects.filter(name__icontains=query).values("id", "name")
        if matches:
            results=list(matches)
            return JsonResponse({"results":results})
        
        else:
            return JsonResponse({"results":"No match found"})
    
    else:
        return redirect("animes")


def anime(request, email, id):
    user = userdata.objects.get(email = unquote(email))
    Anime = animes.objects.get(id = id)
    userAnime = UserAnime.objects.get(user = user, anime = Anime)

    if request.method == "POST":
        status = request.POST.get("status")
        userAnime.status = status
        userAnime.save()
        return JsonResponse({"success":True, "status":userAnime.get_status_display()})
        
    return render(request, "animes.html", {'details':userAnime, 'Anime':Anime, 'user': user, 'id':id})