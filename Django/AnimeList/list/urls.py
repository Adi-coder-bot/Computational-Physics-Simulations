from django.urls import path
from list import views

urlpatterns = [
    path('', views.Homepage, name="Homepage"),
    path('logout/', views.logout, name="logout"),
    path('search/', views.search_anime, name="search"),
    path('anime/<str:email>/<int:id>/', views.anime, name="animes"),
    path('<str:version>/', views.Homepage, name="Homepageform"),
]
