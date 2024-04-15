export module model.wafer;
import <chrono>;
import <thread>;
import <cmath>;
import coremem;
import logger;

class Iwafer_action {
public:
    virtual ~Iwafer_action() = default;
};

export class Iwafer_stage {
public:
    virtual float get_pos() = 0;
    virtual float get_vel() = 0;
    virtual void move(float accel, float pos2) = 0;
    virtual bool is_finished() const = 0;
};

class Imove_profile {
public:
    virtual void set_target(float velocity_norm, float tar_pos) = 0;
    virtual float yield() = 0;
};

class Wafer_move : public Iwafer_action {
public:
    Wafer_move(float _tar_pos, float _accel) : tar_pos(_tar_pos), accel(_accel) {}
    float tar_pos;
    float accel;
};

export class Wafer_stage : public Iwafer_stage {
public:
    Wafer_stage();
    Wafer_stage(float _pos);

    // Iwafer_stage
    float get_pos() override;
    float get_vel() override;
    void move(float accel, float pos2) override;
    bool is_finished() const override;
private:
    // Wafer_stage
    void sleep();
    void history_push(shr_ptr<Iwafer_action> action);
    std::atomic<bool> m_finished = false;
    float m_pos = .0;
    float m_accuracy = 0.01;
    uniq_ptr<Imove_profile> m_move_profile;
    std::vector<shr_ptr<Iwafer_action>> m_history;
};

class Triangular_profile : public Imove_profile {
public:
    // Imove_profile
    void set_target(float velocity_norm, float tar_pos) override;
    float yield() override;
    // Triangular_profile
    Triangular_profile(Iwafer_stage* stage) : m_stage(stage) {}
private:
    float m_velocity_norm = 0.f;
    float m_tar_pos = 0.f;
    float m_init_pos = 0.f;
    Iwafer_stage* m_stage;
};