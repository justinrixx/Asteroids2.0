from distutils.core import setup, Extension

module1 = Extension('nnrunner',
                    sources = ['nnrunner.cpp', 'game.cpp', 'uiDraw.cpp', 
                    'uiInteract.cpp', 'player.cpp', 'ship.cpp', 'network.cpp'],
                    libraries = ['glut', 'GL', 'GLU'])

setup (name = 'NNRunner',
       version = '1.0',
       description = 'This is my first package',
       ext_modules = [module1])