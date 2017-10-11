#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class CyberDNS;
class CyberWorm;
class CyberPC;
class CyberExpert;

#include "../include/cyberworm.h"
#include "../include/cyberexpert.h"
#include "../include/cyberpc.h"
#include "../include/cyberdns.h"

// vector holding pc names
vector<string> cyberPcNamesVec;
// vector holding experts pointer
vector<CyberExpert *> cyberExpertVec;
// vector holding dns pointer
CyberDNS *cyberDNS;

// simulate a day without including the XML
void simulateSingleDay()
{    
    unsigned int computerIndex = 0;
    
    // assign computers to experts for clean up.
    for (unsigned int i = 0; i != cyberExpertVec.size() && computerIndex < cyberDNS->GetCyberPCList().size(); i++)
      for(unsigned int j = 0; j < cyberExpertVec[i]->GetEfficiency() && computerIndex < cyberDNS->GetCyberPCList().size(); j++)
	cyberExpertVec[i]->Clean(cyberDNS->GetCyberPC(cyberDNS->GetCyberPCList()[computerIndex++]));

    for (unsigned int i = 0; i != cyberExpertVec.size(); i++)
      cyberExpertVec[i]->DayPassed();
    
    for (unsigned int i = 0; i != cyberDNS->GetCyberPCList().size(); i++)
      cyberDNS->GetCyberPC(cyberDNS->GetCyberPCList()[i]).Run(*cyberDNS);
}

//fill the computers address to dns vector according to their names 
void fillDNSServer()
{
	using boost::property_tree::ptree;
  	ptree pt;
	
	read_xml("./computers.xml", pt);
	BOOST_FOREACH(ptree::value_type &v, pt.get_child(""))
	{
	  cout << "Adding to server: " << v.second.get<string>("name") << endl;
	  if(!cyberDNS->IsComputerExist(v.second.get<string>("name")))
	  {
	    cyberPcNamesVec.push_back(v.second.get<string>("name"));
	    CyberPC *c = new CyberPC(v.second.get<string>("os"), v.second.get<string>("name"));
	    cyberDNS->AddPC(*c);
	  }
	  cout << v.second.get<string>("name") << " connected to server" << endl;
	}
}

//building the network
void buildNetwork()
{
  	using boost::property_tree::ptree;
  	ptree pt;
  
  	read_xml("./network.xml", pt);
	BOOST_FOREACH(ptree::value_type &v, pt.get_child(""))
	{
	  cout << "Connecting " << v.second.get<string>("pointA") << " to " << v.second.get<string>("pointB") << endl;
	  cyberDNS->GetCyberPC(v.second.get<string>("pointA")).AddConnection(v.second.get<string>("pointB"));
	  cout << "\t" << v.second.get<string>("pointA") << " now connected to " << v.second.get<string>("pointB") << endl;
	  cyberDNS->GetCyberPC(v.second.get<string>("pointB")).AddConnection(v.second.get<string>("pointA"));
	  cout << "\t" << v.second.get<string>("pointB") << " now connected to " << v.second.get<string>("pointA") << endl;
	}
	
}

// simulate event in events xml by day
void eventOccured()
{
  //number of days
  int day = 0;
  
  using boost::property_tree::ptree;
  ptree pt;
  
  read_xml("./events.xml", pt);
  
  const int MAX_DAYS = pt.get<int>("termination.time");

  BOOST_FOREACH(ptree::value_type &v, pt.get_child(""))
  {
    if(day <= MAX_DAYS)
    {
      cout << "Day : " << day << endl;
      // hack event
      if(v.first == "hack")
      {
		cout << "\tHack occured on " << v.second.get<string>("computer") << endl;

		CyberWorm *w = new CyberWorm(v.second.get<string>("wormOs"), v.second.get<string>("wormName"), v.second.get<int>("wormDormancy"));

		cyberDNS->GetCyberPC(v.second.get<string>("computer")).Infect(*w); 
		delete w;
      }
      // clock in event
      if(v.first == "clock-in")
      {
		cyberExpertVec.push_back(new CyberExpert(v.second.get<string>("name"), v.second.get<int>("workTime"),v.second.get<int>("restTime"),v.second.get<int>("efficiency")));
	  }
      simulateSingleDay();
    }
    day++;
  }
  
  // if there are more events to run on
  while(day <= MAX_DAYS)
  {
    cout << "Day : " << day << endl;
    simulateSingleDay();
    day++;
  }
}

//delete variables to avoid memory leaks
void deleteVars()
{
  for (unsigned int i = 0; i != cyberExpertVec.size(); i++)
    delete cyberExpertVec[i];
  delete cyberDNS;
}

int main()
{  
    
    try
    {
	cyberDNS = new CyberDNS();
	
	fillDNSServer();

	buildNetwork();
	
	eventOccured();
	
	deleteVars();
	
    }
    catch (exception &e)
    {
       cout << "Error: " << e.what() << "\n";
    }
    return 0;
}