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


