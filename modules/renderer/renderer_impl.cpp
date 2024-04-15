module renderer;

import <iostream>;
import <thread>;
import <thread>;
import <chrono>;
import model.wafer;
import logger;
import coremem;

void Console_renderer::render(shr_ptr<Iwafer_stage> wafer)
{
    using namespace std::chrono_literals;
    LOG_INFO("INIT render");
    while(!wafer->is_finished()){
        write(*wafer);
        std::this_thread::sleep_for(100ms);
    }
    LOG_INFO("END render");
}

void Console_renderer::write(Iwafer_stage& wafer)
{
    for(int i = 0; i < wafer.get_pos() * 80; ++i){
        std::cout<<"_";
    }
    std::cout<<"+";
    for(int i = wafer.get_pos() * 80; i < 80; ++i){
        std::cout<<"_";
    }
    std::cout<<"\r";
}