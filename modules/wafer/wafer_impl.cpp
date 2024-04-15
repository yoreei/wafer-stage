module model.wafer;

import <chrono>;
import <thread>;
import <cmath>;
import coremem;
import logger;
//export import :move_profile;

void Triangular_profile::set_target(float velocity_norm, float tar_pos)
{
    if (!m_stage) { throw std::runtime_error("m_stage is invalid"); }
    m_velocity_norm = velocity_norm;
    m_tar_pos = tar_pos;
    m_init_pos = m_stage->get_pos();
}
/*
 * yield velocity based on linear interpolation 
 */
float Triangular_profile::yield()
{
    using std::fabs;
    float distance = fabs(m_tar_pos - m_init_pos);
    float h_distance = distance / 2.0;
    float traveled = fabs(m_stage->get_pos() - m_init_pos);
    float remaining = fabs(m_tar_pos - m_stage->get_pos());

    float vel = 0.f;

    if (traveled < h_distance) {
        vel = m_velocity_norm * (traveled / h_distance);
    } else {
        vel = m_velocity_norm * (remaining / h_distance);
    }

    return vel;
}

Wafer_stage::Wafer_stage()
    : Wafer_stage(.0)
{
}

Wafer_stage::Wafer_stage(float _pos)
    : m_pos(_pos)
{
    m_move_profile = std::make_unique<Triangular_profile>(this);
}

float Wafer_stage::get_pos()
{
    return m_pos;
}

float Wafer_stage::get_vel()
{
    return m_pos;
}

/* 
 * velocity_norm: 0 <= velocity_norm <= +inf
 */
void Wafer_stage::move(float velocity_norm, float tar_pos)
{
    if (velocity_norm <= 0) {
        throw std::invalid_argument("velocity_norm must be greater than 0");
    }
    m_finished = false;
    LOG_INFO("INIT move");
    history_push(std::make_shared<Wafer_move>(velocity_norm, tar_pos));

    m_move_profile->set_target(velocity_norm, tar_pos);
        
    float cur_vel = m_move_profile->yield();
    while(tar_pos - m_pos < m_accuracy)
    {
        cur_vel = m_move_profile->yield();
        m_pos += cur_vel;
        sleep();
    }
    m_finished = true;
    LOG_INFO("END move");
}

void Wafer_stage::sleep()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(20ms);
}

bool Wafer_stage::is_finished() const
{
    return m_finished;
}

void Wafer_stage::history_push(shr_ptr<Iwafer_action> action)
{
    m_history.push_back(action);
}

