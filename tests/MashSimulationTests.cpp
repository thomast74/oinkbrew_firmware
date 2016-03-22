#include <boost/test/unit_test.hpp>
#include "runner.h"

#include "ControllerManager.h"

struct MashSetup{
public:
    MashSetup(){
        BOOST_TEST_MESSAGE( "setup mash test fixture" );

        ControllerConfiguration request;
        request.id = 11;
        request.name = "Mach Simulation";
        request.type = 1;

        request.heatActuator = ;		// need to be able to inject a mock actuator
        request.heatingPeriod = 4000;
        request.tempSensor = ;			// need to be able to inject a mock temp sensor so I can calculate the temperatur
        request.temperature = 65.0;
        request.p = 0;					// add real value
        request.i = 0;					// add real value
        request.d = 0;					// add real value

        controllerManager.changeController(request);
    }
    ~MashSetup(){
        BOOST_TEST_MESSAGE( "tear down mash test fixture" );
    }

    void process(){
    	//calculate new temperature
    	// run

    	controllerManager.process();
    	controllerManager.update();
    }
};

struct MashSimHlt : public MashSetup {

};

struct MashSimMash : public MashSetup {

};

BOOST_AUTO_TEST_SUITE( mash_simulation_tests )

BOOST_FIXTURE_TEST_CASE(Simulate_HLT_Temp_Control, MashSimHlt)
{
    ofstream csv("./test_results/" + boost_test_name() + ".csv");
    csv << "4#P, 4#I, 4#D"
        << endl;

    for(int t = 0; t < 7200; t++){
    	process();

        csv << 1 << ","
            << 2 << ","
            << 3
            << endl;

    	delay(1000);
    }

    csv.close();
};

BOOST_FIXTURE_TEST_CASE(Simulate_Mash_Temp_Control, MashSimMash)
{
    ofstream csv("./test_results/" + boost_test_name() + ".csv");
    csv << "4#P, 4#I, 4#D"
        << endl;

    for(int t = 0; t < 7200; t++){
    	process();

        csv << 1 << ","
            << 2 << ","
            << 3
            << endl;

    	delay(1000);
    }

    csv.close();
};


BOOST_AUTO_TEST_SUITE_END()
