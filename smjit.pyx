cdef extern from "cpp_smjit.h":
    char LoadSourcePawnEngine2()
    char LoadPlugin(char *path)
    unsigned int FindPubvarByName(char *name)
    char GetMyinfo()
    char * GetMyinfoVar(char *var)

cdef class PySMJIT:
    def __cinit__(self):
        LoadSourcePawnEngine2()
    def __str__(self):
        return '<SourcePawnEngine2 instance>'
    def load_plugin(self, path):
        return bool(LoadPlugin(<char *>path))
    def find_pubvar(self, name):
        return FindPubvarByName(<char *>name)
    def load_myinfo(self):
        return bool(GetMyinfo())
    def get_myinfo(self, var):
        return GetMyinfoVar(<char *>var)