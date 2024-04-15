export module renderer;
import model.wafer;
import coremem;

export class Irenderer {
public:
    virtual void render(shr_ptr<Iwafer_stage> wafer) = 0;
};

export class Console_renderer : public Irenderer {
public:
    // Irenderer
    virtual void render(shr_ptr<Iwafer_stage> wafer) override;
private:
    void write(Iwafer_stage& wafer);
};
