from django.urls import path
from verification import views 

urlpatterns = [
    path('', views.signup, name='signup'),
    path('login/', views.login, name='login'),
]
