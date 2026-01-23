#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{



public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
protected:
    ModelListener* modelListener;
    void handleButton(void);
    int state = 0;
};

#endif // MODEL_HPP
