#!/usr/bin/python3

def config() -> list["mapyr.ProjectConfig"]:
    result = []

    default = mapyr.ProjectConfig()
    default.OUT_FILE  = "libcvector.a"
    default.SRC_DIRS  = ['.']

    result.append(default)
    return result

#-----------FOOTER-----------
# https://github.com/AIG-Livny/mapyr.git
try:
    import mapyr
except:
    import requests, os
    os.makedirs(f'{os.path.dirname(__file__)}/mapyr',exist_ok=True)
    with open(f'{os.path.dirname(__file__)}/mapyr/__init__.py','+w') as f:
        f.write(requests.get('https://raw.githubusercontent.com/AIG-Livny/mapyr/master/__init__.py').text)
    import mapyr

if __name__ == "__main__":
    mapyr.process(config)