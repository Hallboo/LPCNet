
// API of LPCNet for TTS Server
// Python code use LPCNet directly

// by Zhang Haobo
// Apr 2021

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <math.h>
#include <stdio.h>
#include "arch.h"
#include "lpcnet.h"
#include "freq.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

int debug_model = 0;

static PyObject * lpcnet(PyObject *self, PyObject *args)
{
    PyObject * listObj;

    if(!PyArg_ParseTuple(args, "O", &listObj)){
    	return NULL;
    }

    long length = PyList_Size(listObj);

    LPCNetState *net;
    net = lpcnet_create();


    PyObject* PCM_segments_list = PyList_New(length);

    for(int i = 0; i < length; i++){

        PyObject* one_frame_list = PyList_GetItem(listObj, i);

        float in_features[NB_TOTAL_FEATURES];
        float features[NB_FEATURES];
        short pcm[LPCNET_FRAME_SIZE];
        PyObject* PCM_list = PyList_New(LPCNET_FRAME_SIZE);

        if(debug_model){
            printf("\n\nin_features[%d]:", i);
        }

        for(int k = 0; k < NB_TOTAL_FEATURES; k++){

            PyObject* value_py = PyList_GetItem(one_frame_list, k);
            in_features[k] = PyFloat_AsDouble(value_py);

            if(debug_model){
                printf(" %f ", in_features[k]);
            }
        }

        RNN_COPY(features, in_features, NB_FEATURES);
        RNN_CLEAR(&features[18], 18);

        if(debug_model){
            printf("\n\nfeatures[%d]:", i);
            for(int k = 0; k < NB_FEATURES; k++){
                printf(" %f ", features[k]);
            }
        }

        lpcnet_synthesize(net, features, pcm, LPCNET_FRAME_SIZE);

        if(debug_model){
            printf("\n\nPCM[%d]:", i);
        }
        for(int k = 0; k < LPCNET_FRAME_SIZE; k++){
            PyList_SetItem(PCM_list, k, Py_BuildValue("i", pcm[k]));
       
            if(debug_model){
                printf(" %d ", pcm[k]);
            }
        }

        PyList_SetItem(PCM_segments_list, i, PCM_list); 

    }

    if(debug_model){
        printf("\n");
    }
    
    return PCM_segments_list;
}

static PyMethodDef LpcnetMethods[] = {

    {"run_for_chunk",lpcnet, METH_VARARGS,
    "Synthesis audio from the BFCC."},

    {NULL, NULL, 0, NULL}


};

static struct PyModuleDef lpcnetmodule = {

    PyModuleDef_HEAD_INIT,
    "lpcnet",   /* name of module */
    NULL,       /* module documentation, may be NULL */
    -1,         /* size of per-interpreter state of the module,
               or -1 if the module keeps state in global variables. */

    LpcnetMethods
};

PyMODINIT_FUNC PyInit_lpcnet(void)
{
    return PyModule_Create(&lpcnetmodule);
}


