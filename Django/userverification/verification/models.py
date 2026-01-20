from django.db import models

# Create your models here.
class database(models.Model):
    name = models.CharField(max_length=100)
    number = models.CharField(max_length=10)
    email = models.EmailField()
    password = models.CharField(max_length=100)

    def __str__(self):
        return self.name