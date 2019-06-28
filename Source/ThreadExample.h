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
struct ImageProcessingThread;
using ImagePassingFunc = std::function<void(Image&&, ImageProcessingThread&)>;

struct ImageProcessingThread : public Thread
{
    ImageProcessingThread(int w_, int h_, ImagePassingFunc f) : Thread("ImageProcessingThread"), w(w_), h(h_), updateRenderer( std::move(f) )
    { startThread(); }
    
    ~ImageProcessingThread()
    { stopThread(500); }
    
    void run() override;
    //our updateRenderer is private, so we need a setter
//    void setUpdateRendererFunc(std::function<void(Image&&)> f ) { updateRenderer = std::move(f); }
private:
    //members to hold the image size
    int w { 0 }, h {0};
    ImagePassingFunc updateRenderer;
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
#include <array>
struct Renderer : Component, AsyncUpdater
{
    Renderer();
    ~Renderer();
    void paint(Graphics& g) override;
    void handleAsyncUpdate() override;
private:
    std::unique_ptr<ImageProcessingThread> processingThread;
    std::unique_ptr<LambdaTimer> lambdaTimer;
    bool firstImage = true;
    std::array<Image, 2> imageToRenderTo;
};
