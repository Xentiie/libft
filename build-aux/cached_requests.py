import os
import requests
import pickle
from selenium.webdriver import Firefox, FirefoxOptions
from selenium.webdriver.firefox.service import Service

CACHE_DIR="./cached_requests/"
def get_cache_path(url:str):
    return CACHE_DIR + url.replace("/", "_")

def cache_store(url:str, data):
    if (not os.path.exists(CACHE_DIR)):
        os.mkdir(CACHE_DIR)

    cache_path = get_cache_path(url)
    with open(cache_path, "wb") as f:
        return pickle.dump(data, f)
    
def cache_load(url:str) -> requests.Response|None:
    cache_path = get_cache_path(url)
    if (not os.path.exists(cache_path)):
        return None
    with open(cache_path, "rb") as f:
        return pickle.load(f)

def cached_get_selenium(url:str) -> str:

    cached = cache_load(url)
    if (cached is None):
        options = FirefoxOptions()
        options.add_argument("-headless")
        driver = Firefox(options=options, service=Service("/snap/bin/geckodriver"))
        driver.get("http://users.atw.hu/instlatx64")
        content = driver.page_source
        driver.quit()
        cache_store(url, content)
        return content
    else:
        return cached

def cached_get(url:str, *args, **kwargs) -> requests.Response:
    cached = cache_load(url)
    if (cached is None):
        response = requests.get(url, *args, **kwargs)
        cache_store(url, response)
        return response
    else:
        return cached
