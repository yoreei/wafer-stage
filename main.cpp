import <iostream>;
import <thread>;

import logger;
import input;
import renderer;
import wafer;
using namespace logger;

int main()
{
    ConsoleLogger logger {};
    logger.log("init main");
    ConsoleInput console_input {logger};
    WaferStage wafer_stage = console_input.get_wafer();
    ConsoleRenderer console_renderer {wafer_stage};
    auto stage_task = run_task([&stage](){stage.move(0.1)});
    auto render_task = run_task([&stage](){console_renderer.render(stage)});
    stage_task.join();

    logger.log("end main");
}
/*
point
0 - 1 float [0.1, 0.2, 0.3.. 1]
0 - 150

movepoint(accel, pos)
*/