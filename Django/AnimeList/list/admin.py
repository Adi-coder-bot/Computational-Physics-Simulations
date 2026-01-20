from django.contrib import admin
from list.models import userdata, Genres, animes, UserAnime

# Register your models here.
admin.site.register(userdata)
admin.site.register(Genres)
admin.site.register(animes)
admin.site.register(UserAnime)