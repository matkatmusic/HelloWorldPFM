/*
  ==============================================================================

    ThreadExample.h
    Created: 19 Jun 2019 5:22:54pm
    Author:  Charles Schiermeyer

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct MyThreadExample : Thread
{
    MyThreadExample() : Thread("Thread Example")
    {
        startThread();
    }
    
    ~MyThreadExample()
    {
        stopThread(500);
    }
    
    void run() override
    {
        while( true )
        {
            if( threadShouldExit() )
                break;
            
            /*
             do some work
             */
            if( threadShouldExit() )
                break;
            /*
             do some work
             */
            if( threadShouldExit() )
                break;
            
            wait( 10 );
            //or
            wait( -1 );
            /*
             MyThread mt;
             mt.notify();
             */
        }
    }
};
//=================================================================
struct ImageProcessingThread : public Thread
{
    ImageProcessingThread(int w_, int h_ ) : Thread("ImageProcessingThread"), w(w_), h(h_)
    { startThread(); }
    
    ~ImageProcessingThread()
    { stopThread(500); }
    
    void run() override;
    //our updateRenderer is private, so we need a setter
    void setUpdateRendererFunc(std::function<void(Image&&)> f ) { updateRenderer = std::move(f); }
private:
    //members to hold the image size
    int w { 0 }, h {0};
    std::function<void(Image&&)> updateRenderer;
    Random r;
};
//=================================================================
struct LambdaTimer : Timer
{
    LambdaTimer(int ms, std::function<void()> f);
    ~LambdaTimer();
    void timerCallback() override;
private:
    std::function<void()> lambda;
};
//=================================================================
struct Renderer : Component
{
    void paint(Graphics& g) override;
private:
    std::unique_ptr<ImageProcessingThread> processingThread;
};
