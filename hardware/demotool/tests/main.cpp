// Copyright (C) 2006 Ruben Smits <ruben dot smits at mech dot kuleuven dot be>
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//  
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//  

#include <rtt/RTT.hpp>
#include <rtt/NonPreemptibleActivity.hpp>
#include <rtt/os/main.h>
#include "hardware/demotool/Demotool.hpp"
#include "hardware/krypton/KryptonK600Sensor.hpp"
#include "hardware/wrench/WrenchSensor.hpp"
#include "taskbrowser/TaskBrowser.hpp"
#include "reporting/FileReporting.hpp"


using namespace std;
using namespace RTT;
using namespace Orocos;


/**
 * main() function
 */
int ORO_main(int arc, char* argv[])
{
    // Set log level more verbose than default,
    // such that we can see output :
    if ( Logger::log().getLogLevel() < Logger::Info ) {
        Logger::log().setLogLevel( Logger::Info );
        Logger::log() << Logger::Info << argv[0] << " manually raises LogLevel to 'Info' (5). "
		      << "See also file 'orocos.log'."<<Logger::endl;
    }

    // krypton
    KryptonK600Sensor krypton("Krypton",6);
    NonPreemptibleActivity kryptonTask(0.1, krypton.engine() );

    // wrench sensor
    WrenchSensor wrenchsensor(0.01, "Wrenchsensor", 0);
    NonPreemptibleActivity wrenchsensorTask(0.1, wrenchsensor.engine() );

    // demotool task
    Demotool demotool("Demtool");
    NonPreemptibleActivity demotoolTask(0.1, demotool.engine() );
    demotool.connectPeers(&krypton);
    demotool.connectPeers(&wrenchsensor);

    // reporter
    FileReporting reporter("Reporting");
    reporter.connectPeers(&demotool);
 
    TaskBrowser browser( &demotool );
    browser.loop();

    demotoolTask.stop();
    kryptonTask.stop();
    wrenchsensorTask.stop();
    return 0;
}
