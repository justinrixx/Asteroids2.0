/********************************************************
 * This a c++ module to be called from Python.
 ********************************************************/

#include <Python.h>
#include <vector>
#include "game.h"
#include "neuralnetai.h"

using namespace std;

/**************************************************
 * This is the actual function that will be called
 *************************************************/
static int run(string filename)
{
    srand(clock());
    Game * pGame = new Game();

    vector<int> topology;
    topology.push_back(20);

    Network net(31, 4, topology);

    net.fromFile(filename);

    NNAI ai(pGame, net);

    pGame->setAI(&ai);

    while (!pGame->isGameOver())
        pGame->update(NULL);

    return pGame->getScore();
}

static PyObject *
nnrunner_run(PyObject * self, PyObject * args)
{
    string filename;
    int score;
    if (!PyArg_ParseTuple(args, "s", &filename))
        return NULL;
    score = run(filename);
    return PyLong_FromLong(score);
}

static PyMethodDef NnrunnerMethods[] = {
        {"run",  nnrunner_run, METH_VARARGS,
         "Run the game and return the score"},
        {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef nnrunnermodule = {
        PyModuleDef_HEAD_INIT,
        "nnrunner",   /* name of module */
        NULL, /* module documentation, may be NULL */
        -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
        NnrunnerMethods
};

PyMODINIT_FUNC
PyInit_nnrunner(void)
{
    PyObject *m;

    m = PyModule_Create(&nnrunnermodule);
    if (m == NULL)
        return NULL;

    return m;
}