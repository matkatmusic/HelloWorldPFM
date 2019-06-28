/*
  ==============================================================================

    ThreadExample.cpp
    Created: 19 Jun 2019 5:22:54pm
    Author:  Charles Schiermeyer

  ==============================================================================
*/

#include "ThreadExample.h"

void ImageProcessingThread::run()
{
    while(true)
    {
        if( threadShouldExit() )
            break;
        
        auto canvas = Image(Image::PixelFormat::RGB, w, h, true);
        
        if( threadShouldExit() )
            break;
        
        for( int x = 0; x < w; ++x )
        {
            for( int y = 0; y < h; ++y )
            {
                canvas.setPixelAt(x, y, Colour{r.nextFloat(), r.nextFloat(), r.nextFloat(), r.nextFloat()});
            }
        }
        
        if( threadShouldExit() )
            break;
        
        if( updateRenderer )
            updateRenderer(std::move(canvas)); //move semantics don't allocate or so we currently believe
        
        wait(-1);
    }
}
//=================================================================
LambdaTimer::LambdaTimer(int ms, std::function<void()> f) : lambda(std::move(f))
{
    startTimer(ms);
}

LambdaTimer::~LambdaTimer()
{
    stopTimer();
}

void LambdaTimer::timerCallback()
{
    stopTimer();
    if( lambda )
        lambda();
}
//=================================================================
void Renderer::paint(Graphics& g)
{
    
}
