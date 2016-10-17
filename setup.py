"""
To build this module:
python3 setup.py build
python3 setup.py install
"""
from distutils.core import setup, Extension

module1 = Extension('nnrunner',
                    sources = ['nnrunner.cpp', 'game.cpp', 'uiDraw.cpp', 
                    'uiInteract.cpp', 'player.cpp', 'ship.cpp', 'network.cpp'],
                    libraries = ['glut', 'GL', 'GLU'],
                    library_dirs = ['/home/justin/code/Asteroids2.0/module_includes'])

setup (name = 'NNRunner',
       version = '1.0',
       description = 'This is my first package',
       ext_modules = [module1])