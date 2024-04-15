import <iostream>;
import <thread>;
import <future>;

import logger;
import renderer;
import model.wafer;
import coremem;

class Core : public std::enable_shared_from_this<Core> {
private:
    struct Private_tag {};
public:
    Core(Private_tag _) :
        m_wafer_stage(create_wafer()),
        m_renderer(create_renderer())
    {
        LOG_INFO("CONSTRUCTED Core");
    }
    void run()
    {
        float tar_pos;
        std::cout<<"target position:\n";
        std::cin>>tar_pos;
        float accel;
        std::cout<<"acceleration:\n";
        std::cin>>accel;

        auto core_ptr = shared_from_this();

        auto stage_task = run_task([tar_pos, accel, core_ptr](){
            core_ptr->get_wafer()->move(tar_pos, accel);
            });
        auto render_task = run_task([core_ptr](){
            auto wafer_ptr = core_ptr->get_wafer();
            core_ptr->get_renderer()->render(wafer_ptr);
            });
        stage_task.wait();
        render_task.wait();
    }
    static shr_ptr<Core> create()
    {
        return std::make_shared<Core>(Private_tag{});
    }
private:
    std::future<void> run_task(std::function<void()> task) {
        return std::async(std::launch::async, task);
    }

    static shr_ptr<Iwafer_stage> create_wafer()
    {
        float init_pos;
        std::cout<<"initial position:\n";
        std::cin>>init_pos;
        return std::make_shared<Wafer_stage>(init_pos);
    }

    static shr_ptr<Irenderer> create_renderer()
    {
        return std::make_shared<Console_renderer>();
    }

    shr_ptr<Iwafer_stage> get_wafer() {
        return m_wafer_stage;
    }

    shr_ptr<Irenderer> get_renderer() {
        return m_renderer;
    }

    shr_ptr<Iwafer_stage> m_wafer_stage;
    shr_ptr<Irenderer> m_renderer;
};

int main()
{
    LOG_INFO("INIT main");

    shr_ptr<Core> core = Core::create();
    core->run();

    LOG_INFO("END main");
}
/*
point
0 - 1 float [0.1, 0.2, 0.3.. 1]
0 - 150

movepoint(accel, pos)
*/