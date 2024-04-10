module;

#include <thread>
#include <chrono>

export module sim;
import <iostream>;

export namespace sim {
    void simulate() {
               std::cout << "Simulating...\n";
    }

    class IWaferStage {
    public:
        virtual float getPos() = 0;
        virtual void move(float accel, float pos2) = 0;
        virtual void simulate(float pos2) = 0;
        virtual void display() = 0;
        virtual void sleep() = 0;
    };

    class WaferStage {
    public:
        WaferStage() = default;
        WaferStage(float _pos) : pos(_pos) {};
        virtual float getPos()
        {
            return pos;
        }
        virtual void setPos(float _pos)
        {
            pos = _pos;
        }

        void move(float accel /* speed */, float pos2)
        {
            pos += accel;
        }
        /*
        HW:
    
        */
        void simulate(float pos2)
        {
            const float MIN_DIFF = 0.01;
            float ABS_ACCEL = 0.01;
            float accel = pos < pos2 ? ABS_ACCEL : -ABS_ACCEL; // vel
            while(pos2 - pos < MIN_DIFF)
            {
                move(accel, pos2);
                sleep();
            }
            std::cout<<"DONE";
        }

        void sleep()
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(20ms);
        }

    private:
        float pos = .0;
    };
}

