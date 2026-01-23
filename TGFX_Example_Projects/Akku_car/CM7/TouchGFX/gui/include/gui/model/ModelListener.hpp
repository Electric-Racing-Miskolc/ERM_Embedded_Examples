#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void buttonControl(int stateAVG, int stateALL){} //empty definition, tame has to be the same in the presenter

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
