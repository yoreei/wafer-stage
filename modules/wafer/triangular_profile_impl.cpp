module model.wafer;

import <chrono>;
import <thread>;
import <cmath>;
import <stdexcept>;
import coremem;
import logger;

void Triangular_profile::set_target(float velocity_norm, float tar_pos)
{
    if (!m_stage) { throw std::runtime_error("m_stage is invalid"); }
    m_velocity_norm = velocity_norm;
    m_tar_pos = tar_pos;
    m_init_pos = m_stage->get_pos();
}

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