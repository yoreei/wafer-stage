import <iostream>;
import sim;

module renderer;

void ConsoleRenderer::render(sim::IWaferStage& wafer)
{
    for(int i = 0; i < wafer.getPos() * 80; ++i){
        std::cout<<"_";
    }
    std::cout<<"+";
    for(int i = wafer.getPos() * 80; i < 80; ++i){
        std::cout<<"_";
    }
    std::cout<<"\r";
}