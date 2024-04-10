export module renderer;
import sim;

export class IRenderer {
    virtual void render(sim::IWaferStage wafer) = 0;
};

class ConsoleRenderer : public IRenderer {
    virtual void render(sim::IWaferStage wafer) override;
};
