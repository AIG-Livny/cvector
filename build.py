#!/usr/bin/python3

def get_config() -> 'mapyr.Config':
    tc = mapyr.Config()
    tc.MINIMUM_REQUIRED_VERSION = '0.6.0'
    return tc

def get_project(name:str) -> 'mapyr.Project|None':
    if name not in ['main','debug','test']:
        return None

    p = mapyr.create_c_project(
        name,
        'libcvector.a',
        private_config={
            'SOURCES':['cvector.c'],
            'CFLAGS':['-Ofast','-flto'] if name == 'main' else ['-g','-O0'],
        },
        export_config={
            'INCLUDE_DIRS':['.'],
            'LIBS':['cvector'],
            'LIB_DIRS':['.'],
        }
    )

    if name == 'test':
        test = mapyr.create_c_project('test',
            private_config={
                'SOURCES':['test.c'],
                'CFLAGS':['-g','-O0'],
            },
            subprojects=[p]
        )
        return test

    return p

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
        mapyr.process(get_project,get_config)