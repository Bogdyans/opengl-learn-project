#ifndef OPENGL_LEARN_TRIANGLE_TASKS_H
#define OPENGL_LEARN_TRIANGLE_TASKS_H

#include "../../../shared/files.h"

namespace triangle_tasks
{
    enum TTasks {
        TRIANGLE_TASK_1,
        TRIANGLE_TASK_2,
        TRIANGLE_TASK_3
    };

    int run(TTasks task);

    int taskT1();

    int taskT2();

    int taskT3();

}
#endif //OPENGL_LEARN_TRIANGLE_TASKS_H