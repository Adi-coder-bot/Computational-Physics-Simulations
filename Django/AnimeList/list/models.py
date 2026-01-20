from django.db import models

# Create your models here.
class userdata(models.Model):
    name = models.CharField(max_length=100)
    email = models.EmailField(unique=True)
    password = models.CharField(max_length=100)
    userimage = models.ImageField(upload_to='user_images')

    def __str__(self):
        return self.name
    
class Genres(models.Model):
    name = models.CharField(max_length=50, unique=True)

    def __str__(self):
        return self.name
    
class animes(models.Model):
    name = models.CharField(max_length=500)
    genres = models.ManyToManyField(Genres)
    cliphanger = models.ImageField(upload_to='anime_images')
    link = models.URLField(max_length=500, default="https://hianimez.is")

    def __str__(self):
        return self.name
    
class UserAnime(models.Model):
    STATUS_CHOICES = [
        ("CW", "Currently Watching"),
        ("PW", "Plan to Watch"),
        ("C", "Completed"),
    ]

    user = models.ForeignKey(userdata, on_delete=models.CASCADE)
    anime = models.ForeignKey(animes, on_delete=models.CASCADE)
    status = models.CharField(max_length=2, choices=STATUS_CHOICES)

    def __str__(self):
        return f"{self.user.name} - {self.anime.name} ({self.get_status_display()})"