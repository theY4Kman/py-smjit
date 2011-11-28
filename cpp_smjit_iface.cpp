#include <cpp_smjit.h>
#include <sp_vm_api.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

using namespace SourcePawn;

typedef ISourcePawnEngine2 *(*GET_SP_V2)();

struct sm_plugininfo_c_t
{
    cell_t name;
    cell_t description;
    cell_t author;
    cell_t version;
    cell_t url;
};
sm_plugininfo_c_t *cinfo;

GET_SP_V2 get_sp_func = NULL;
ISourcePawnEngine2 *g_JIT = NULL;
IPluginRuntime *g_Plugin = NULL;

char LoadSourcePawnEngine2()
{
    if (get_sp_func == NULL)
    {
        void *lib = dlopen("sourcepawn.jit.x86.dylib", RTLD_NOW);
        get_sp_func = (GET_SP_V2)dlsym(lib, "GetSourcePawnEngine2");
    }

    g_JIT = get_sp_func();
    return (g_JIT != 0);
}

char LoadPlugin(char *path)
{
    int err;
    ICompilation *co = g_JIT->StartCompilation();
    g_Plugin = g_JIT->LoadPlugin(co, path, &err);

    return (g_Plugin != 0);
}

unsigned int FindPubvarByName(char *name)
{
	unsigned int idx;
	int err = g_Plugin->FindPubvarByName(name, &idx);

	return idx;
}

char GetMyinfo()
{
    cell_t local_addr;

	unsigned int idx;
	int err = g_Plugin->FindPubvarByName("myinfo", &idx);

    return (g_Plugin->GetPubvarAddrs(idx, &local_addr, (cell_t **)&cinfo) == 0);
}

char * GetMyinfoVar(char *var)
{
    unsigned int idx = NULL;
    if (strcmp(var, "name") == 0)
        idx = cinfo->name;
    else if (strcmp(var, "description") == 0)
        idx = cinfo->description;
    else if (strcmp(var, "author") == 0)
        idx = cinfo->author;
    else if (strcmp(var, "version") == 0)
        idx = cinfo->version;
    else if (strcmp(var, "url") == 0)
        idx = cinfo->url;

    char *value = new char[512];
    IPluginContext *ctx = g_Plugin->GetDefaultContext();
    ctx->LocalToString(idx, (char **)&value);

    return value;
}