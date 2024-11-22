#!/usr/bin/python3

import copy

def tool_config() -> "mapyr.ToolConfig":
    tc = mapyr.ToolConfig()
    tc.MINIMUM_REQUIRED_VERSION = '0.5.0'
    return tc

def config() -> dict[str,"mapyr.ProjectConfig"]:
    main = mapyr.ProjectConfig()
    main.OUT_FILE  = "libcvector.a"
    main.CFLAGS = ['-Ofast','-flto']
    main.INCLUDE_DIRS  = ['.']
    main.SOURCES = ['cvector.c']

    debug = copy.deepcopy(main)
    debug.CFLAGS = ['-g','-O0']

    test = mapyr.ProjectConfig()
    test.OUT_FILE = "test"
    test.SOURCES = ['test.c']
    test.CFLAGS = ['-g','-O0']
    test.SUBPROJECTS = [
        debug
    ]

    return {
        'main':main,
        'debug':debug,
        'test':test,
    }

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
    mapyr.process(config, tool_config)