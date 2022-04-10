import requests

path = "https://natas15.natas.labs.overthewire.org"
requests.post(path, data={"username": username})
