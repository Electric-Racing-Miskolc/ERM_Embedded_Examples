#ifndef ACCUMULATOR_TEMP_1_SEGMENT_HPP
#define ACCUMULATOR_TEMP_1_SEGMENT_HPP

#include <gui_generated/containers/Accumulator_temp_1_segmentBase.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>

class Accumulator_temp_1_segment : public Accumulator_temp_1_segmentBase
{
public:
    Accumulator_temp_1_segment();
    virtual ~Accumulator_temp_1_segment() {}

    virtual void initialize();
    virtual void updateAllBars(int value, int avg);

protected:

    virtual void updateColor(PainterRGB565* painter, int value, int avg);
    int avgLimit[2];
};

#endif // ACCUMULATOR_TEMP_1_SEGMENT_HPP
