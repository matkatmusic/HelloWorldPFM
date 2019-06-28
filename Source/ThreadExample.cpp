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
        
        /*
         image processing here
         */
        
        if( threadShouldExit() )
            break;
        
        if( updateRenderer )
            updateRenderer(std::move(canvas)); //move semantics don't allocate or so we currently believe
        
        wait(-1);
    }
}
