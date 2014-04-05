#include "InitWindow.h"

int main(int argc, char **argv)
{
    Config *cfg=loadCFG("config.cfg");
    init_and_run_window(cfg);

    return 0;
}
